#include "../inc/my_defines.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

typedef struct list_t list_t;
struct list_t
{
    int val;
    list_t *prev;
    list_t *next;
};

void print_menu(void)
{
    printf("\n");

    printf("1 - Влево\n");
    printf("2 - Вправо\n");
    printf("3 - Печать элемента\n");
    printf("4 - Удалить элемент\n");
    printf("5 - Сортировка\n");

    printf("0 - Выход из программы\n\n");
    printf("\n");
}

int get_input(char str[], unsigned max_length)
{
    size_t pos = 0;

    str[pos] = getc(stdin);
    pos++;

    while (str[pos - 1] != '\n')
    {
        if (pos > max_length)
        {
            return RETURN_INPUT_ERROR;
        }
        str[pos] = fgetc(stdin);
        pos++;
    }

    str[pos - 1] = '\0';

    return RETURN_SUCCESS;
}

list_t *create_node(int val)
{
    list_t *list = malloc(sizeof(list_t));
    list->next = NULL;
    list->prev = NULL;
    list->val = val;

    return list;
}

void add_elem(list_t **list, int val)
{
    list_t *cur_list = *list;
    list_t *new_node = create_node(val);

    if (*list == NULL)
    {
        *list = new_node;
        return;
    }

    while (cur_list->next != NULL)
        cur_list = cur_list->next;

    new_node->prev = cur_list;
    cur_list->next = new_node;
}

void remove_elem(list_t **list, int val)
{
    list_t *cur_list = *list;

    if (cur_list == NULL)
    {
        return;
    }

    if (cur_list->val == val)
    {
        *list = cur_list->next;
        (*list)->prev = NULL;
        free(cur_list);
        return;
    }

    while (cur_list->next != NULL && cur_list->next->val != val)
        cur_list = cur_list->next;

    if (cur_list == NULL)
        return;

    list_t *temp;
    if (cur_list->next == NULL)
    {
        temp = NULL;
    }
    else
        temp = cur_list->next->next;

    free(cur_list->next);
    cur_list->next = temp;

    if (temp != NULL)
        temp->prev = cur_list;
}

void print_list(list_t *list)
{
    while (list != NULL)
    {
        printf("%d ", list->val);
        list = list->next;
    }
    printf("\n");
}

void print_list_test(list_t *list, list_t *cur_elem)
{
    while (list->next != NULL)
    {
        list = list->next;
    }

    while (list->prev != NULL)
    {
        list = list->prev;
    }

    while (list != NULL)
    {
        if (list == cur_elem)
        {
            printf("\033[0;34m%d \033[0m", list->val);
        }
        else
        {
            printf("%d ", list->val);
        }
        list = list->next;
    }
    printf("\n");
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

void free_list(list_t *list)
{
    while (list != NULL)
    {
        list_t *tmp = list->next;
        free(list);
        list = tmp;
    }
    printf("\n");
}

int get_input_num(char str[], unsigned max_length, int *num)
{
    int rc = get_input(str, max_length);
    if (rc == RETURN_SUCCESS)
    {
        if (is_integer(str) && strlen(str) > 0)
        {
            *num = atoi(str);
            return RETURN_SUCCESS;
        }
    }
    return RETURN_INPUT_ERROR;
}

void swap_elems(list_t *list1, list_t *list2)
{
    int tmp = list1->val;

    list1->val = list2->val;
    list2->val = tmp;
}

void sort_elems(list_t *list)
{
    list_t *list1 = list;
    while (list1 != NULL)
    {
        list_t *list2 = list;
        while (list2->next != NULL)
        {
            if (list2->val > list2->next->val)
            {
                swap_elems(list2, list2->next);
            }
            list2 = list2->next;
        }
        list1 = list1->next;
    }
}

list_t *gen_list(int size)
{
    list_t *list = NULL;
    while (size > 0)
    {
        int val = rand() % 100;
        add_elem(&list, val);
        size--;
    }
    return list;
}

int main()
{
    srand(time(NULL));
    int rc;
    list_t *list;

    list = gen_list(30);

    // for (int i = 0; i < 10; i++)
    //    add_elem(&list, 10 - i);

    int working = 1;
    char input[INPUT_BUFFER];

    list_t *cur_elem = list;

    while (working)
    {
        print_list_test(list, cur_elem);
        print_menu();

        rc = get_input(input, INPUT_BUFFER);

        if (rc == RETURN_SUCCESS)
        {
            if (strcmp(input, "0") == 0)
            {
                working = 0;
            }
            else if (strcmp(input, "1") == 0)
            {
                if (cur_elem->prev == NULL)
                {
                    printf("Предыдущего элемента нет\n");
                }
                else
                {
                    cur_elem = cur_elem->prev;
                }
            }
            else if (strcmp(input, "2") == 0)
            {
                if (cur_elem->next == NULL)
                {
                    printf("Следующего элемента нет\n");
                }
                else
                {
                    cur_elem = cur_elem->next;
                }
            }
            else if (strcmp(input, "3") == 0)
            {
                printf("\n");
                if (cur_elem->prev == NULL)
                    printf("NULL ");
                else
                    printf("%d ", cur_elem->prev->val);

                printf("%d ", cur_elem->val);

                if (cur_elem->next == NULL)
                    printf("NULL\n");
                else
                    printf("%d\n", cur_elem->next->val);
            }
            else if (strcmp(input, "4") == 0)
            {
                int num_to_add;

                printf("Введите целое число: ");
                rc = get_input_num(input, INPUT_BUFFER, &num_to_add);
                if (rc == RETURN_SUCCESS)
                {
                    remove_elem(&list, num_to_add);
                    cur_elem = list;
                }
                else
                {
                    printf("Неверный ввод\n");
                }
            }
            else if (strcmp(input, "5") == 0)
            {
                sort_elems(list);
            }
        }
    }

    free_list(list);
    return RETURN_SUCCESS;
}