#include "../inc/list_funcs.h"
#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"
#include <stdlib.h>
#include <string.h>

void *pop_front(list_node **head)
{
    if (head == NULL || *head == NULL)
        return NULL;

    list_node *first_elem = *head;
    list_node *second_elem = first_elem->next;

    void *value = first_elem->data;

    *head = second_elem;
    free(first_elem);

    return (value);
}

void insert(list_node **head, list_node *elem, list_node *before)
{
    if (head == NULL || *head == NULL || elem == NULL)
        return;

    list_node *ptr = *head;

    if (ptr == before)
    {
        elem->next = ptr;
        *head = elem;
    }
    else
    {
        while (ptr != NULL && ptr->next != before)
        {
            ptr = ptr->next;
        }

        if (ptr != NULL)
        {
            elem->next = ptr->next;
            ptr->next = elem;
        }
    }
}

list_node *reverse(list_node *head)
{
    list_node *rev_ptr = NULL;
    list_node *ptr = head;

    while (ptr != NULL)
    {
        void *val = pop_front(&ptr);

        list_node *new_node = calloc(1, sizeof(list_node));

        if (new_node == NULL)
        {
            while (rev_ptr != NULL)
            {
                list_node *tmp = rev_ptr->next;
                free(rev_ptr);
                rev_ptr = tmp;
            }

            return NULL;
        }

        new_node->data = val;
        new_node->next = rev_ptr;
        rev_ptr = new_node;
    }

    return rev_ptr;
}

void front_back_split(list_node *head, list_node **back)
{
    int count = 0;
    int half;

    list_node *ptr = head;
    while (ptr != NULL)
    {
        count++;
        ptr = ptr->next;
    }

    if (count <= 1)
        return;

    half = (count + 1) / 2 - 1;
    ptr = head;

    for (int i = 0; i < half; i++)
    {
        ptr = ptr->next;
    }

    *back = ptr->next;
    ptr->next = NULL;
}

list_node *sorted_merge(list_node **head_a, list_node **head_b, int (*comparator)(const void *, const void *))
{
    list_node *ptr = NULL;
    list_node *ptr_head = ptr;
    list_node *smaller;

    while (*head_a != NULL || *head_b != NULL)
    {
        int compare;
        if (*head_a != NULL && *head_b != NULL)
            compare = comparator((*head_a)->data, (*head_b)->data);
        else if (*head_a != NULL)
            compare = -1;
        else
            compare = 1;

        smaller = compare < 0 ? *head_a : *head_b;

        if (ptr != NULL)
        {
            ptr->next = smaller;
            ptr = ptr->next;
        }
        else
        {
            ptr_head = smaller;
        }
        ptr = smaller;
        smaller = smaller->next;

        if (compare < 0)
            *head_a = smaller;
        else
            *head_b = smaller;
    }

    if (ptr_head != NULL)
        ptr->next = NULL;

    return ptr_head;
}

list_node *sort(list_node *head, int (*comparator)(const void *, const void *))
{
    if (head == NULL)
        return NULL;
    if (head->next == NULL)
        return head;

    list_node *right;
    front_back_split(head, &right);

    list_node *lval = sort(head, comparator);
    list_node *rval = sort(right, comparator);
    list_node *merged = sorted_merge(&lval, &rval, comparator);

    return merged;
}
