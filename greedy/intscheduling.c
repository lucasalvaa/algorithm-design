#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * INTERVAL SCHEDULING
 *
 * Input:
 * Let A = {A_1, ..., A_n} be a set of activities where each activity A_i
 * has a start time s_i and a finish time f_i, with s_i < f_i.
 * 
 * Problem:
 * The activities in A must be assigned to a resource,
 * under the condition that if Ai and Aj are both assigned 
 * to the resource, their intervals must not overlap in time.
 *
 * Output:
 * A subset S of A, in which the activities are pairwise
 * compatible in terms of time. The cardinality of S must be maximum.
 */

// First of all, let's define a struct representing an activity
typedef struct {
    char name;
    int s;  // start time
    int f;  // finish time
} activity_t;

// activity_selector is the function that solves the problem

/**
 * @brief Returns a subset of A containing the maximum amount of compatible activities.
 *
 * The function solves the problem using a greedy approach.
 *  #1 Activities are sorted in ascending order of end time.
 *  #2 First activity of A (A_i) is put into a new set S.
 *  #3 For each activity A_j in A-{A_1}, if it starts after
 *      the finish time of the last activity in S, A_j is put into S 
 *  
 * Time complexity: O(n*log(n))
 * The time complexity of this algorithm is dominated by the time complexity
 * of the sorting algorithm used in step #1. Since the quick sort algorithm
 * is used, the complexity is  O(n*log(n)). Step #3 just requires a O(n) time.
 *
 * @param A A set of activities to schedule. It could be unsorted.
 * @param input_size The number of activities in A.
 * @param output_size A pointer to a variabile that will contain the size of the subset S.
 *
 * @return A subset S of activities contained in A.
 */
activity_t *activity_selector (activity_t A[], const int input_size, int *output_size);


// Utilities

activity_t create_activity (const char name, const int s, const int f);

void sort_by_finish_time (activity_t A[], const int size);

int cmp (const void *a, const void *b);

void *secure_malloc(size_t bytes);

//

// A test for this function

// Array A
// 1  2  3  4  5  6  7  8  9  10 11 12 13 14 <- time
// a  a  a  a
//       b  b  b
//             c  c  c
//       d  d  d  d  d  d
//                e  e  e  e  e
//                      f  f  f  f
// g  g  g  g  g  g
//                      h  h  h  h  h
//    i  i  i  i  i  i  i  i  i  i  i  i
//                                  j  j  j
//             k  k  k  k  k 

// Sorted A
// 1  2  3  4  5  6  7  8  9  10 11 12 13 14 <- time
// a  a  a  a
//       b  b  b
// g  g  g  g  g  g
//             c  c  c
//       d  d  d  d  d  d
//             k  k  k  k  k
//                e  e  e  e  e
//                      f  f  f  f
//                      h  h  h  h  h
//    i  i  i  i  i  i  i  i  i  i  i  i
//                                  j  j  j

// Subset S
// 1  2  3  4  5  6  7  8  9  10 11 12 13 14 <- time
// a  a  a  a
//             c  c  c
//                      f  f  f  f
//                                  j  j  j
int  main () {
    const int n = 11;
    activity_t A[] = {
        create_activity('a', 1, 4), create_activity('b', 3, 5), 
        create_activity('c', 5, 7), create_activity('d', 3, 8), 
        create_activity('e', 6, 10), create_activity('f', 8, 11), 
        create_activity('g', 1, 6), create_activity('h', 8, 12),
        create_activity('i', 2, 13), create_activity('j', 12, 14),
        create_activity('k', 5, 9)
    };
    
    int size = 0;
    activity_t* S = activity_selector(A, n, &size);
    for (int i=0; i<size; i++) {
        printf("Activity %c: {start: %d, finish: %d}\n", S[i].name, S[i].s, S[i].f);
    }

    free(S);
    return 0;
}

activity_t *activity_selector (activity_t A[], const int input_size, int *output_size) {
    // Step #1
    // O(n*log(n))
    sort_by_finish_time(A, input_size);
    
    // Step #2
    // O(1)
    activity_t temp[input_size];
    int j=0;
    temp[j] = A[0];
    j++;

    // Step #3
    // O(n)
    for (int i=1; i<input_size; i++) {
        if (temp[j-1].f <= A[i].s) {
            temp[j] = A[i];
            j++;
        }
    }

    activity_t* S = secure_malloc(sizeof(activity_t) * j);
    memcpy(S, temp, sizeof(activity_t) * j);
    *output_size = j;
    return S;
}

void sort_by_finish_time (activity_t A[], const int size) {
    qsort(A, size, sizeof(activity_t), cmp);
}

int cmp (const void *a, const void *b) {
    const activity_t *act1 = (const activity_t *)a;
    const activity_t *act2 = (const activity_t *)b;
    return act1->f - act2->f;
}


void *secure_malloc (size_t bytes) {
    void *p = malloc(bytes);
    if (p == NULL) {
        fprintf(stderr, "malloc failed while requesting %ld bytes\n", bytes);
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return p;
}

activity_t create_activity (const char name, const int s, const int f) {
    if (f <= s) {
        fprintf(stderr, "Start time must be before finish time\n");
        exit(EXIT_FAILURE);
    }
    return (activity_t) {.name = name, .s = s, .f = f};
}