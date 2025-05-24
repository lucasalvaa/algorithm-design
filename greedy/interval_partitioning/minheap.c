#include "minheap.h"
#include <stdio.h>
#include <stdlib.h>

struct min_heap {
    int *data;
    int size;
    int capacity;
};

static void heapify_up (min_heap_t heap, int i);

static void heapify_down (min_heap_t heap, int i);

static bool heap_is_empty (min_heap_t heap);

static bool heap_is_full (min_heap_t heap);

static void swap (int *a, int *b);

static void *secure_malloc (size_t bytes);


min_heap_t create_heap (int capacity) {
    min_heap_t heap = secure_malloc(sizeof(struct min_heap));
    heap->data = secure_malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}


// heap-insert
void heap_push (min_heap_t heap, int value) {
    if (heap == NULL) {
        fprintf(stderr, "Push operation attempted on an invalid heap\n");
        exit(EXIT_FAILURE);
    } 
    
    if (heap_is_full(heap)) {
        fprintf(stderr, "Push operation attempted on a completely full heap\n");
        exit(EXIT_FAILURE);
    }

    heap->data[heap->size] = value;
    heapify_up(heap, heap->size); // O(log(n))
    heap->size++;
}


// heap-extract-min
int heap_pop (min_heap_t heap) {
    if (heap == NULL) {
        fprintf(stderr, "Pop operation attempted on an invalid heap\n");
        exit(EXIT_FAILURE);
    } 
    
    if (heap_is_empty(heap)) {
        fprintf(stderr, "Pop operation attempted on an empty heap\n");
        exit(EXIT_FAILURE);
    }

    int top = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapify_down(heap, 0); // O(log(n))
    return top;
}


int heap_top (min_heap_t heap) {
    if (heap == NULL) {
        fprintf(stderr, "Top operation attempted on an invalid heap\n");
        exit(EXIT_FAILURE);
    } 
    
    if (heap_is_empty(heap)) {
        fprintf(stderr, "Top operation attempted on an empty heap\n");
        exit(EXIT_FAILURE);
    }
    
    return heap->data[0];
}


void heap_sort (int *arr, int n) {
    if (arr == NULL || n <= 0) {
        fprintf(stderr, "Heap sort attempted for an empty array\n");
    }

    min_heap_t heap = create_heap(n);
    
    // Total time complexity: O(n*log(n))
    // Loop: O(n)
    for (int i=0; i<n; i++) {
        // Heap push: O(log(n))
        heap_push(heap, arr[i]);
    }

    // Total time complexity: O(n*log(n))
    // Loop: O(n)
    for (int i=0; i<n; i++) {
        // Heap pop: O(log(n))
        arr[i] = heap_pop(heap);
    }

    destroy_heap(&heap);
}

int heap_get_size (min_heap_t heap) {
    if (heap == NULL) {
        fprintf(stderr, "Operation attempted on an invalid heap\n");
        exit(EXIT_FAILURE);
    } 
    return heap->size;
}


void destroy_heap (min_heap_t *heap_ptr) {
    min_heap_t heap = *heap_ptr;
    free(heap->data);
    *heap_ptr = NULL;
}


// O(log(n))
static void heapify_up (min_heap_t heap, int i) {
    int parent;
    while (i > 0) {
        parent = (i-1)/2;
        if (heap->data[parent] <= heap->data[i]) {
            return;
        }
        swap(&heap->data[i], &heap->data[parent]);
        i = parent;
    }
}


// O(log(n))
static void heapify_down (min_heap_t heap, int i) {
    while (2*i+1 < heap->size) {
        int left = 2*i+1;
        int right = 2*i+2;
        int min = left;

        if (right < heap->size && heap->data[right] < heap->data[left]) {
            min = right;
        }

        if (heap->data[i] <= heap->data[min]) {
            return;
        }

        swap(&heap->data[i], &heap->data[min]);
        i = min;
    }
}


static bool heap_is_empty (min_heap_t heap) {
    return heap->size == 0;
}


static bool heap_is_full (min_heap_t heap) {
    return heap->size == heap->capacity;
}


static void swap (int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp; 
}


static void *secure_malloc (size_t bytes) {
    void *p = malloc(bytes);
    if (p == NULL) {
        fprintf(stderr, "malloc failed while requesting %ld bytes\n", bytes);
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return p;
}
