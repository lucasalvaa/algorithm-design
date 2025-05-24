#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name;
    int v;  // value
    int w;  // weight
} item_t;

// O(n*log(n))
double* fractional_knapsack (item_t* items, const int n, const int W);

int cmp (const void* a, const void *b);

int main () {
    const int W = 50; // total weight capacity
    item_t items[] = {
        {'a', 60, 10}, 
        {'b', 100, 20}, 
        {'c', 120, 30}
    };
    const int n = sizeof(items) / sizeof(item_t);

    double* knapsack = fractional_knapsack(items, n, W);
    double total_value = 0;
    printf("Items taken (fractions):\n");
    for (int i=0; i<n; i++) {
        if (knapsack[i] > 0) {
            printf("Item %c: %.2f (value: %.2f)\n", items[i].name, knapsack[i], knapsack[i] * items[i].v);
            total_value += knapsack[i] * items[i].v;
        }
    }
    printf("Total value: %.2f\n", total_value);
    return 0;
}

double* fractional_knapsack (item_t* items, const int n, const int W) {
    // O(n log(n))
    qsort(items, n, sizeof(item_t), cmp);
    
    // The array x will contain the weights of each item put in the knapsack
    double *x = calloc(n, sizeof(double)); 
    double cap = W; // remaining capacity

    // O(n)
    for (int j=0; j<n && cap > 0; j++) {
        if (items[j].w <= cap) {
            x[j] = 1;
        }
        else {
            x[j] = cap / items[j].w;
        }

        cap -= x[j] * items[j].w;
    }

    return x;
}

int cmp(const void* a, const void* b) {
    item_t i = *(item_t*)a;
    item_t j = *(item_t*)b;
    double r1 = (double)i.v / i.w;
    double r2 = (double)j.v / j.w;
    return (r1 < r2) ? 1 : (r1 > r2) ? -1 : 0;
}