#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"
#include "../inc/tree_funcs.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

struct allocated_data_s global_data;

// trc-ignore
int cmpdate(void *node_1, void *node_2)
{
    file_info node1 = *(file_info *)node_1;
    file_info node2 = *(file_info *)node_2;
    if (node1.year - node2.year != 0)
        return node1.year - node2.year;
    if (node1.month - node2.month != 0)
        return node1.month - node2.month;
    return node1.day - node2.day;
}

// trc-ignore
void center_text(char *text, int width)
{
    int pad1 = (width - strlen(text)) / 2;
    int pad2 = width - pad1 - strlen(text);
    printf("%*s%s%*s", pad1, " ", text, pad2, " ");
}

void print_menu(void)
{
    printf("1 - Вывод дерева в файл\n\n");

    printf("2 - Обход дерева (pre)\n");
    printf("3 - Обход дерева (in)\n");
    printf("4 - Обход дерева (post)\n\n");

    printf("5 - Добавить элемент\n");
    printf("6 - Удалить элемент\n");

    printf("7 - Удалить файлы с временем обращения меньше заданного\n");
    printf("8 - Провести тестирование\n");

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
unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long)-1;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

// trc-ignore
void print_table_middle(int size, double branching, unsigned long long time)
{
    char temp_str[50];
    printf("|");
    sprintf(temp_str, "%d", size);
    center_text(temp_str, 12);

    printf("|");
    sprintf(temp_str, "%.2lf", branching);
    center_text(temp_str, 12);

    printf("|");
    sprintf(temp_str, "%llu ms", time);
    center_text(temp_str, 12);

    printf("|\n");
}

int main(void)
{
    // srand(time(NULL));
    int rc = init_global_data();
    if (!rc)
        terminate_program(rc);

    int working = 1;
    char input[INPUT_BUFFER];

    tree_node *tree_main = NULL;

    FILE *f = fopen("temp.gv", "w");
    tree_export(f, "Temp", tree_main);
    fclose(f);

    for (int i = 0; i < 20; i++)
    {
        int *ptr = my_malloc(sizeof(int));
        *ptr = rand() % 1000;
        if (tree_search(tree_main, ptr, cmp_int) == 1)
        {
            i--;
        }
        else
        {
            insert(&tree_main, ptr, cmp_int);
            FILE *f = fopen("temp.gv", "w");
            tree_export(f, "Temp", tree_main);
            fclose(f);
        }
    }
    free_tree(tree_main);
    tree_main = NULL;

    while (working)
    {
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
                FILE *f = fopen("export.gv", "w");
                tree_export(f, "Результат", tree_main);
                fclose(f);
            }
            else if (strcmp(input, "2") == 0)
            {
                printf("Текущее дерево: \n\n");
                apply_pre(tree_main, print_int, "\033[0;34m%d\033[0m\n");
                printf("\n");
            }
            else if (strcmp(input, "3") == 0)
            {
                printf("Текущее дерево: \n\n");
                apply_in(tree_main, print_int, "\033[0;34m%d\033[0m\n");
                printf("\n");
            }
            else if (strcmp(input, "4") == 0)
            {
                printf("Текущее дерево: \n\n");
                apply_post(tree_main, print_int, "\033[0;34m%d\033[0m\n");
                printf("\n");
            }
            else if (strcmp(input, "5") == 0)
            {
                int num_to_add;

                printf("Введите целое число: ");
                rc = get_input_num(input, INPUT_BUFFER, &num_to_add);
                if (rc == RETURN_SUCCESS)
                {
                    int *ptr = my_malloc(sizeof(int));
                    *ptr = num_to_add;
                    if (tree_search(tree_main, ptr, cmp_int) == 1)
                    {
                        printf("Элемент уже есть в дереве\n");
                    }
                    else
                    {
                        insert(&tree_main, ptr, cmp_int);
                        FILE *f = fopen("temp.gv", "w");
                        tree_export(f, "Temp", tree_main);
                        fclose(f);
                    }
                }
            }
            else if (strcmp(input, "6") == 0)
            {
                int num_to_add;

                printf("Введите целое число: ");
                rc = get_input_num(input, INPUT_BUFFER, &num_to_add);
                if (rc == RETURN_SUCCESS)
                {
                    int *ptr = malloc(sizeof(int));
                    *ptr = num_to_add;

                    int exist = tree_search(tree_main, ptr, cmp_int);
                    if (exist == 0)
                    {
                        printf("\033[0;34mТакого элемента нет\033[0m\n");
                    }
                    else
                    {
                        tree_main = delete_node(tree_main, ptr, cmp_int);
                    }
                    free(ptr);

                    FILE *f = fopen("temp.gv", "w");
                    tree_export(f, "Temp", tree_main);
                    fclose(f);
                }
            }
            else if (strcmp(input, "7") == 0)
            {
                int num;
                printf("Введите кол-во узлов:\n");
                rc = scanf("%d", &num);
                rc = 1;
                if (rc == 0)
                    terminate_program(RETURN_WRONG_ARGUMENTS);

                file_info search_struct;
                printf("Введите последюю дату обращения (ДД ММ ГГГГ): ");
                rc = scanf("%d %d %d", &(search_struct.day), &(search_struct.month), &(search_struct.year));

                if (rc != 3 || search_struct.day < 1 || search_struct.day > 31 || search_struct.month < 1 ||
                    search_struct.month > 12 || search_struct.year < 1 || search_struct.year > 2022)
                {
                    printf("\033[0;34mОшибка ввода\033[0m\n");
                    terminate_program(RETURN_WRONG_FORMAT);
                }

                tree_node *file_tree = NULL;

                for (int i = 0; i < num; i++)
                {
                    file_info *test = my_malloc(sizeof(file_info));
                    test->filename = my_malloc(sizeof(char) * 7);
                    sprintf(test->filename, "TEST%d", i);

                    test->year = (rand() % 30) + 1992;
                    test->month = (rand() % 11) + 1;
                    test->day = (rand() % 29) + 1;
                    insert(&file_tree, test, cmpdate);
                }

                FILE *f = fopen("before.gv", "w");
                tree_export_f(f, "Temp", file_tree);
                fclose(f);

                delete_node_less_than(&file_tree, &search_struct, cmpdate);
                f = fopen("after.gv", "w");
                tree_export_f(f, "Temp", file_tree);
                fclose(f);

                if (num <= 0)
                {
                    printf("\033[0;34mОшибка ввода\033[0m\n");
                    terminate_program(RETURN_WRONG_FORMAT);
                }
            }
            else if (strcmp(input, "8") == 0)
            {
                printf("+------------+------------+------------+\n");
                printf("|    SIZE    |  BRANCHING |     TIME   |\n");
                printf("+------------+------------+------------+\n");
                for (int size = 100; size <= 300; size += 50)
                {
                    for (double branching = 0; branching <= 1; branching += 0.25)
                    {
                        tree_node *test_tree = gen_tree(branching, size);

                        unsigned long long time = milliseconds_now();
                        for (int i = 0; i < 1000; i++)
                            rc = find_non_sorted(test_tree, (rand() % size) + 1);

                        time = milliseconds_now() - time;

                        print_table_middle(size, branching, time);

                        free_tree(test_tree);
                    }
                }
                printf("+------------+------------+------------+\n");
                printf("\033[0;34mУспешно\033[0m\n");
            }
        }
    }

    free_tree(tree_main);
    terminate_program(RETURN_SUCCESS);
}