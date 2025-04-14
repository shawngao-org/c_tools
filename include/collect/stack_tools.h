//
// Created by ZetoHkr on 2025/4/14.
//

#ifndef TOOLS_STACK_TOOLS_H
#define TOOLS_STACK_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack {
    void **data;
    int top;
    int capacity;
    size_t size;
};

struct stack *create_stack(int initialCapacity, size_t elementSize);
int is_empty_stack(struct stack *stack);
int is_full_stack(struct stack *stack);
void resize_stack(struct stack *stack);
void push_stack(struct stack *stack, const void *item);
void *pop_stack(struct stack *stack);
void *peek_stack(struct stack *stack);
void destroy_stack(struct stack *stack);

#endif //TOOLS_STACK_TOOLS_H
