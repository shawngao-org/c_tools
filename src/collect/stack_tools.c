//
// Created by ZetoHkr on 2025/4/14.
//

#include "collect/stack_tools.h"

struct stack *create_stack(int init_capacity, size_t size) {
    struct stack *stack = (struct stack *) malloc(sizeof(struct stack));
    if (stack == NULL) {
        perror("Failed to allocate stack.");
        exit(EXIT_FAILURE);
    }
    stack->capacity = init_capacity;
    stack->top = -1;
    stack->size = size;
    stack->data = (void **) malloc(stack->capacity * sizeof(void *));
    if (stack->data == NULL) {
        perror("Failed to allocate stack data.");
        free(stack);
        exit(EXIT_FAILURE);
    }
    return stack;
}

int is_empty_stack(struct stack *stack) {
    return stack->top == -1;
}

int is_full_stack(struct stack *stack) {
    return stack->top == stack->capacity - 1;
}

void resize_stack(struct stack *stack) {
    stack->capacity *= 2;
    void **new_data = (void **) realloc(stack->data, stack->capacity * sizeof(void *));
    if (new_data == NULL) {
        perror("Failed to reallocate stack data.");
        exit(EXIT_FAILURE);
    }
    stack->data = new_data;
}

void push_stack(struct stack *stack, const void *item) {
    if (is_full_stack(stack)) {
        resize_stack(stack);
    }
    stack->top++;
    stack->data[stack->top] = malloc(stack->size);
    if (stack->data[stack->top] == NULL) {
        perror("Failed to allocate memory.");
        exit(EXIT_FAILURE);
    }
    memcpy(stack->data[stack->top], item, stack->size);
}

void *pop_stack(struct stack *stack) {
    if (is_empty_stack(stack)) {
        return NULL;
    }
    void *item = stack->data[stack->top];
    stack->top--;
    return item;
}

void *peek_stack(struct stack *stack) {
    if (is_empty_stack(stack)) {
        return NULL;
    }
    return stack->data[stack->top];
}

void destroy_stack(struct stack *stack) {
    if (stack) {
        if (stack->data) {
            for (int i = 0; i <= stack->top; i++) {
                free(stack->data[i]);
            }
            free(stack->data);
        }
        free(stack);
    }
}
