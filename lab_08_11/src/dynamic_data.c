#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>

void free_matrix(int **ptrs)
{
    free(ptrs[0]);

    free(ptrs);
}

int init_global_data(void)
{
    global_data.create_mem = DYN_START_MEM;
    global_data.step_mem = DYN_STEP_MEM;

    global_data.ptr = malloc(sizeof(void *) * global_data.create_mem);
    global_data.type = malloc(sizeof(int *) * global_data.create_mem);
    global_data.total = 0;
    global_data.current_mem = global_data.create_mem;

    if (global_data.ptr == NULL || global_data.type == NULL)
    {
        free(global_data.ptr);
        free(global_data.type);
        return 0;
    }
    return 1;
}

int add_global_data(void *ptr, int type)
{
    if (global_data.total >= global_data.current_mem)
    {
        void *test_ptr1 = realloc(global_data.ptr, sizeof(void *) * (global_data.current_mem + global_data.step_mem));
        void *test_ptr2 = realloc(global_data.type, sizeof(int *) * (global_data.current_mem + global_data.step_mem));
        if (test_ptr1 == NULL || test_ptr2 == NULL)
        {
            return 0;
        }

        global_data.ptr = test_ptr1;
        global_data.type = test_ptr2;

        global_data.current_mem += global_data.step_mem;
    }

    global_data.ptr[global_data.total] = ptr;
    global_data.type[global_data.total] = type;
    global_data.total++;

    return 1;
}

void *my_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr != NULL)
    {
        int rc = add_global_data(ptr, TYPE_ARRAY);
        if (!rc)
        {
            free(ptr);
            return NULL;
        }
    }
    return ptr;
}

int **allocate_matrix(int n, int m)
{
    int **ptrs, *data;
    ptrs = malloc(n * sizeof(int *));
    if (!ptrs)
        return NULL;
    data = calloc(n * m, sizeof(int));
    if (!data)
    {
        free(ptrs);
        return NULL;
    }
    for (int i = 0; i < n; i++)
        ptrs[i] = data + i * m;

    int rc = add_global_data(ptrs, TYPE_MATRIX);
    if (!rc)
    {
        free_matrix(ptrs);
        return NULL;
    }

    return ptrs;
}

void free_memory(int index)
{
    if (global_data.type[index] == TYPE_ARRAY)
    {
        free(global_data.ptr[index]);
    }
    else if (global_data.type[index] == TYPE_MATRIX)
    {
        free_matrix((int **)global_data.ptr[index]);
    }
    // else if (global_data.type[index] == TYPE_LIST)
    // {
    //     free_list((list_t *)global_data.ptr[index]);
    // }
    else if (global_data.type[index] == TYPE_FILE)
    {
        fclose((FILE *)global_data.ptr[index]);
    }
    else
    {
        printf("WRONG TYPE\n");
    }
}

void free_memory_index(int index)
{
    free_memory(index);
    for (int i = index; i < global_data.total - 1; i++)
    {
        global_data.ptr[i] = global_data.ptr[i + 1];
        global_data.type[i] = global_data.type[i + 1];
    }
    global_data.total--;
}

void free_memory_value(void *ptr)
{
    for (int i = 0; i < global_data.total; i++)
    {
        if (global_data.ptr[i] == ptr)
        {
            free_memory_index(i);
        }
    }
}

void free_memory_all(void)
{
    for (int i = 0; i < global_data.total; i++)
    {
        free_memory(i);
    }
    free(global_data.ptr);
    free(global_data.type);
}

void terminate_program(int rc)
{
    free_memory_all();
    exit(rc);
}

/*
int init_list(list_t *ptr)
{
    ptr->head = NULL;
    ptr->total = 0;
    ptr->tail = NULL;

    int rc = add_global_data(ptr, TYPE_LIST);
    if (!rc)
    {
        free_list(ptr);
        return RETURN_MEMORY_ERROR;
    }

    return RETURN_SUCCESS;
}

void free_list(list_t *list)
{
    list_node *ptr = list->head;

    while (ptr != NULL)
    {
        list_node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
}

int list_add_last(list_t *list, double value)
{
    list_node *new_node;
    list_node *ptr = list->head;

    new_node = malloc(sizeof(list_node));

    if (new_node == NULL)
    {
        return RETURN_MEMORY_ERROR;
    }
    new_node->data = value;
    new_node->next = NULL;

    if (ptr == NULL)
    {
        list->head = new_node;
    }
    else
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }

    list->total++;

    return RETURN_SUCCESS;
}

void list_remove_index(list_t *list, int index)
{
    list_node *ptr = list->head;

    if (index == 0)
    {
        free(ptr);
        list->head = NULL;
        return;
    }
    else
    {
        for (int i = 0; i < index - 1; i++)
        {
            ptr = ptr->next;
        }

        free(ptr->next);
        ptr->next = NULL;
    }
}

void list_remove_last(list_t *list)
{
    list_node *ptr = list->head;
    list_node *tmp;

    if (ptr == NULL)
        return;
    if (ptr->next == NULL)
    {
        free(ptr);
        list->head = NULL;
    }
    else
    {
        while (ptr->next != NULL)
        {
            tmp = ptr;
            ptr = ptr->next;
        }

        free(ptr);
        tmp->next = NULL;
    }

    list->total--;
}

void list_get_info(list_t *list, int index, double *val, void **adress)
{
    list_node *ptr = list->head;

    for (int i = 0; i < index; i++)
    {
        ptr = ptr->next;
    }

    *val = ptr->data;
    *adress = ptr;
}

FILE *my_fopen(const char *filename, const char *modes)
{
    FILE *f = fopen(filename, modes);
    if (f != NULL)
    {
        int rc = add_global_data(f, TYPE_FILE);
        if (!rc)
        {
            fclose(f);
            return NULL;
        }
    }
    return f;
}*/