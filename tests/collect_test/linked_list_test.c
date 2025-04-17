//
// Created by ZetoHkr on 2025/4/16.
//

#include "linked_list_test.h"
#include "collect/linked_list_tools.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>

// Helper function to compare integer data in list nodes
static int compare_int_data(const struct list_node *node, const int *expected) {
    if (node == NULL || node->data == NULL) {
        return 0; // Consider NULL as not matching
    }
    return (*(int *)node->data == *expected);
}

// Test case for new_list_node
static void test_new_list_node(void **state) {
    int data = 10;
    struct list_node *prev_node = (struct list_node *)malloc(sizeof(struct list_node));
    struct list_node *next_node = (struct list_node *)malloc(sizeof(struct list_node));
    struct list_node *new_node = new_list_node(prev_node, next_node, &data);

    assert_non_null(new_node);
    assert_ptr_equal(new_node->data, &data);
    assert_ptr_equal(new_node->prev, prev_node);
    assert_ptr_equal(new_node->next, next_node);

    free(prev_node);
    free(next_node);
    free(new_node);
}

// Test case for create_linked_list
static void test_create_linked_list(void **state) {
    struct list_node *head = NULL;
    int data = 20;
    create_linked_list(&head, &data);

    assert_non_null(head);
    assert_ptr_equal(head->data, &data);
    assert_null(head->prev);
    assert_null(head->next);

    destroy_linked_list(&head);
}

// Test case for is_empty_linked_list
static void test_is_empty_linked_list(void **state) {
    struct list_node *head = NULL;
    assert_true(is_empty_linked_list(head));

    int data = 30;
    create_linked_list(&head, &data);
    assert_false(is_empty_linked_list(head));

    destroy_linked_list(&head);
}

// Test case for get_linked_list_length
static void test_get_linked_list_length(void **state) {
    struct list_node *head = NULL;
    assert_int_equal(get_linked_list_length(&head), 0);

    int data1 = 40, data2 = 50, data3 = 60;
    create_linked_list(&head, &data1);
    assert_int_equal(get_linked_list_length(&head), 1);

    head = insert_linked_list_in_tail(&head, &data2);
    assert_int_equal(get_linked_list_length(&head), 2);

    head = insert_linked_list_in_tail(&head, &data3);
    assert_int_equal(get_linked_list_length(&head), 3);

    destroy_linked_list(&head);
}

// Test case for insert_linked_list_in_head
static void test_insert_linked_list_in_head(void **state) {
    struct list_node *head = NULL;
    int data1 = 70, data2 = 80;

    head = insert_linked_list_in_head(&head, &data1);
    assert_non_null(head);
    assert_ptr_equal(head->data, &data1);
    assert_null(head->prev);
    assert_null(head->next);

    head = insert_linked_list_in_head(&head, &data2);
    assert_non_null(head);
    assert_ptr_equal(head->data, &data2);
    assert_null(head->prev);
    assert_non_null(head->next);
    assert_ptr_equal(head->next->data, &data1);
    assert_ptr_equal(head->next->prev, head);
    assert_null(head->next->next);

    destroy_linked_list(&head);
}

// Test case for insert_linked_list_by_index
static void test_insert_linked_list_by_index(void **state) {
    struct list_node *head = NULL;
    int data1 = 90, data2 = 100, data3 = 110, data4 = 120;

    // Insert into empty list
    head = insert_linked_list_by_index(&head, &data1, 0);
    assert_non_null(head);
    assert_ptr_equal(head->data, &data1);
    assert_null(head->prev);
    assert_null(head->next);

    // Insert at the beginning
    head = insert_linked_list_by_index(&head, &data2, 0);
    assert_non_null(head);
    assert_ptr_equal(head->data, &data2);
    assert_null(head->prev);
    assert_non_null(head->next);
    assert_ptr_equal(head->next->data, &data1);
    assert_ptr_equal(head->next->prev, head);
    assert_null(head->next->next);

    // Insert at the end
    head = insert_linked_list_by_index(&head, &data3, 2);
    assert_non_null(head->next->next);
    assert_ptr_equal(head->next->next->data, &data3);
    assert_ptr_equal(head->next->next->prev, head->next);
    assert_null(head->next->next->next);

    // Insert in the middle
    struct list_node *temp_head = head; // Keep track of the original head
    head = temp_head;
    head = insert_linked_list_by_index(&head, &data4, 1);
    assert_ptr_equal(head->data, &data2);
    assert_ptr_equal(head->next->data, &data4);
    assert_ptr_equal(head->next->prev, head);
    assert_ptr_equal(head->next->next->data, &data1);
    assert_ptr_equal(head->next->next->prev, head->next);
    assert_ptr_equal(head->next->next->next->data, &data3);
    assert_ptr_equal(head->next->next->next->prev, head->next->next);
    assert_null(head->next->next->next->next);

    // Insert with out-of-range negative index
    temp_head = head;
    head = temp_head;
    struct list_node *original_head_negative = head;
    head = insert_linked_list_by_index(&head, &data1, -1);
    assert_ptr_equal(head, original_head_negative);

    destroy_linked_list(&head);
}

