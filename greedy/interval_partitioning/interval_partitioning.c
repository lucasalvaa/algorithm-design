#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "minheap.h"

/**
 * INTERVAL PARTITIONING
 *
 * Input:
 * Let A = {A_1, ..., A_n} be a set of lectures where each activity A_i
 * has a start time s_i and a finish time f_i, with s_i < f_i.
 * 
 * Output:
 * We need to find the minimum number d of classrooms in which
 * we can arrange the n lectures in such a way that no two courses
 * take place at the same time in the same classroom.
 */

 // First of all, let's define a struct representing a lecture
typedef struct {
    char name;
    int s;  // start time
    int f;  // finish time
} lecture_t;

/**
 * Two solutions with different complexities are proposed.
 *
 * Solution #1 uses an array that keeps track of
 * the last end time for each classroom.
 *
 * Solution #2 uses a min heap where each node represents
 * the end time of the last lecture assigned to a classroom.
 *
 * We can split both implementations in two principal steps:
 * #1 Lectures in A are sorted in ascending order of start time.
 * #2 Computation of the minimum number of classrooms needed
 *      to schedule all lectures without overlap
 */

/**
 * Solution #1
 * Time complexity analysis
 *  - Step #1 has a complexity of O(n*log(n)) (quick sort)
 *  - Step #2 has a complexity of O(n^2)
 *      In the worst case, d can reach n, so the loop that searches
 *      for a classroom to assign the lecture to can run up to n
 *      iterations for each lecture.
 * 
 * In total, this solution has a complexity equal to O(n*log(n) + n^2) = O(n^2)
 */
int lectures_partitioning (lecture_t A[], int n);

/**
 * Solution #2
 * Time complexity analysis
 *  - Step #1 has a complexity of O(n*log(n)) (quick sort)
 *  - Step #2 has a complexity of O(n*log(d)), where d is the number of classrooms. 
 *      In the worst case, d=n, so the heap operations
 *      take O(log(n)) per lecture, totaling O(n*log(n)).
 *
 * It's clear that the time complexity of this solution is O(n*log(n)).
 */
int lectures_partitioning_heap (lecture_t A[], int n);

// Utilities

int cmp (const void *a, const void *b);

void *secure_malloc (size_t bytes);

//

// Test
int main() {
    lecture_t lectures[] = {
        {'A', 9, 11}, {'B', 9, 13}, {'C', 9, 11},
        {'D', 11, 13}, {'E', 11, 14}, {'F', 13, 15},
        {'G', 13, 15}, {'H', 14, 16}, {'I', 15, 17},
        {'J', 15, 17}
    };

    int n = sizeof(lectures) / sizeof(lecture_t);
    int classrooms_needed;

    // Solution #1 test
    classrooms_needed = lectures_partitioning(lectures, n);
    printf("Minimum amount of classrooms needed: %d\n", classrooms_needed);
    // Expected output: "Minimum amount of classrooms needed: 3"

    // Solution #2 test
    classrooms_needed = lectures_partitioning_heap(lectures, n);
    printf("Minimum amount of classrooms needed: %d (min heap)\n", classrooms_needed);
    // Expected output: "Minimum amount of classrooms needed: 3 (min heap)""

    return 0;
}

int lectures_partitioning (lecture_t A[], int n) {
    // O(n*log(n))
    qsort(A, n, sizeof(lecture_t), cmp);

    int d = 0;
    int classroom_finish_times[n];

    // O(n^2)
    for (int i=0; i<n; i++) {
        bool assigned = false;
        for (int j=0; j<d; j++) {
            if (A[i].s >= classroom_finish_times[j]) {   
                classroom_finish_times[j] = A[i].f;
                assigned = true;
                break;
            }
        }

        if (!assigned) {
            classroom_finish_times[d] = A[i].f;
            d++;
        }
    }   

    return d;
}

int lectures_partitioning_heap (lecture_t A[], int n) {
    // O(n*log(n))
    qsort(A, n, sizeof(lecture_t), cmp);

    min_heap_t heap = create_heap(n);

    // O(n*log(d)) 
    for (int i=0; i<n; i++) {
        if (heap_get_size(heap) > 0 && heap_top(heap) <= A[i].s) {
            heap_pop(heap); // O(log(d))
        }
        heap_push(heap, A[i].f); // O(log(d))
    }

    int d = heap_get_size(heap);
    destroy_heap(&heap);
    return d;
}


int cmp (const void *a, const void *b) {
    const lecture_t *l1 = (const lecture_t*) a;
    const lecture_t *l2 = (const lecture_t*) b;
    return l1->s - l2->s;
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
