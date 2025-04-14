//
// Created by ZetoHkr on 2025/4/14.
//

#include "stack_test.h"
#include <tools.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stack_test() {
    struct stack *int_stack = create_stack(5, sizeof(int));
    int num1 = 10, num2 = 20, num3 = 30;
    push_stack(int_stack, &num1);
    push_stack(int_stack, &num2);
    push_stack(int_stack, &num3);

    printf("Integer Stack:\n");
    int *peek_int = (int *) peek_stack(int_stack);
    if (peek_int) printf("Peek: %d\n", *peek_int);

    int *popped_int;
    while (!is_empty_stack(int_stack)) {
        popped_int = (int *) pop_stack(int_stack);
        if (popped_int) {
            printf("Popped: %d\n", *popped_int);
            free(popped_int); // 释放 pop 返回的内存
        }
    }
    destroy_stack(int_stack);

    printf("\n");

    struct stack *float_stack = create_stack(3, sizeof(float));
    float f1 = 3.14f, f2 = 2.718f;
    push_stack(float_stack, &f1);
    push_stack(float_stack, &f2);

    printf("Float Stack:\n");
    float *peek_float = (float *) peek_stack(float_stack);
    if (peek_float) printf("Peek: %.2f\n", *peek_float);

    float *popped_float;
    while (!is_empty_stack(float_stack)) {
        popped_float = (float *) pop_stack(float_stack);
        if (popped_float) {
            printf("Popped: %.2f\n", *popped_float);
            free(popped_float);
        }
    }
    destroy_stack(float_stack);

    printf("\n");

    struct stack *string_stack = create_stack(2, sizeof(char *));
    char *str1 = strdup("Hello");
    char *str2 = strdup("World");
    push_stack(string_stack, &str1);
    push_stack(string_stack, &str2);

    printf("String Stack:\n");
    char **peek_str = (char **) peek_stack(string_stack);
    if (peek_str && *peek_str) printf("Peek: %s\n", *peek_str);

    char **popped_str;
    while (!is_empty_stack(string_stack)) {
        popped_str = (char **) pop_stack(string_stack);
        if (popped_str && *popped_str) {
            printf("Popped: %s\n", *popped_str);
            free(*popped_str);
            free(popped_str);
        }
    }
    destroy_stack(string_stack);

    return 0;
}
