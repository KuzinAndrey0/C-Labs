#include "../inc/stack_handle.h"
#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>

int stack_list_push(list_t *list, int value)
{
    list_node *new_node;

    new_node = malloc(sizeof(list_node));

    if (new_node == NULL)
    {
        return RETURN_MEMORY_ERROR;
    }

    new_node->value = value;
    new_node->next = list->head;

    list->head = new_node;

    list->total++;

    return RETURN_SUCCESS;
    // return list_add_last(list, value);
}

int stack_list_pop(list_t *list)
{
    list_node *ptr = list->head;
    int val = 0;
    list_node *new_ptr;

    if (ptr == NULL)
        return val;

    val = ptr->value;
    new_ptr = ptr->next;
    free(ptr);
    list->head = new_ptr;

    list->total--;
    return val;
}

void stack_array_push(int *arr, int value, int *pos)
{
    arr[*pos] = value;
    (*pos)++;
}

int stack_array_pop(int *arr, int *pos)
{
    (*pos)--;

    return arr[*pos];
}
