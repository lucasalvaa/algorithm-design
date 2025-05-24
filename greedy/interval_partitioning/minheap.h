#include <stdbool.h>

typedef struct min_heap* min_heap_t;

min_heap_t create_heap (int capacity);

void destroy_heap (min_heap_t *heap_ptr);

// Time complexity: O(1)
int heap_get_size (min_heap_t heap);

// Time complexity: O(log(n))
void heap_push (min_heap_t heap, int value);

// Time complexity: O(log(n))
int heap_pop (min_heap_t heap);

// Time complexity: O(1)
int heap_top (min_heap_t heap);

// Time complexity: O(n*log(n))
void heap_sort (int *arr, int n);

