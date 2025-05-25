#include "minheap.h"
#include "utils.h"
#include <stdio.h>

typedef struct {
    void *data;   
    int priority;
} heap_node_t;

struct min_heap {
    heap_node_t *nodes;
    int size;
    int capacity;
};

static void heapify_up (min_heap_t heap, int i);

static void heapify_down (min_heap_t heap, int i);

static bool heap_is_empty (min_heap_t heap);

static bool heap_is_full (min_heap_t heap);

static void swap (heap_node_t* a, heap_node_t* b);


min_heap_t create_heap (int capacity) {
    min_heap_t heap = secure_malloc(sizeof(struct min_heap));
    heap->nodes = secure_malloc(sizeof(heap_node_t) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// heap-insert
void heap_push (min_heap_t heap, void* data, int priority) {
    if (heap == NULL) {
        fprintf(stderr, "Push operation attempted on an invalid heap\n");
        exit(EXIT_FAILURE);
    } 
    
    if (heap_is_full(heap)) {
        fprintf(stderr, "Push operation attempted on a completely full heap\n");
        exit(EXIT_FAILURE);
    }

    int i = heap->size;
    heap->nodes[i].data = data;
    heap->nodes[i].priority = priority;
    heap->size++;
    heapify_up(heap, i); // O(log(n))
}


// heap-extract-min
void* heap_pop (min_heap_t heap) {
    if (heap == NULL) {
        fprintf(stderr, "Pop operation attempted on an invalid heap\n");
        exit(EXIT_FAILURE);
    } 
    
    if (heap_is_empty(heap)) {
        fprintf(stderr, "Pop operation attempted on an empty heap\n");
        exit(EXIT_FAILURE);
    }

    void* top = heap->nodes[0].data;
    heap->nodes[0] = heap->nodes[--heap->size];
    heapify_down(heap, 0); // O(log(n))
    return top;
}


void* heap_top (min_heap_t heap) {
    if (heap == NULL) {
        fprintf(stderr, "Top operation attempted on an invalid heap\n");
        exit(EXIT_FAILURE);
    } 
    
    if (heap_is_empty(heap)) {
        fprintf(stderr, "Top operation attempted on an empty heap\n");
        exit(EXIT_FAILURE);
    }
    
    return heap->nodes[0].data;
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
        heap_push(heap, &arr[i], arr[i]);
    }

    // Total time complexity: O(n*log(n))
    // Loop: O(n)
    for (int i=0; i<n; i++) {
        // Heap pop: O(log(n))
        arr[i] = *(int*) heap_pop(heap);
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
    free(heap->nodes);
    *heap_ptr = NULL;
}


// O(log(n))
static void heapify_up (min_heap_t heap, int i) {
    int parent;
    while (i > 0) {
        parent = (i-1)/2;
        if (heap->nodes[parent].priority <= heap->nodes[i].priority) {
            return;
        }
        swap(&heap->nodes[i], &heap->nodes[parent]);
        i = parent;
    }
}


// O(log(n))
static void heapify_down (min_heap_t heap, int i) {
    while (2*i+1 < heap->size) {
        int left = 2*i+1;
        int right = 2*i+2;
        heap_node_t left_node = heap->nodes[left];
        heap_node_t right_node = heap->nodes[right];
        int min = left;

        if (right < heap->size && right_node.priority < left_node.priority) {
            min = right;
        }

        if (heap->nodes[i].priority <= heap->nodes[min].priority) {
            return;
        }

        swap(&heap->nodes[i], &heap->nodes[min]);
        i = min;
    }
}


static bool heap_is_empty (min_heap_t heap) {
    return heap->size == 0;
}


static bool heap_is_full (min_heap_t heap) {
    return heap->size >= heap->capacity;
}


static void swap (heap_node_t* a, heap_node_t* b) {
    heap_node_t tmp = *a;
    *a = *b;
    *b = tmp; 
}
