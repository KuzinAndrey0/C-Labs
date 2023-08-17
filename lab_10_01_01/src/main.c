#define _GNU_SOURCE

#include "../inc/dynamic_data.h"
#include "../inc/list_funcs.h"
#include "../inc/my_defines.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct allocated_data_s global_data;

int is_eof(FILE *f)
{
    char buf;
    long prev = ftell(f);
    int num;

    num = fread(&buf, sizeof(char), 1, f);
    fseek(f, prev, SEEK_SET);
    if (feof(f) || num == 0 || buf == 0)
    {
        return 1;
    }
    return 0;
}

int cmpfunc(const void *ptr1, const void *ptr2)
{
    int num1 = ((product_t *)ptr1)->quantity * ((product_t *)ptr1)->cost;
    int num2 = ((product_t *)ptr2)->quantity * ((product_t *)ptr2)->cost;
    return num1 - num2;
}

int read_line(FILE *f, char **str)
{
    ssize_t size = 0;
    size_t len = 0;

    size = getline(str, &len, f);

    if (size <= 0)
    {
        free(*str);
        return 1;
    }

    if ((*str)[size - 1] == '\n')
    {
        (*str)[size - 1] = '\0';
        size--;

        if (size == 0)
        {
            free(*str);
            return RETURN_WRONG_FORMAT;
        }
    }

    if ((*str)[size - 1] == '\r')
    {
        (*str)[size - 1] = '\0';
        size--;

        if (size == 0)
        {
            free(*str);
            return RETURN_WRONG_FORMAT;
        }
    }
    int rc = add_global_data((void *)(*str), TYPE_ARRAY);
    if (!rc)
    {
        free(str);
        return RETURN_MEMORY_ERROR;
    }

    return 0;
}

int is_integer(char str[])
{
    char *new_ptr = str;
    int len = strlen(str);
    while (len > 0 && new_ptr[0] == ' ')
    {
        new_ptr++;
    }
    while (len > 0 && new_ptr[len - 1] == ' ')
    {
        len--;
    }

    if (len == 0)
        return 1;

    if (new_ptr[0] != '-' && !isdigit(new_ptr[0]))
        return 0;

    for (int i = 1; i < len; i++)
    {
        if (!isdigit(new_ptr[i]))
            return 0;
    }

    return 1;
}

int read_struct(FILE *f, void **ptr)
{
    char *tmp_str[4];

    int tmp_quantity, tmp_cost;
    int rc;
    product_t *new_node_ptr;

    for (int i = 0; i < 4; i++)
    {
        tmp_str[i] = NULL;
        rc = read_line(f, &(tmp_str[i]));
        if (rc != RETURN_SUCCESS)
            return rc;
    }

    if (!is_integer(tmp_str[2]))
        return RETURN_QUANTITY_NOT_NUM;

    tmp_quantity = atoi(tmp_str[2]);
    tmp_cost = atoi(tmp_str[3]);

    int dyn_data_index = global_data.total - 1;

    free_memory_index(dyn_data_index);
    free_memory_index(dyn_data_index - 1);

    if (tmp_quantity < 0 || tmp_cost <= 0)
        return RETURN_WRONG_FORMAT;

    new_node_ptr = my_malloc(sizeof(product_t));
    if (new_node_ptr == NULL)
        return RETURN_MEMORY_ERROR;

    new_node_ptr->name = tmp_str[0];
    new_node_ptr->category = tmp_str[1];
    new_node_ptr->quantity = tmp_quantity;
    new_node_ptr->cost = tmp_cost;

    *ptr = new_node_ptr;

    return RETURN_SUCCESS;
}

int read_all_structs(FILE *f, list_t *product_list)
{
    int rc = 0;
    while (rc == RETURN_SUCCESS)
    {
        void *ptr_to_add;

        rc = read_struct(f, &ptr_to_add);
        if (rc == RETURN_SUCCESS)
        {
            rc = list_add_last(product_list, ptr_to_add);
            if (rc != RETURN_SUCCESS)
                terminate_program(rc);

            if (is_eof(f))
                break;
        }
    }
    return RETURN_SUCCESS;
}

