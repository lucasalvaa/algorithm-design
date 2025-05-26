/**
 * PROBLEM
 * Given a base "a" and an exponent "n", compute a^n
 * with the fewest number of operations.
 */

#include <stdio.h>
#include <stdlib.h>

// Time complexity: O(log(n))
int fast_power (int a, int n) {
    if (n == 1) {
        return a;
    }

    int y = fast_power(a, n/2);
    
    return n % 2 == 0
        ? y*y
        : y*y*a; 
}

//// Test
int main () {
    const int a=5, n=10;
    printf("%d to the power of %d: %d\n", 5, 10, fast_power(a, n));
    return 0;
}