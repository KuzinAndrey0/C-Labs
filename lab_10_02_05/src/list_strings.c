#define _GNU_SOURCE
#include "../inc/list_strings.h"
#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    return RETURN_SUCCESS;
}

void print_list_string(list_t list_info)
{
    list_node *ptr = list_info.head;
    char chr = 'D';

    while (chr != '\0')
    {
        for (int i = 0; i < SUBSTRING_SIZE; i++)
        {
            chr = ((char *)ptr->data)[i];
            if (chr == '\0')
            {
                break;
            }
            else
            {
                printf("%c", chr);
            }
        }
        ptr = ptr->next;
    }
}

void print_list_debug(list_t list_info)
{
    list_node *ptr = list_info.head;
    char chr = 'D';

    while (ptr != NULL)
    {
        for (int i = 0; i < SUBSTRING_SIZE; i++)
        {
            chr = ((char *)ptr->data)[i];
            if (chr == '\0')
            {
                printf("ZERO");
            }
            else
            {
                printf("%c", chr);
            }
        }
        ptr = ptr->next;
    }
}

void compact(list_t *list_info)
{
    list_node *ptr = list_info->head;
    list_node *ptr_non_zero = list_info->head;
    char chr = 'D';
    int j = 0;

    while (ptr != NULL)
    {
        for (int i = 0; i < SUBSTRING_SIZE; i++)
        {
            chr = ((char *)ptr->data)[i];

            if (chr != '\0')
            {
                ((char *)ptr_non_zero->data)[j] = chr;
                j++;
                if (j >= SUBSTRING_SIZE)
                {
                    j = 0;
                    ptr_non_zero = ptr_non_zero->next;
                }
            }
        }
        ptr = ptr->next;
    }
    ((char *)ptr_non_zero->data)[j] = 0;

    list_node *next = ptr_non_zero->next;
    ptr_non_zero->next = NULL;
    ptr_non_zero = next;

    while (ptr_non_zero != NULL)
    {
        list_node *tmp = ptr_non_zero->next;
        free(ptr_non_zero);
        ptr_non_zero = tmp;

        list_info->total--;
    }
}

void remove_spaces(list_t *list_info)
{
    list_node *ptr = list_info->head;
    char chr = 'D';
    int removing = 0;

    while (chr != '\0')
    {
        for (int i = 0; i < SUBSTRING_SIZE; i++)
        {
            chr = ((char *)ptr->data)[i];
            if (chr == ' ')
            {
                if (!removing)
                    removing = 1;
                else
                {
                    ((char *)ptr->data)[i] = 0;
                }
            }
            else
                removing = 0;
        }
        ptr = ptr->next;
    }

    compact(list_info);
}

int convert_to_list(char *input, list_t *list_info)
{
    int len = strlen(input) + 1;
    int num = (len - 1) / SUBSTRING_SIZE + 1;

    for (int i = 0; i < num; i++)
    {
        char *substr_ptr = my_malloc(sizeof(char) * SUBSTRING_SIZE);
        if (substr_ptr == NULL)
            return RETURN_MEMORY_ERROR;

        int repeat_count = len - i * SUBSTRING_SIZE < SUBSTRING_SIZE ? len - i * SUBSTRING_SIZE : SUBSTRING_SIZE;
        for (int j = 0; j < repeat_count; j++)
            substr_ptr[j] = input[i * SUBSTRING_SIZE + j];

        for (int j = repeat_count; j < SUBSTRING_SIZE; j++)
            substr_ptr[j] = 0;

        list_add_last(list_info, (void *)substr_ptr);
    }

    return RETURN_SUCCESS;
}

void concatenate_strings(list_t *list1, list_t *list_2)
{
    list_node *ptr = list1->head;
    list_node *ptr2 = list_2->head;
    int j = 0;
    char chr = 'D';
    while (chr != '\0')
    {
        for (int i = 0; i < SUBSTRING_SIZE; i++)
        {
            chr = ((char *)ptr->data)[i];
            if (chr == '\0')
            {
                j = i;
                ptr->next = ptr2;
                break;
            }
        }
        if (chr != '\0')
            ptr = ptr->next;
    }

    while (ptr2 != NULL)
    {
        for (int i = 0; i < SUBSTRING_SIZE; i++)
        {
            chr = ((char *)ptr2->data)[i];

            ((char *)ptr->data)[j] = chr;
            j++;
            if (j >= SUBSTRING_SIZE)
            {
                j = 0;
                ptr = ptr->next;
                list1->total++;
            }
        }
        ptr2 = ptr2->next;
    }

    for (int i = j; j < SUBSTRING_SIZE; j++)
        ((char *)ptr->data)[i] = 0;

    list_2->head = NULL;
    list_2->total = 0;
}

int find_substring(list_t string_list, list_t substring_list)
{
    list_node *ptr1 = string_list.head;
    list_node *ptr2 = substring_list.head;

    int str_pos = 0;
    int substr_pos = 0;
    int pos = 0;
    int start_pos = 0;

    while (ptr1 != NULL)
    {
        char chr1 = ((char *)ptr1->data)[str_pos];
        char chr2 = ((char *)ptr2->data)[substr_pos];

        if (chr2 == '\0')
            return start_pos;

        str_pos++;
        pos++;
        if (str_pos >= SUBSTRING_SIZE)
        {
            str_pos = 0;
            ptr1 = ptr1->next;
        }

        if (chr1 == chr2)
        {
            substr_pos++;
            if (substr_pos >= SUBSTRING_SIZE)
            {
                substr_pos = 0;
                ptr2 = ptr2->next;
            }
        }
        else
        {
            start_pos = pos;
            ptr2 = substring_list.head;
            substr_pos = 0;
        }
    }

    return -1;
}