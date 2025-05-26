/**
 * Input
 * A set of n songs, each of which has a duration d.
 * A CD with a time capacity D.
 *
 * Output
 * The maximum number m of songs we can store on the CD.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
   int j;
   int d;
} song_t;

int cmp (const void* a, const void* b);

int main (void) {

    //// Input

    song_t songs[] = {
        {1, 180}, {2, 140},
        {3, 200}, {4, 150},
        {5, 210}, {6, 156},
        {7, 170}
    };

    const int n = sizeof(songs)/sizeof(songs[0]);

    int D = 500;

    //// Computation

    song_t CD[n];
    int m = 0;

    // O(n*log(n))
    qsort(songs, n, sizeof(song_t), cmp);

    // O(n)
    for (int i=0; i<n; i++) {
        if (songs[i].d <= D) {
            D -= songs[i].d;
            CD[m] = songs[i];
            m++;
        }
    } 

    //// Output

    printf("The maximum amount of songs that the CD can contain is %d\n", m);
    printf("Songs stored in the CD:\n");
    for (int i=0; i<m; i++) {
        printf("%d) No %d, duration: %d\n", i+1, CD[i].j, CD[i].d);
    }

    return 0;    
}

int cmp (const void* a, const void* b) {
    return ((song_t*) a)->d - ((song_t*) b)->d;
}