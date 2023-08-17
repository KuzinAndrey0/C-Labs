#include "../inc/list_funcs.h"
#include "../inc/my_defines.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_digit(char *str)
{
    char *start_ptr = str;
    if ((*start_ptr) == '-')
        start_ptr++;

    int is_int = (*start_ptr) == '\0' ? 0 : 1;
    while ((*start_ptr) != '\0')
    {
        if (!isdigit(*start_ptr))
        {
            is_int = 0;
        }
        start_ptr++;
    }
    return is_int;
}

int read_file(FILE *f, list_t **list_head)
{
    int rc, num;
    while (!feof(f))
    {
        rc = fscanf(f, "%d", &num);

        if (!feof(f))
        {
            if (rc != 1)
            {
                printf("Неверное содержание файла\n");
                // free_list(*list_head);
                // fclose(f);
                return RETURN_WRONG_FILE;
            }

            list_t *node = create_node(num);

            if (node == NULL)
            {
                printf("Ошибка выделения памяти\n");

                // fclose(f);
                return RETURN_ERROR_GENERIC;
            }
            insert_sorted(list_head, node);
        }
    }
    return RETURN_SUCCESS;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Неверное кол-во аргументов\n");
        return RETURN_ERROR_GENERIC;
    }

    if (!is_digit(argv[2]))
    {
        printf("Второй аргумент не число\n");
        return RETURN_NOT_DIGIT;
    }

    int rc;
    list_t *list_head = NULL;

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Файла нет\n");
        return RETURN_NO_FILE;
    }
    rc = read_file(f, &list_head);
    fclose(f);
    if (rc != RETURN_SUCCESS)
    {
        free_list(list_head);
        return rc;
    }

    printf("До вставки числа:\n");
    print_list(list_head);

    list_t *node = create_node(atoi(argv[2]));

    insert_sorted(&list_head, node);

    printf("\nПосле вставки числа:\n");
    print_list(list_head);

    free_list(list_head);
    printf("\n");
    return RETURN_SUCCESS;
}