// Test case for insert_linked_list_in_tail
static void test_insert_linked_list_in_tail(void **state) {
    struct list_node *head = NULL;
    int data1 = 130, data2 = 140, data3 = 150;

    head = insert_linked_list_in_tail(&head, &data1);
    assert_non_null(head);
    assert_ptr_equal(head->data, &data1);
    assert_null(head->prev);
    assert_null(head->next);

    head = insert_linked_list_in_tail(&head, &data2);
    assert_non_null(head);
    const struct list_node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    assert_ptr_equal(current->data, &data2);
    assert_ptr_equal(current->prev->data, &data1);
    assert_null(current->next);

    head = insert_linked_list_in_tail(&head, &data3);
    current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    assert_ptr_equal(current->data, &data3);
    assert_ptr_equal(current->prev->data, &data2);
    assert_null(current->next);

    destroy_linked_list(&head);
}

// Test case for remove_linked_list_node_in_head
static void test_remove_linked_list_node_in_head(void **state) {
    struct list_node *head = NULL;
    int data1 = 160, data2 = 170;

    // Remove from empty list (should not crash, but returns NULL)
    struct list_node *removed_empty = remove_linked_list_node_in_head(&head);
    assert_null(removed_empty);

    // Remove from a single-node list
    create_linked_list(&head, &data1);
    head = remove_linked_list_node_in_head(&head);
    assert_null(head);

    // Remove from a multi-node list
    create_linked_list(&head, &data1);
    head = insert_linked_list_in_tail(&head, &data2);
    head = remove_linked_list_node_in_head(&head);
    assert_non_null(head);
    assert_ptr_equal(head->data, &data2);
    assert_null(head->prev);
    assert_null(head->next);
    // The removed node (old_head) should have been freed (valgrind check)

    destroy_linked_list(&head);
}

// Test case for remove_linked_list_node_by_index
static void test_remove_linked_list_node_by_index(void **state) {
    struct list_node *head = NULL;
    int data1 = 180, data2 = 190, data3 = 200, data4 = 210;

    // Remove from empty list
    struct list_node *removed_empty = remove_linked_list_node_by_index(&head, 0);
    assert_null(removed_empty);

    // Remove from single-node list
    create_linked_list(&head, &data1);
    head = remove_linked_list_node_by_index(&head, 0);
    assert_null(head);

    // Remove from the head of a multi-node list
    create_linked_list(&head, &data1);
    head = insert_linked_list_in_tail(&head, &data2);
    struct list_node *temp_head = head;
    head = remove_linked_list_node_by_index(&head, 0);
    assert_non_null(head);
    assert_ptr_equal(head->data, &data2);
    assert_null(head->prev);
    assert_null(head->next);

    // Remove from the tail of a multi-node list
    create_linked_list(&head, &data1);
    head = insert_linked_list_in_tail(&head, &data2);
    head = insert_linked_list_in_tail(&head, &data3);
    temp_head = head;
    head = remove_linked_list_node_by_index(&head, 2);
    assert_non_null(head);
    struct list_node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    assert_ptr_equal(current->data, &data2);
    assert_null(current->next);

    // Remove from the middle of a multi-node list
    create_linked_list(&head, &data1);
    head = insert_linked_list_in_tail(&head, &data2);
    head = insert_linked_list_in_tail(&head, &data3);
    head = insert_linked_list_in_tail(&head, &data4);
    temp_head = head;
    head = remove_linked_list_node_by_index(&head, 1);
    assert_non_null(head);
    assert_ptr_equal(head->data, &data1);
    assert_ptr_equal(head->next->data, &data3);
    assert_ptr_equal(head->next->prev, head);
    assert_ptr_equal(head->next->next->data, &data4);
    assert_ptr_equal(head->next->next->prev, head->next);
    assert_null(head->next->next->next);

    // Remove with out-of-range index (negative)
    temp_head = head;
    head = temp_head;
    struct list_node *original_head_negative_remove = head;
    head = remove_linked_list_node_by_index(&head, -1);
    assert_ptr_equal(head, original_head_negative_remove);

    // Remove with out-of-range index (too large)
    temp_head = head;
    head = temp_head;
    struct list_node *original_head_large_remove = head;
    head = remove_linked_list_node_by_index(&head, 100);
    assert_ptr_equal(head, original_head_large_remove);

    destroy_linked_list(&head);
}

// Test case for destroy_linked_list
static void test_destroy_linked_list(void **state) {
    struct list_node *head = NULL;
    int data1 = 220, data2 = 230, data3 = 240;

    create_linked_list(&head, &data1);
    head = insert_linked_list_in_tail(&head, &data2);
    head = insert_linked_list_in_tail(&head, &data3);

    destroy_linked_list(&head);
    assert_null(head); // Head should be NULL after destroying
}

void linked_list_test() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_new_list_node),
        cmocka_unit_test(test_create_linked_list),
        cmocka_unit_test(test_is_empty_linked_list),
        cmocka_unit_test(test_get_linked_list_length),
        cmocka_unit_test(test_insert_linked_list_in_head),
        cmocka_unit_test(test_insert_linked_list_by_index),
        cmocka_unit_test(test_insert_linked_list_in_tail),
        cmocka_unit_test(test_remove_linked_list_node_in_head),
        cmocka_unit_test(test_remove_linked_list_node_by_index),
        cmocka_unit_test(test_destroy_linked_list),
    };
    cmocka_run_group_tests(tests, NULL, NULL);
}
