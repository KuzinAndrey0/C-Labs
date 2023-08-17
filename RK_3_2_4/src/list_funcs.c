#include "../inc/list_funcs.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>

int insert_sorted(list_t **head, list_t *node)
{
    if ((*head) == NULL)
    {
        *head = node;
        return RETURN_SUCCESS;
    }

    list_t *ptr = *head;
    list_t *ptr_prev = NULL;

    while (ptr != NULL && ptr->val < node->val)
    {
        ptr_prev = ptr;
        ptr = ptr->next;
    }

    if (ptr_prev == NULL)
    {
        node->next = *head;
        *head = node;
        return RETURN_SUCCESS;
    }
    if (ptr != NULL)
    {
        ptr_prev->next = node;
        node->next = ptr;

        return RETURN_SUCCESS;
    }
    if (ptr == NULL)
    {
        ptr_prev->next = node;
        return RETURN_SUCCESS;
    }
    return RETURN_ERROR_GENERIC;
}

void free_list(list_t *head)
{
    while (head != NULL)
    {
        list_t *ptr = head->next;
        free(head);
        head = ptr;
    }
}

void print_list(list_t *list_head)
{
    list_t *test = list_head;
    if (test == NULL)
    {
        printf("<Пустой список>");
    }
    while (test != NULL)
    {
        if (test != NULL)
        {
            printf("%d ", test->val);
            test = test->next;
        }
    }
    printf("\n");
}

list_t *create_node(int val)
{
    list_t *node = malloc(sizeof(list_t));
    if (node == NULL)
        return NULL;
    node->val = val;
    node->next = NULL;

    return node;
}