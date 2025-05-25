#include <stdio.h>
#include "utils.h"

void *secure_malloc (size_t bytes) {
    void *p = malloc(bytes);
    if (p == NULL) {
        fprintf(stderr, "malloc failed while requesting %ld bytes\n", bytes);
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return p;
}

void *secure_calloc (int num, size_t size) {
    void *p = calloc(num, size);
    if (p == NULL) {
        fprintf(stderr, "calloc failed while requesting %ld bytes\n", size*num);
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    return p;
}