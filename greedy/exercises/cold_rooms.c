/**
 * PROBLEM
 *
 * Let A be a set of n items. Each of them must be stored and
 * kept in the appropriate temperature range [s_i, f_i], i = 1, ... , n
 *
 * OUTPUT
 * We need to compute the minimum number of cold rooms r in which
 * we can store the objects.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
   char name;
   int s;
   int f;
} item_t;

int cmp (const void* a, const void* b);

int main () {
    item_t A[] = {
        {'a', 1, 4},
        {'b', 2, 5},
        {'c', 3, 6},
        {'d', 7, 9},
        {'e', 8, 10}
    };

    const int n = sizeof(A)/sizeof(A[0]);
    
    int r = 0;
    
    // O(n*log(n))
    qsort(A, n, sizeof(item_t), cmp);

    int lf = 0; // last finish time chosen
    // O(n)
    for (int i=0; i<n; i++) {
        if (lf < A[i].s) {
            lf = A[i].f;
            r++;
        }
    }

    printf("Just %d rooms are required\n", r);
}

int cmp (const void* a, const void* b) {
    return ((item_t*) a)->f - ((item_t*) b)->f;    
}
