/**
 * PROBLEM
 * Given an array sorted in ascending order and a target value t,
 * we need to implement a function that returns the index of t in the array.
 * If the array doesn't contain the target, the function should return -1;
 */

#include <stdio.h>

/**
 * @brief Search the index of the target value t in the array arr
 *
 * This algorithm uses a divide-and-conquer approach to search
 * a target element into an array with time complexity equals to O(log(n)).
 *
 * @param arr The array in which we need to search for the target
 * @param t Target (the value we are looking for)
 * @param i The starting index of the current search interval
 * @param j The ending index of the current search interval
 *
 * @return The index of the target value in the array arr (-1 if arr doesn't contain t)
 */
int binary_search (int arr[], int t, int i, int j);

int main () {
    int arr[] = {1, 2, 4, 5, 8, 10, 18, 20, 25, 38};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Array: ");
    for (int i=0; i<n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int target = 5;
    int index = binary_search(arr, target, 0, n-1);

    if (index == -1) {
        printf("The array doesn't contain the target %d\n", target);
    }
    else {
        printf("Target %d found at position %d\n", target, index);
    }

}

int binary_search (int arr[], int t, int i, int j) {
    if (i > j) {
        return -1;
    }

    int c = (i+j)/2;

    if (arr[c] == t) {
        return c;
    }

    return t < arr[c]
        ? binary_search(arr, t, i, c-1)
        : binary_search(arr, t, c+1, j);
}

//  Time complexity calculus
//  T(n):
//  - c             if n=1
//  - T(n/2) + k    if n>1

// T(n) = T(n/2) + k
//      = (T(n/4) + k) + k
//      = ...
//      = T(n/2^i) + i*k

//  Basis step
//  n/2^i = 1 <=> n = 2^1 <=> log_2(n) = i

//  T(n) = c + k*log_2(n) => T(n) = O(log(n))