//
// Created by ZetoHkr on 2025/4/14.
//

#ifndef TOOLS_STACK_TOOLS_H
#define TOOLS_STACK_TOOLS_H

#include "tools.h"

struct stack *create_stack(int init_capacity, size_t size);
int is_empty_stack(const struct stack *stack);
int is_full_stack(const struct stack *stack);
void resize_stack(struct stack *stack);
void push_stack(struct stack *stack, const void *item);
void *pop_stack(struct stack *stack);
void *peek_stack(const struct stack *stack);
void destroy_stack(struct stack *stack);

#endif //TOOLS_STACK_TOOLS_H
