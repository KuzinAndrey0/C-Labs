#include "../inc/my_defines.h"

#ifndef __LIST_FUNCS__

#define __LIST_FUNCS__

int insert_sorted(list_t **head, list_t *node);
void free_list(list_t *head);
void print_list(list_t *list_head);
list_t *create_node(int val);

#endif