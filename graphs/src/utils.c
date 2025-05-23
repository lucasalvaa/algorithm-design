#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

static int cmp(const void *a, const void *b);

void *secure_malloc(size_t bytes) {
    void *p = malloc(bytes);
    if (p == NULL) {
        fprintf(stderr, "malloc failed while requesting %ld bytes\n", bytes);
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return p;
}

bool same_elements (int* arr1, int *arr2, int size) {
    qsort(arr1, size, sizeof(int), cmp);
    qsort(arr2, size, sizeof(int), cmp);
    return memcmp(arr1, arr2, size * sizeof(int)) == 0;
}


static int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
