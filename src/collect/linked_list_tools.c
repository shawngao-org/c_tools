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

int is_empty_linked_list(const struct list_node *head) {
    return head == NULL;
}

int get_linked_list_length(struct list_node **head) {
    if (is_empty_linked_list(*head)) {
        return 0;
    }
    const struct list_node *head_tmp = *head;
    int length = 0;
    while (head_tmp != NULL) {
        length++;
        head_tmp = head_tmp->next;
    }
    return length;
}

struct list_node *insert_linked_list_in_head(struct list_node **head, void *data) {
    if (is_empty_linked_list(*head)) {
        create_linked_list(head, data);
        return *head;
    }
    struct list_node *new_node = new_list_node(NULL, *head, data);
    (*head)->prev = new_node;
    *head = new_node;
    return *head;
}

struct list_node *insert_linked_list_by_index(struct list_node **head, void *data, const int index) {
    if (index < 0) {
        printf("Index [%d] out of range.\n", index);
        return *head;
    }
    if (is_empty_linked_list(*head)) {
        create_linked_list(head, data);
        return *head;
    }
    if (index == 0) {
        insert_linked_list_in_head(head, data);
        return *head;
    }
    int i = 0;
    struct list_node *head_tmp = *head;
    const int final_idx = index - 1;
    while (i < final_idx) {
        if ((*head)->next == NULL) {
            *head = insert_linked_list_in_tail(head, data);
            return *head;
        }
        *head = (*head)->next;
        i++;
    }
    struct list_node *new_node = new_list_node(NULL, (*head)->next, data);
    new_node->prev = *head;
    if ((*head)->next != NULL) {
        (*head)->next->prev = new_node;
    }
    (*head)->next = new_node;
    return head_tmp;
}

struct list_node *insert_linked_list_in_tail(struct list_node **head, void *data) {
    if (is_empty_linked_list(*head)) {
        create_linked_list(head, data);
        return *head;
    }
    struct list_node *head_tmp = *head;
    while ((*head)->next != NULL) {
        *head = (*head)->next;
    }
    struct list_node *new_node = new_list_node(*head, NULL, data);
    (*head)->next = new_node;
    return head_tmp;
}

struct list_node *remove_linked_list_node_in_head(struct list_node **head) {
    if (is_empty_linked_list(*head)) {
        return *head;
    }
    if (get_linked_list_length(head) == 1) {
        destroy_linked_list(head);
        return NULL;
    }
    struct list_node *old_head = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(old_head);
    return *head;
}

struct list_node *remove_linked_list_node_by_index(struct list_node **head, const int index) {
    if (is_empty_linked_list(*head)) {
        return *head;
    }
    const int len = get_linked_list_length(head);
    if (index < 0 || len <= index) {
        printf("Index [%d] out of range [0 - %d].\n", index, len);
        return *head;
    }
    if (index == 0) {
        return remove_linked_list_node_in_head(head);
    }
    struct list_node *head_tmp = *head;
    int i = 0;
    const int final_idx = index - 1;
    while (i < final_idx) {
        *head = (*head)->next;
        i++;
    }
    if (*head == NULL) {
        return head_tmp;
    }
    if ((*head)->next != NULL) {
        struct list_node *wait_remove = (*head)->next;
        if (wait_remove->next != NULL) {
            (*head)->next = wait_remove->next;
            wait_remove->next->prev = *head;
        } else {
            (*head)->next = NULL;
        }
        free(wait_remove);
    }
    return head_tmp;
}

void destroy_linked_list(struct list_node **head) {
    while (*head != NULL) {
        struct list_node *tmp = (*head)->next;
        if (*head != NULL) {
            free(*head);
        }
        *head = tmp;
    }
}
