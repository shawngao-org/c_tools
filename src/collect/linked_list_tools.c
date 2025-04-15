//
// Created by ZetoHkr on 2025/4/15.
//

#include "collect/linked_list_tools.h"

#include <stdio.h>
#include <stdlib.h>

struct list_node *new_list_node(struct list_node *prev, struct list_node *next, void *data) {
    struct list_node *new_node = (struct list_node *) malloc(sizeof(struct list_node));
    new_node->data = data;
    new_node->prev = prev;
    new_node->next = next;
    return new_node;
}

void create_linked_list(struct list_node **head, void *fst_data) {
    *head = new_list_node(NULL, NULL, fst_data);
}

int is_empty_linked_list(struct list_node *head) {
    return head == NULL;
}

void insert_linked_list_in_head(struct list_node **head, void *data) {
    if (is_empty_linked_list(*head)) {
        create_linked_list(head, data);
    } else {
        struct list_node *new_node = new_list_node(NULL, *head, data);
        (*head)->prev = new_node;
        *head = new_node;
    }
}

void insert_linked_list_in_tail(struct list_node **head, void *data) {
    if (is_empty_linked_list(*head)) {
        create_linked_list(head, data);
    } else {
        struct list_node *new_node = new_list_node(*head, NULL, data);
        while ((*head)->next != NULL) {
            *head = (*head)->next;
        }
        (*head)->next = new_node;
    }
}

void destroy_linked_list(struct list_node **head) {
    while (*head != NULL) {
        struct list_node *tmp = (*head)->next;
        free(*head);
        *head = tmp;
    }
}
