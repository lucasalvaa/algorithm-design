/**
 * PROBLEM
 * Given a sequence "a" of n numbers, calculate the amount 
 * of pairs (a[i], a[i+1]) for which a[i] = a[i+1].
 */

#include <stdio.h>

// Time complexity: O(n)
// The recurrence relation is at the bottom of this file
int identical_pairs (int a[], int i, int j) {
    if (j == i+1) {
        return a[i] == a[j];
    }

    int c = (i+j)/2;

    return identical_pairs(a, i, c) + identical_pairs(a, c, j);
}

//// Test

int main () {
    int a[] = {2, 4, 4, 1, 5, 6, 1, 1, 1, 8, 9, 10, 10, 1};
    const int n = sizeof(a) / sizeof(a[0]);
    
    printf("Number of identical pairs (a[i] = a[i+1]): %d\n", identical_pairs(a, 0, n-1));
}

//// Time complexity

// T(n):
// - c                 if n <= 2
// - 2*T(n/2) + k      if n > 2

// T(n) = 2*T(n/2) + k
//      = 2*(2*T(n/4) + k) + k
//      = 4*T(n/4) + 2k + k
//      = 4*(2*T(n/8) + k) + 2k + k
//      = 8*T(n/8) + 4k + 2k + k
//      = ...
//      = 2^i * T(n/2^i) + [2^i -1]*k

// T(n/2^i) = T(1) <=> n/2^i = 1 <=> i = log_2(n)

// T(n) = n * T(1) + (n-1)*k 
//      = n*c + (n-1)*c 
//      => T(n) = O(n)