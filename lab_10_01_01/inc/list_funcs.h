#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"

#ifndef __LIST_FUNCS__

#define __LIST_FUNCS__

void *pop_front(list_node **head);
void insert(list_node **head, list_node *elem, list_node *before);
list_node *reverse(list_node *head);
void front_back_split(list_node *head, list_node **back);
list_node *sorted_merge(list_node **head_a, list_node **head_b, int (*comparator)(const void *, const void *));
list_node *sort(list_node *head, int (*comparator)(const void *, const void *));

#endif

//Отсортировать по цене/кол-ву/категории/имени по убыванию, по возрастанию
//Общая выручка из каждой категории
//Вывести отсутствующие товары