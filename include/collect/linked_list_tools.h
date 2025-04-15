//
// Created by ZetoHkr on 2025/4/15.
//

#ifndef TOOLS_LINKED_LIST_TOOLS_H
#define TOOLS_LINKED_LIST_TOOLS_H

#include "tools.h"

struct list_node *new_list_node(struct list_node *prev, struct list_node *next, void *data);
void create_linked_list(struct list_node **head, void *fst_data);
int is_empty_linked_list(struct list_node *head);
void insert_linked_list_in_head(struct list_node **head, void *data);
void insert_linked_list_in_tail(struct list_node **head, void *data);
void destroy_linked_list(struct list_node **head);

#endif //TOOLS_LINKED_LIST_TOOLS_H
