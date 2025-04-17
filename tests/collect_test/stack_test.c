//
// Created by ZetoHkr on 2025/4/14.
//

#include "collect/stack_tools.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to compare integer data on the stack
static int compare_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

// Test case for create_stack
static void test_create_stack(void **state) {
    struct stack *stack = create_stack(5, sizeof(int));
    assert_non_null(stack);
    assert_int_equal(stack->capacity, 5);
    assert_int_equal(stack->top, -1);
    assert_int_equal(stack->size, sizeof(int));
    assert_non_null(stack->data);
    free(stack->data);
    free(stack);
}

// Test case for is_empty_stack
static void test_is_empty_stack(void **state) {
    struct stack *stack = create_stack(5, sizeof(int));
    assert_true(is_empty_stack(stack));
    int item = 10;
    push_stack(stack, &item);
    assert_false(is_empty_stack(stack));
    pop_stack(stack);
    assert_true(is_empty_stack(stack));
    destroy_stack(stack);
}

// Test case for is_full_stack
static void test_is_full_stack(void **state) {
    struct stack *stack = create_stack(2, sizeof(int));
    assert_false(is_full_stack(stack));
    int item1 = 10, item2 = 20;
    push_stack(stack, &item1);
    assert_false(is_full_stack(stack));
    push_stack(stack, &item2);
    assert_true(is_full_stack(stack));
    destroy_stack(stack);
}

// Test case for resize_stack
static void test_resize_stack(void **state) {
    struct stack *stack = create_stack(2, sizeof(int));
    assert_int_equal(stack->capacity, 2);
    resize_stack(stack);
    assert_int_equal(stack->capacity, 4);
    destroy_stack(stack);
}

// Test case for push_stack
static void test_push_stack(void **state) {
    struct stack *stack = create_stack(2, sizeof(int));
    int item1 = 10, item2 = 20, item3 = 30;

    push_stack(stack, &item1);
    assert_int_equal(stack->top, 0);
    assert_non_null(stack->data[0]);
    assert_int_equal(*(int *)stack->data[0], item1);

    push_stack(stack, &item2);
    assert_int_equal(stack->top, 1);
    assert_non_null(stack->data[1]);
    assert_int_equal(*(int *)stack->data[1], item2);

    push_stack(stack, &item3); // Should trigger resize
    assert_int_equal(stack->top, 2);
    assert_int_equal(stack->capacity, 4);
    assert_non_null(stack->data[2]);
    assert_int_equal(*(int *)stack->data[2], item3);

    destroy_stack(stack);
}

// Test case for pop_stack
static void test_pop_stack(void **state) {
    struct stack *stack = create_stack(3, sizeof(int));
    int item1 = 10, item2 = 20;
    push_stack(stack, &item1);
    push_stack(stack, &item2);

    void *popped_item = pop_stack(stack);
    assert_non_null(popped_item);
    assert_int_equal(*(int *)popped_item, item2);
    free(popped_item);
    assert_int_equal(stack->top, 0);

    popped_item = pop_stack(stack);
    assert_non_null(popped_item);
    assert_int_equal(*(int *)popped_item, item1);
    free(popped_item);
    assert_int_equal(stack->top, -1);

    assert_null(pop_stack(stack)); // Pop from empty stack

    destroy_stack(stack);
}

// Test case for peek_stack
static void test_peek_stack(void **state) {
    struct stack *stack = create_stack(3, sizeof(int));
    assert_null(peek_stack(stack)); // Peek at empty stack

    int item1 = 10, item2 = 20;
    push_stack(stack, &item1);
    assert_non_null(peek_stack(stack));
    assert_int_equal(*(int *)peek_stack(stack), item1);
    assert_int_equal(stack->top, 0); // Top should not change after peek

    push_stack(stack, &item2);
    assert_non_null(peek_stack(stack));
    assert_int_equal(*(int *)peek_stack(stack), item2);
    assert_int_equal(stack->top, 1); // Top should not change after peek

    destroy_stack(stack);
}

// Test case for destroy_stack
static void test_destroy_stack(void **state) {
    struct stack *stack = create_stack(3, sizeof(int));
    int item1 = 10, item2 = 20;
    push_stack(stack, &item1);
    push_stack(stack, &item2);

    destroy_stack(stack);
    // After destroy_stack, the pointer 'stack' is still valid but the memory it points to is freed.
    // We can't safely access its members to assert NULL.
    // The test's success is primarily about not having memory leaks (which cmocka helps detect).
}

void stack_test() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_stack),
        cmocka_unit_test(test_is_empty_stack),
        cmocka_unit_test(test_is_full_stack),
        cmocka_unit_test(test_resize_stack),
        cmocka_unit_test(test_push_stack),
        cmocka_unit_test(test_pop_stack),
        cmocka_unit_test(test_peek_stack),
        cmocka_unit_test(test_destroy_stack),
    };
    cmocka_run_group_tests(tests, NULL, NULL);
}
