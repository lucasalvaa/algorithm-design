#ifndef STACK 
#define STACK

#include <stdbool.h>

typedef struct stack* stack_t;

stack_t create_stack ();

bool stack_is_empty (stack_t stack);

bool stack_push (stack_t stack, int value);

bool stack_pop (stack_t stack);

int stack_top (stack_t stack);

void destroy_stack (stack_t* stack_ptr);

#endif