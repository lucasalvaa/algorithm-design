/**
 * PROBLEM
 *
 * We have a metal tube of length L from which we want to obtain
 * at most n segments of shorter length, having lengths of
 * S[1], S[2], ... , S[n], respectively.
 *
 * The tube is always sawn starting from one of the ends, so each
 * cut reduces its length by the removed measurement. 
 *
 * OUTPUT
 * We want to determine the maximum number of segments that can be obtained.
 */

#include <stdio.h>
#include <stdlib.h>

int cmp (const void* a, const void* b);

int main (void) {
    int S[] = {8, 7, 2, 3, 5};   // tube lengths
    const int n = sizeof(S)/sizeof(S[0]);
    
    int L = 10; // tube length

    // O(n*log(n))
    qsort(S, n, sizeof(int), cmp);

    printf("Segments taken: ");

    // O(n)
    int i = 0;
    while (i < n && L >= S[i]) {
        L -= S[i];
        printf("%d ", S[i]);
        
        i++;
    }
    printf("\n");

    printf("Maximum number of segments that can be obtained: %d\n", i);
    return 0;
}

int cmp (const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}