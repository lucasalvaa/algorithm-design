#include "queue.h"
#include "utils.h"

struct queue {
    int *arr;
    int front, size;
    int capacity;
};

queue_t create_queue (int capacity) {
    if (capacity <= 0) {
        perror("create_queue");
        fprintf(stderr, "Invalid input for queue capacity: %d\n", capacity);
        exit(EXIT_FAILURE);
    }

    queue_t queue = secure_malloc(sizeof(struct queue));
    queue->arr = secure_malloc(sizeof(int) * capacity);
    queue->front = 0;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

bool queue_is_empty (queue_t queue) {
    return queue == NULL || queue->size == 0;
}

bool queue_enqueue (queue_t queue, int elem) {
    if (queue->size == queue->capacity) {
        return false;
    }

    int rear = (queue->front + queue->size) % queue->capacity;
    queue->arr[rear] = elem;
    queue->size++;
    return true;
}

bool queue_dequeue (queue_t queue, int *output) {
    if (queue->size == 0) {
        perror("queue_dequeue");
        fprintf(stderr, "Dequeue operation attempted on an empty queue\n");
        return false;
    }

    *output = queue->arr[queue->front];
    queue->front = (queue->front+1) % queue->capacity;
    queue->size--;
    return true;
}

void destroy_queue(queue_t* queue_ptr) {
    if (queue_ptr == NULL || *queue_ptr == NULL) {
        return;
    }

    queue_t queue = *queue_ptr;

    free(queue->arr);
    free(queue);
    *queue_ptr = NULL;
}