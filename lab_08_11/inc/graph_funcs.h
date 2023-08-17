#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef __GRAPH_FUNCS__

// trc-ignore
#define __GRAPH_FUNCS__

// Обход графа в ширину
int bfs(int **graph, int size, int first_node, int second_node, int *path_size, int **path);

// Создание очереди
int init_queue_array(queue_arr_t *queue, size_t size);
// Получение элемента из очереди
int queue_array_pop(void *queue_p, int *val);
// Добавление элемента в очередь
int queue_array_push(void *queue_p, int val);

#endif