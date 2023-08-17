#include "../inc/graph_funcs.h"
#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"
#include <ctype.h>
#include <stdio.h>

int queue_array_push(void *queue_p, int val)
{
    queue_arr_t *queue = (queue_arr_t *)queue_p;
    if (queue->total >= queue->max)
        return RETURN_QUEUE_OVERFLOW;

    *(queue->ptr_end) = val;
    queue->ptr_end++;

    if ((queue->ptr_end - queue->val) >= queue->max)
        queue->ptr_end -= queue->max;

    queue->total++;

    return RETURN_SUCCESS;
}

int queue_array_pop(void *queue_p, int *val)
{
    queue_arr_t *queue = (queue_arr_t *)queue_p;
    if (queue->total <= 0)
        return RETURN_QUEUE_OVERFLOW;

    *val = *(queue->ptr_start);
    queue->ptr_start++;

    if ((queue->ptr_start - queue->val) >= QUEUE_SIZE)
        queue->ptr_start -= QUEUE_SIZE;
    queue->total--;

    return RETURN_SUCCESS;
}

int init_queue_array(queue_arr_t *queue, size_t size)
{
    int *queue_array_vals;
    queue_array_vals = my_malloc(size * sizeof(int));
    if (queue_array_vals == NULL)
        return RETURN_MEMORY_ERROR;
    queue->val = queue_array_vals;
    queue->ptr_start = queue->val;
    queue->ptr_end = queue->ptr_start;
    queue->total = 0;
    queue->max = size;

    return RETURN_SUCCESS;
}

int bfs(int **graph, int size, int first_node, int second_node, int *path_size, int **path)
{
    *path = NULL;
    *path_size = 0;

    int *visited = my_malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
        visited[i] = 0;

    int *parent = my_malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
        parent[i] = -1;

    int index = global_data.total - 2;

    queue_arr_t queue_arr;
    init_queue_array(&queue_arr, QUEUE_SIZE);

    queue_array_push(&queue_arr, first_node);
    // print_queue_array(queue_arr);

    visited[first_node] = 1;
    while (queue_arr.total > 0)
    {
        int v;
        queue_array_pop(&queue_arr, &v);
        for (int i = 0; i < size; i++)
        {
            if (graph[v][i])
            {
                if (!visited[i])
                {
                    queue_array_push(&queue_arr, i);
                    // print_queue_array(queue_arr);
                    visited[i] = 1;
                    parent[i] = v;
                    if (i == second_node)
                    {
                        int num = second_node;

                        while (num != first_node)
                        {
                            num = parent[num];
                            (*path_size)++;
                        }
                        num = second_node;
                        (*path) = my_malloc(sizeof(int) * (*path_size));

                        for (int z = 0; z < (*path_size); z++)
                        {
                            (*path)[(*path_size) - 1 - z] = num;
                            num = parent[num];
                        }

                        for (int z = 0; z < 2; z++)
                            free_memory_index(index);
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
