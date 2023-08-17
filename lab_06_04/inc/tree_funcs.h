#include "../inc/my_defines.h"
#include <stdio.h>

#ifndef __TREE_FUNCS__

// trc-ignore
#define __TREE_FUNCS__

// trc-ignore
typedef void (*ptr_action_t)(struct tree_node *, void *);

/*
Информация о файле
*/
typedef struct file_info
{
    char *filename; // Название файла
    int day;        // День изменения файла
    int month;      // Месяц изменения файла
    int year;       // Год изменения файла
} file_info;

// Поиск минимального значения в дереве
tree_node *find_minimum(tree_node *current_node);
// Поиск значения в дереве
int tree_search(tree_node *root, void *value, int cmpfunc(void *, void *));
//Компаратор для сравнения в дереве, хранящем целые числа
int cmp_int(void *ptr1, void *ptr2);
//Вывод дерева, хранящего целые числа
void print_int(tree_node *ptr, void *param);
//Добавление элемента в дерево
void insert(tree_node **root, void *value, int cmpfunc(void *, void *));
// trc-ignore
void node_to_dot_int(struct tree_node *tree, void *param);
// trc-ignore
void apply_pre(struct tree_node *tree, ptr_action_t f, void *arg);
// trc-ignore
void apply_in(struct tree_node *tree, ptr_action_t f, void *arg);
// trc-ignore
void apply_post(struct tree_node *tree, ptr_action_t f, void *arg);
// trc-ignore
void tree_export(FILE *f, const char *tree_name, tree_node *root);
// trc-ignore
void free_node(tree_node *ptr, void *param);
// trc-ignore
void free_tree(tree_node *root);
// trc-ignore
tree_node *delete_node(tree_node *root, void *value, int cmpfunc(void *, void *));
// trc-ignore
tree_node *delete_node_less_than_tmp(tree_node *root, void *value, int cmpfunc(void *, void *), int *rc);
// trc-ignore
void delete_node_less_than(tree_node **root, void *value, int cmpfunc(void *, void *));
// trc-ignore
void node_to_dot_file(tree_node *tree, void *param);
// trc-ignore
void tree_export_f(FILE *f, const char *tree_name, tree_node *tree);
// trc-ignore
int find_non_sorted(tree_node *root, int val);
// trc-ignore
tree_node *gen_tree(double branching, int node_num);

#endif