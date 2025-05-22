#ifndef QUEUE 
#define QUEUE

#include <stdbool.h>

typedef struct queue* queue_t;

queue_t create_queue (int capacity);

bool queue_is_empty (queue_t queue);

bool queue_enqueue (queue_t queue, int elem);

bool queue_dequeue (queue_t queue, int *output);

void destroy_queue (queue_t* queue_ptr);

#endif