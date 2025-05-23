#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void *secure_malloc(size_t bytes);

bool same_elements (int* arr1, int* arr2, int size);

#endif
