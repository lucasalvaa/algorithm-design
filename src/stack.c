#include "stack.h"
#include "utils.h"

struct node {
    int value;
    struct node* next;
};

typedef struct node* node_t;

static struct node* create_node (int value, struct node* next);

struct stack {
    node_t top;
    int size;
};

stack_t create_stack () {
    stack_t stack = secure_malloc(sizeof(struct stack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

bool stack_is_empty (stack_t stack) {
    return stack == NULL || stack->size == 0;
}

bool stack_push (stack_t stack, int value) {
    if (stack == NULL) {
        perror("stack_push");
        fprintf(stderr, "Push operation attempted on an invalid stack\n");
        return false;
    }

    stack->top = create_node(value, stack->top);
    stack->size++;
    return true;
}

bool stack_pop (stack_t stack) {
    if (stack == NULL) {
        perror("stack_pop");
        fprintf(stderr, "Pop operation attempted on an invalid stack\n");
        return false;
    }

    if (stack_is_empty(stack)) {
        return false;
    }

    node_t to_remove = stack->top;
    stack->top = to_remove->next;
    free(to_remove);
    stack->size--;
    return true;
}

int stack_top (stack_t stack) {
    if (stack_is_empty(stack)) {
        perror("stack_top");
        fprintf(stderr, "Top operation attempted on an empty or invalid stack\n");
        exit(EXIT_FAILURE);
    }

    return stack->top->value;
}

void destroy_stack (stack_t* stack_ptr) {
    if (stack_ptr == NULL || *stack_ptr == NULL) {
        return;
    }

    stack_t stack = *stack_ptr;

    while(!stack_is_empty(stack)) {
        stack_pop(stack);
    }

    free(stack);
    *stack_ptr = NULL;
}

static struct node* create_node (int value, struct node* next) {
    node_t new_node = secure_malloc(sizeof(struct node));
    new_node->value = value;
    new_node->next = next;
    return new_node;
}



