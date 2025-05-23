#include "minheap.h"
#include <stdio.h>
#include <stdlib.h>

struct min_heap {
    int *data;
    int size;
    int capacity;
};


static void heapify_up (min_heap_t heap, int idx);

static void heapify_down (min_heap_t heap, int idx);

static void *secure_malloc (size_t bytes);


min_heap_t create_heap (int capacity) {
    min_heap_t heap = secure_malloc(sizeof(struct min_heap));
    heap->data = secure_malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void heap_push (min_heap_t heap, int value) {
    heap->data[heap->size++] = value;
    heapify_up(heap, heap->size - 1);
}

int heap_pop (min_heap_t heap) {
    int top = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapify_down(heap, 0);
    return top;
}

int heap_top (min_heap_t heap) {
    return heap->data[0];
}

bool heap_is_empty (min_heap_t heap) {
    return heap->size == 0;
}

int heap_get_size (min_heap_t heap) {
    return heap->size;
}

void destroy_heap (min_heap_t *heap_ptr) {
    min_heap_t heap = *heap_ptr;
    free(heap->data);
    *heap_ptr = NULL;
}

static void heapify_up (min_heap_t heap, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap->data[parent] <= heap->data[idx]) break;
        int tmp = heap->data[parent];
        heap->data[parent] = heap->data[idx];
        heap->data[idx] = tmp;
        idx = parent;
    }
}

static void heapify_down (min_heap_t heap, int idx) {
    while (2 * idx + 1 < heap->size) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = left;

        if (right < heap->size && heap->data[right] < heap->data[left])
            smallest = right;

        if (heap->data[idx] <= heap->data[smallest]) break;

        int tmp = heap->data[idx];
        heap->data[idx] = heap->data[smallest];
        heap->data[smallest] = tmp;
        idx = smallest;
    }
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
