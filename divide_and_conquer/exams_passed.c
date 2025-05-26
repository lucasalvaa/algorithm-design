/**
 * PROBLEM
 * Given a set of exam grades, calculate how many students passed the exam.
 * In other words, we need to calculate the number of students
 * who have obtained a grade greater than or equal to a threshold k.
 */

#include <stdio.h>
#include <stdlib.h>

// Brute force solution
int promoted_linear_counter (int arr[], int n, int k)

// Divide and conquer solution
int promoted_logarithmic_counter (int arr[], int k, int i, int j);

int cmp (const void* a, const void* b);

//// Test

int main (void) {
    int grades[] = {27, 26, 28, 30, 27, 14, 17, 9, 30, 30, 24, 1};
    const int n = sizeof(grades) / sizeof(grades[0]);
    const int k = 18;

    // If the array is not sorted, it must be sorted before running the algorithm.
    // This operation increases the total complexity to O(n*log(n)).
    qsort(grades, n, sizeof(int), cmp);

    int a = promoted_linear_counter(grades, n, k);
    int b = promoted_logarithmic_counter(grades, k, 0, n-1);

    printf("Number of promoted students:\n");
    printf("Linear algorithm says %d\n", a);
    printf("Divide and conquer algorithm says %d\n", b);
}

//// Brute force solution

// Time complexity: O(n)

int promoted_linear_counter (int arr[], int n, int k) {
    int i=0;
    for (i<0; i<n && arr[i]<k; i++);
    return n-i;
} 

//// Divide and conquer solution

// Time complexity: O(log(n))

// Reccurence relation is the same as the binary search.
// You can find the calculus in the binary_search.c file.

int promoted_logarithmic_counter (int arr[], int k, int i, int j) {
    if (i>j) {
        return 0;
    }

    int m = (i+j)/2;
    
    return arr[m] < k
        ? promoted_logarithmic_counter(arr, k, m+1, j)
        : (j-m+1) + promoted_logarithmic_counter(arr, k, i, m-1);
}

////

int cmp (const void* a, const void* b) {
    return *(int*)a - *(int*) b;
}
