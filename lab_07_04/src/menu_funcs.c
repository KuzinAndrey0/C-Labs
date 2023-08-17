#include "../inc/menu_funcs.h"
#include "../inc/my_defines.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// trc-ignore
void center_text(char *text, int width)
{
    int pad1 = (width - strlen(text)) / 2;
    int pad2 = width - pad1 - strlen(text);
    printf("%*s%s%*s", pad1, " ", text, pad2, " ");
}

void print_menu(void)
{
    printf("1 - Вывод справки по ключевому слову С++ (Hash-Таблица)\n");
    printf("2 - Вывод справки по ключевому слову С++ (AVL-Дерево)\n");

    printf("3 - Вычисление времени поиска (Hash-Таблица)\n");
    printf("4 - Вычисление времени поиска (AVL-Дерево)\n");
    printf("5 - Вычисление времени поиска (ДДП-Дерево)\n");

    printf("6 - Вывод Hash-Таблицы\n");
    printf("7 - Реструктуризация Hash-Таблицы\n");

    printf("8 - Тестирование Hash-Таблицы при разном проценте коллизий\n");
    printf("9 - Изменить поведение при коллизии\n");
    printf("\n0 - Выход из программы\n");
}

// trc-ignore
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

// trc-ignore
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

// trc-ignore
int get_input_num(char str[], unsigned max_length, int *num)
{
    int rc = get_input(str, max_length);
    if (rc == RETURN_SUCCESS)
    {
        if (is_integer(str))
        {
            *num = atoi(str);
            return RETURN_SUCCESS;
        }
    }
    return RETURN_INPUT_ERROR;
}

// trc-ignore
void print_table_middle(int size, char *key, char *value)
{
    char temp_str[13];
    (void)value;

    printf("|");
    sprintf(temp_str, "%d", size);
    center_text(temp_str, 12);

    printf("|");
    sprintf(temp_str, "%s", key);
    center_text(temp_str, 12);
    printf("|\n");
}
