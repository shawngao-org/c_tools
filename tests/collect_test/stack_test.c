//
// Created by ZetoHkr on 2025/4/14.
//
// TODO

#include "stack_test.h"

#include <assert.h>
#include <tools.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_int_stack() {
    struct stack *int_stack = create_stack(5, sizeof(int));
    const int num1 = 10;
    const int num2 = 20;
    const int num3 = 30;
    const int num4 = 40;
    const int num5 = 50;
    const int num6 = 60;
    push_stack(int_stack, &num1);
    push_stack(int_stack, &num2);
    push_stack(int_stack, &num3);
    push_stack(int_stack, &num4);
    if (is_full_stack(int_stack)) {
        resize_stack(int_stack);
    }
    push_stack(int_stack, &num5);
    push_stack(int_stack, &num6);

    printf("Integer Stack:\n");
    const int *peek_int = (int *) peek_stack(int_stack);
    if (peek_int) printf("Peek: %d\n", *peek_int);

    while (!is_empty_stack(int_stack)) {
        int* popped_int = (int*)pop_stack(int_stack);
        if (popped_int) {
            printf("Popped: %d\n", *popped_int);
            free(popped_int);
        }
    }
    printf("\n");
    destroy_stack(int_stack);
}

void test_int_arr_stack() {
    struct stack *int_arr_stack = create_stack(5, sizeof(int *));
    const int arr1[] = {10, 30};
    const int arr2[] = {20, 40, 60};
    push_stack(int_arr_stack, &arr1);
    push_stack(int_arr_stack, &arr2);
    while (!is_empty_stack(int_arr_stack)) {
        int *popped_int = (int *)pop_stack(int_arr_stack);
        if (popped_int) {
            printf("Popped arr head: %d\n", *popped_int);
            free(popped_int);
        }
    }
    printf("\n");
    destroy_stack(int_arr_stack);
}

void test_float_stack() {
    struct stack *float_stack = create_stack(3, sizeof(float));
    const float f1 = 3.14f;
    const float f2 = 2.718f;
    push_stack(float_stack, &f1);
    push_stack(float_stack, &f2);

    printf("Float Stack:\n");
    const float *peek_float = (float *) peek_stack(float_stack);
    if (peek_float) printf("Peek: %.2f\n", *peek_float);

    while (!is_empty_stack(float_stack)) {
        float* popped_float = (float*)pop_stack(float_stack);
        if (popped_float) {
            printf("Popped: %.2f\n", *popped_float);
            free(popped_float);
        }
    }
    printf("\n");
    destroy_stack(float_stack);
}

void test_string_stack() {
    struct stack *string_stack = create_stack(2, sizeof(char *));
    char *str1 = strdup("Hello");
    char *str2 = strdup("World");
    push_stack(string_stack, &str1);
    push_stack(string_stack, &str2);

    printf("String Stack:\n");
    char **peek_str = (char **) peek_stack(string_stack);
    if (peek_str && *peek_str) printf("Peek: %s\n", *peek_str);

    while (!is_empty_stack(string_stack)) {
        char** popped_str = (char**)pop_stack(string_stack);
        if (popped_str && *popped_str) {
            printf("Popped: %s\n", *popped_str);
            free(*popped_str);
            free(popped_str);
        }
    }
    printf("\n");
    destroy_stack(string_stack);
}

void test_null_stack() {
    printf("Null of Stack:\n");
    struct stack *null_stack = create_stack(2, sizeof(int));
    assert(!peek_stack(null_stack));
    assert(!pop_stack(null_stack));
}

int stack_test() {
    test_int_stack();
    test_float_stack();
    test_string_stack();
    test_null_stack();

    printf("List of int:\n");
    struct list_node *head = NULL;
    struct list_node *head2 = NULL;
    int a = 1;
    create_linked_list(&head, &a);
    create_linked_list(&head2, &a);
    struct list_node *origin_head = head;
    struct list_node *origin_head2 = head2;
    struct list_node *p_head = head;
    struct list_node *p_head2 = head2;
    int b = 2;
    insert_linked_list_in_tail(&head, &b);
    insert_linked_list_in_tail(&head2, &b);
    int c = 3;
    insert_linked_list_in_tail(&head2, &c);
    while (p_head != NULL) {
        printf("%d ", *(int *) p_head->data);
        p_head = p_head->next;
    }
    printf("\n");
    while (p_head2 != NULL) {
        printf("%d ", *(int *) p_head2->data);
        p_head2 = p_head2->next;
    }
    printf("\n");
    struct stack *list_stack = create_stack(2, sizeof(struct list_node *));
    push_stack(list_stack, &origin_head);
    push_stack(list_stack, &origin_head2);
    while (!is_empty_stack(list_stack)) {
        struct list_node **popped_list = (struct list_node **) pop_stack(list_stack);
        if (popped_list) {
            printf("Popped: ");
            struct list_node *p_list = *popped_list;
            while (p_list != NULL) {
                printf("%d ", *(int *) p_list->data);
                p_list = p_list->next;
            }
            printf("\n");
        }
    }
    destroy_linked_list(&head);
    destroy_linked_list(&head2);
    destroy_stack(list_stack);
    test_int_arr_stack();
    return 0;
}