int main(int argc, char **argv)
{
    if (argc < 4)
        terminate_program(RETURN_NOT_ENOUGH_ARGUMENTS);
    int f_index;
    FILE *f;

    int rc = init_global_data();
    if (!rc)
        terminate_program(rc);

    list_t product_list;
    rc = init_list(&product_list);
    if (rc != RETURN_SUCCESS)
        terminate_program(rc);

    f = my_fopen(argv[1], "r");
    if (f == NULL)
        terminate_program(RETURN_NO_FILE);

    f_index = global_data.total - 1;
    rc = 0;

    rc = read_all_structs(f, &product_list);

    free_memory_index(f_index);

    if (rc != RETURN_SUCCESS)
    {
        terminate_program(rc);
    }

    if (strcmp(argv[3], "missing") == 0)
    {
        if (product_list.total == 0)
            terminate_program(RETURN_EMPTY_FILE);
        list_node *ptr = product_list.head;
        f = my_fopen(argv[2], "w");
        if (f == NULL)
            terminate_program(RETURN_NO_FILE);
        f_index = global_data.total - 1;

        while (ptr != NULL)
        {
            if (((product_t *)ptr->data)->quantity == 0)
            {
                fprintf(f, "%s\n", ((product_t *)ptr->data)->name);
                fprintf(f, "%s\n", ((product_t *)ptr->data)->category);
                fprintf(f, "%d\n", ((product_t *)ptr->data)->quantity);
                fprintf(f, "%d\n", ((product_t *)ptr->data)->cost);
            }
            ptr = ptr->next;
        }

        free_memory_index(f_index);
    }
    else if (strcmp(argv[3], "sort") == 0)
    {
        if (product_list.total == 0)
            terminate_program(RETURN_EMPTY_FILE);
        product_list.head = sort(product_list.head, cmpfunc);

        list_node *ptr = product_list.head;
        f = my_fopen(argv[2], "w");
        if (f == NULL)
            terminate_program(RETURN_NO_FILE);
        f_index = global_data.total - 1;

        while (ptr != NULL)
        {
            fprintf(f, "%s\n", ((product_t *)ptr->data)->name);
            fprintf(f, "%s\n", ((product_t *)ptr->data)->category);
            fprintf(f, "%d\n", ((product_t *)ptr->data)->quantity);
            fprintf(f, "%d\n", ((product_t *)ptr->data)->cost);

            ptr = ptr->next;
        }

        free_memory_index(f_index);
    }
    else if (strcmp(argv[3], "sortrev") == 0)
    {
        if (product_list.total == 0)
            terminate_program(RETURN_EMPTY_FILE);
        product_list.head = sort(product_list.head, cmpfunc);
        product_list.head = reverse(product_list.head);

        list_node *ptr = product_list.head;
        f = my_fopen(argv[2], "w");
        if (f == NULL)
            terminate_program(RETURN_NO_FILE);
        f_index = global_data.total - 1;

        while (ptr != NULL)
        {
            fprintf(f, "%s\n", ((product_t *)ptr->data)->name);
            fprintf(f, "%s\n", ((product_t *)ptr->data)->category);
            fprintf(f, "%d\n", ((product_t *)ptr->data)->quantity);
            fprintf(f, "%d\n", ((product_t *)ptr->data)->cost);

            ptr = ptr->next;
        }

        free_memory_index(f_index);
    }
    else if (strcmp(argv[3], "insert") == 0)
    {
        list_t product_list2;
        rc = init_list(&product_list2);
        if (rc != RETURN_SUCCESS)
            terminate_program(rc);

        f = my_fopen(argv[2], "r");
        if (f == NULL)
            terminate_program(RETURN_NO_FILE);
        f_index = global_data.total - 1;

        rc = read_all_structs(f, &product_list);

        free_memory_index(f_index);

        if (rc != RETURN_SUCCESS)
        {
            terminate_program(rc);
        }

        list_node *ptr = product_list.head;
        f = my_fopen(argv[1], "w");

        if (f == NULL)
            terminate_program(RETURN_NO_FILE);

        f_index = global_data.total - 1;

        while (ptr != NULL)
        {
            fprintf(f, "%s\n", ((product_t *)ptr->data)->name);
            fprintf(f, "%s\n", ((product_t *)ptr->data)->category);
            fprintf(f, "%d\n", ((product_t *)ptr->data)->quantity);
            fprintf(f, "%d\n", ((product_t *)ptr->data)->cost);

            ptr = ptr->next;
        }

        ptr = product_list2.head;
        while (ptr != NULL)
        {
            fprintf(f, "%s\n", ((product_t *)ptr->data)->name);
            fprintf(f, "%s\n", ((product_t *)ptr->data)->category);
            fprintf(f, "%d\n", ((product_t *)ptr->data)->quantity);
            fprintf(f, "%d\n", ((product_t *)ptr->data)->cost);

            ptr = ptr->next;
        }

        free_memory_index(f_index);
    }
    else
    {
        terminate_program(RETURN_WRONG_ARGUMENTS);
    }

    terminate_program(RETURN_SUCCESS);
}