#include <stdio.h>

int square_root (int n) {
    if (n==0 || n==1) {
        return n;
    }

    int root;       // result of the computation

    int l = 1;      // left
    int r = n/2;    // right
    int c;          // center

    while (l <= r) {
        c = (l+r)/2;
        if (c*c == n) {
            return c;
        }

        if (c*c < n) {
            l = c+1;
            root = c;
        }
        else {
            r = c-1;
        }
    }
    
    return root;
}

//// Test
int main () {
    for (int i=0; i<=25; i++) {
        printf("Square root of %d: %d\n", i, square_root(i));
    }
}