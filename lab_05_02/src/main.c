#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"
#include "../inc/queue_funcs.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

struct allocated_data_s global_data;

//#define repeat(x) for (int __i__ = 0; __i__ < x; __i__++)

// trc-ignore
void print_menu(void)
{
    printf("\n");

    printf("1 - Вывод очереди\n");
    printf("2 - Добавить элемент\n");
    printf("3 - Удалить элемент\n");
    printf("4 - Моделирование ОА (массив)\n");
    printf("5 - Моделирование ОА (список)\n");
    printf("6 - Тестирование эффективности\n");
    printf("7 - Изменить время ОА\n");

    printf("0 - Выход из программы\n\n");

    // printf("D - Генерация очереди\n");
    printf("F - Прочитать из файла\n");
    printf("\n");
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

// trc-ignore
void center_text(char *text, int width)
{
    int pad1 = (width - strlen(text)) / 2;
    int pad2 = width - pad1 - strlen(text);
    printf("%*s%s%*s", pad1, " ", text, pad2, " ");
}

// trc-ignore
void print_table_middle(int percent, unsigned long long time1, unsigned long long time2, int mem1, int mem2)
{
    char temp_str[50];
    printf("|");
    sprintf(temp_str, "%d", percent);
    center_text(temp_str, 12);

    printf("|");
    sprintf(temp_str, "%llu ms", time1);
    center_text(temp_str, 12);

    printf("|");
    sprintf(temp_str, "%d", mem1);
    center_text(temp_str, 11);

    printf("|");
    sprintf(temp_str, "%llu ms", time2);
    center_text(temp_str, 12);

    printf("|");
    sprintf(temp_str, "%d", mem2);
    center_text(temp_str, 11);

    printf("|\n");
}

int main(void)
{
    srand(time(NULL));
    int rc = init_global_data();
    if (!rc)
        terminate_program(rc);

    queue_arr_t queue_arr;
    list_t queue_list;
    int working = 1;
    char input[INPUT_BUFFER];

    int *list_free_val;
    void **list_free_adr;
    int list_free_total = 0;

    double t1_time[2];
    double t2_time[2];

    double t1_ao_time[2];
    double t2_ao_time[2];

    t1_time[0] = 1;
    t1_time[1] = 5;

    t2_time[0] = 0;
    t2_time[1] = 3;

    t1_ao_time[0] = 0;
    t1_ao_time[1] = 4;

    t2_ao_time[0] = 0;
    t2_ao_time[1] = 1;

    list_free_val = my_malloc(100 * sizeof(int));
    if (!list_free_val)
        terminate_program(RETURN_MEMORY_ERROR);

    list_free_adr = my_malloc(100 * sizeof(void *));
    if (!list_free_adr)
        terminate_program(RETURN_MEMORY_ERROR);

    if (init_list(&queue_list) != RETURN_SUCCESS || init_queue_array(&queue_arr, QUEUE_SIZE) != RETURN_SUCCESS)
        terminate_program(RETURN_MEMORY_ERROR);

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
                printf("Размер списка: %d\n", queue_list.total);

                if (queue_list.total > 0)
                {
                    printf("Список:\n");
                    print_queue_list(queue_list);
                    printf("\n");
                }

                if (list_free_total > 0)
                {
                    printf("Освобожденные значения:\n");
                    for (int i = 0; i < list_free_total; i++)
                    {
                        printf("\033[0;34m%5d\033[0m\n     (адрес: %p)\n", list_free_val[i], list_free_adr[i]);
                    }
                }

                printf("\nРазмер массива: %d\n", queue_arr.total);

                if (queue_arr.total > 0)
                {
                    printf("Массив:\n");
                    print_queue_array(queue_arr);
                    printf("\n");
                }
            }
            else if (strcmp(input, "2") == 0)
            {
                int num_to_add;

                printf("Введите целое число: ");
                rc = get_input_num(input, INPUT_BUFFER, &num_to_add);
                if (rc == RETURN_SUCCESS)
                {
                    if (queue_arr.total < QUEUE_SIZE)
                    {
                        rc = queue_list_push(&queue_list, num_to_add);
                        if (rc != RETURN_SUCCESS)
                        {
                            printf("Ошибка выделения памяти\n");
                        }
                        else
                        {
                            queue_array_push(&queue_arr, num_to_add);
                        }
                    }
                    else
                    {
                        printf("\033[0;34mОчередь переполнена\033[0m\n");
                    }
                }
                else
                {
                    printf("\033[0;34mНеверный ввод\033[0m\n");
                }
            }
            else if (strcmp(input, "3") == 0)
            {
                if (queue_list.total > 0)
                {
                    double val;
                    void *adress;
                    list_get_info(&queue_list, 0, &val, &adress);

                    // list_remove_last(&stack_list);
                    double tmp;
                    queue_array_pop(&queue_arr, &tmp);
                    queue_list_pop(&queue_list, &tmp);

                    printf("В списке удалён элемент со значением %lf, по адресу %p\n", val, adress);

                    if (list_free_total == 100)
                    {
                        list_free_total = 0;
                    }
                    list_free_adr[list_free_total] = adress;
                    list_free_val[list_free_total] = val;

                    list_free_total++;
                }
                else
                {
                    printf("\033[0;34mОчередь уже пуст\033[0m\n");
                }
            }
            else if (strcmp(input, "4") == 0)
            {
                printf("Введите размер очереди (по умолчанию 1000):\n");
                int size;
                rc = get_input_num(input, INPUT_BUFFER, &size);
                if (rc != RETURN_SUCCESS || size < 1)
                    size = QUEUE_SIZE;
                printf("Размер: %d...\n", size);

                queue_arr_t queue_t1_arr;
                queue_arr_t queue_t2_arr;

                process_list_t arr_process;
                arr_process.get_total = get_total_array;
                arr_process.pop_func = queue_array_pop;
                arr_process.push_func = queue_array_push;
                arr_process.calc_info = calc_info_array;
                for (int i = 0; i < 2; i++)
                {
                    arr_process.t1_time[i] = t1_time[i];
                    arr_process.t2_time[i] = t2_time[i];

                    arr_process.t1_ao_time[i] = t1_ao_time[i];
                    arr_process.t2_ao_time[i] = t2_ao_time[i];
                }

                if (init_queue_array(&queue_t1_arr, size) != RETURN_SUCCESS ||
                    init_queue_array(&queue_t2_arr, size) != RETURN_SUCCESS)
                    terminate_program(RETURN_MEMORY_ERROR);

                int index = global_data.total - 2;

                rc = calc_ao(&queue_t1_arr, &queue_t2_arr, &arr_process, 1, 1000);
                if (rc != RETURN_SUCCESS)
                    terminate_program(rc);

                for (int i = 0; i < 2; i++)
                {
                    free_memory_index(index);
                }
            }
            else if (strcmp(input, "5") == 0)
            {
                list_t queue_t1_list;
                list_t queue_t2_list;

                process_list_t list_process;
                list_process.get_total = get_total_list;
                list_process.pop_func = queue_list_pop;
                list_process.push_func = queue_list_push;
                list_process.calc_info = calc_info_list;
                for (int i = 0; i < 2; i++)
                {
                    list_process.t1_time[i] = t1_time[i];
                    list_process.t2_time[i] = t2_time[i];

                    list_process.t1_ao_time[i] = t1_ao_time[i];
                    list_process.t2_ao_time[i] = t2_ao_time[i];
                }

                if (init_list(&queue_t1_list) != RETURN_SUCCESS || init_list(&queue_t2_list) != RETURN_SUCCESS)
                {
                    terminate_program(RETURN_MEMORY_ERROR);
                }

                int index = global_data.total - 2;

                rc = calc_ao(&queue_t1_list, &queue_t2_list, &list_process, 1, 1000);
                if (rc != RETURN_SUCCESS)
                    terminate_program(rc);

                for (int i = 0; i < 2; i++)
                {
                    free_memory_index(index);
                }
            }
            else if (strcmp(input, "6") == 0)
            {
                printf("Введите размер очереди (по умолчанию 1000):\n");
                int size;

                rc = get_input_num(input, INPUT_BUFFER, &size);
                if (rc != RETURN_SUCCESS || size < 1)
                    size = QUEUE_SIZE;

                printf("Размер: %d...\n", size);

                int rep_count = 20;
                queue_arr_t queue_t1_arr;
                queue_arr_t queue_t2_arr;

                list_t queue_t1_list;
                list_t queue_t2_list;

                process_list_t arr_process;
                arr_process.get_total = get_total_array;
                arr_process.pop_func = queue_array_pop;
                arr_process.push_func = queue_array_push;
                arr_process.calc_info = calc_info_array;
                for (int i = 0; i < 2; i++)
                {
                    arr_process.t1_time[i] = t1_time[i];
                    arr_process.t2_time[i] = t2_time[i];

                    arr_process.t1_ao_time[i] = t1_ao_time[i];
                    arr_process.t2_ao_time[i] = t2_ao_time[i];
                }

                process_list_t list_process;
                list_process.get_total = get_total_list;
                list_process.pop_func = queue_list_pop;
                list_process.push_func = queue_list_push;
                list_process.calc_info = calc_info_list;
                for (int i = 0; i < 2; i++)
                {
                    list_process.t1_time[i] = t1_time[i];
                    list_process.t2_time[i] = t2_time[i];

                    list_process.t1_ao_time[i] = t1_ao_time[i];
                    list_process.t2_ao_time[i] = t2_ao_time[i];
                }

                if (init_list(&queue_t1_list) != RETURN_SUCCESS || init_list(&queue_t2_list) != RETURN_SUCCESS)
                {
                    terminate_program(RETURN_MEMORY_ERROR);
                }

                if (init_queue_array(&queue_t1_arr, size) != RETURN_SUCCESS ||
                    init_queue_array(&queue_t2_arr, size) != RETURN_SUCCESS)
                    terminate_program(RETURN_MEMORY_ERROR);

                int index = global_data.total - 4;

                for (int i = 0; i < 10; i++)
                {
                    arr_process.time[i] = 0;
                    list_process.time[i] = 0;
                }

                // printf("Массив: \n");

                for (int i = 0; i < rep_count; i++)
                {
                    // printf("TEST");
                    rc = calc_ao(&queue_t1_arr, &queue_t2_arr, &arr_process, 0, size);
                    if (rc != RETURN_SUCCESS)
                        terminate_program(rc);

                    // printf("\n\nСпысок: \n");
                    rc = calc_ao(&queue_t1_list, &queue_t2_list, &list_process, 0, size);
                    if (rc != RETURN_SUCCESS)
                        terminate_program(rc);
                }

                char sss[] = "Максимальная требуемая память под массив (для 1 очереди): %lu\n";
                printf(sss, sizeof(double) * size + sizeof(queue_arr_t));

                char ss[] = "Максимальная требуемая память под список (для 1 очереди): %lu\n";
                printf(ss, sizeof(list_t) + size * sizeof(list_node));

                printf("+------------+------------------------+------------------------+\n");
                printf("|            |          LIST          |          ARRAY         |\n");
                printf("|   READY    |------------+-----------|------------+-----------|\n");
                printf("|            |    TIME    |   MEMORY  |    TIME    |   MEMORY  |\n");
                printf("+------------+------------+-----------+------------+-----------+\n");

                for (int i = 0; i < 10; i++)
                {
                    int v = (i + 1) * size / 10;
                    size_t t = list_process.time[i] / rep_count;
                    size_t t2 = arr_process.time[i] / rep_count;
                    print_table_middle(v, t, t2, list_process.memory[i], arr_process.memory[i]);
                }

                printf("+------------+------------+-----------+------------+-----------+\n");

                for (int i = 0; i < 4; i++)
                {
                    free_memory_index(index);
                }
            }
            else if (strcmp(input, "7") == 0)
            {
                int test_num;

                for (int i = 0; i < 1; i++)
                {
                    printf("Введите минимальное время появления элемента 1 очереди:\n");
                    rc = get_input_num(input, INPUT_BUFFER, &test_num);
                    if (rc != RETURN_SUCCESS)
                        break;
                    t1_time[0] = test_num;
                    printf("Введите максимальное время появления элемента 1 очереди:\n");
                    rc = get_input_num(input, INPUT_BUFFER, &test_num);
                    if (rc != RETURN_SUCCESS)
                        break;
                    t1_time[1] = test_num;
                    printf("Введите минимальное время появления элемента 2 очереди:\n");
                    rc = get_input_num(input, INPUT_BUFFER, &test_num);
                    if (rc != RETURN_SUCCESS)
                        break;
                    t2_time[0] = test_num;
                    printf("Введите максимальное время появления элемента 2 очереди:\n");
                    rc = get_input_num(input, INPUT_BUFFER, &test_num);
                    if (rc != RETURN_SUCCESS)
                        break;
                    t2_time[1] = test_num;

                    printf("Введите минимальное время выхода из ОА элемента 1 очереди:\n");
                    rc = get_input_num(input, INPUT_BUFFER, &test_num);
                    if (rc != RETURN_SUCCESS)
                        break;
                    t1_ao_time[0] = test_num;
                    printf("Введите максимальное время выхода из ОА элемента 1 очереди:\n");
                    rc = get_input_num(input, INPUT_BUFFER, &test_num);
                    if (rc != RETURN_SUCCESS)
                        break;
                    t1_ao_time[1] = test_num;
                    printf("Введите минимальное время выхода из ОА элемента 2 очереди:\n");
                    rc = get_input_num(input, INPUT_BUFFER, &test_num);
                    if (rc != RETURN_SUCCESS)
                        break;
                    t2_ao_time[0] = test_num;
                    printf("Введите максимальное время выхода из ОА элемента 2 очереди:\n");
                    rc = get_input_num(input, INPUT_BUFFER, &test_num);
                    if (rc != RETURN_SUCCESS)
                        break;
                    t2_ao_time[1] = test_num;
                }
            }
            /*else if (strcmp(input, "D") == 0)
            {
                free_memory_value(&stack_list);
                rc = init_list(&stack_list);
                if (rc != RETURN_SUCCESS)
                    terminate_program(RETURN_MEMORY_ERROR);
                queue_arr.total = ARRAY_SIZE;

                for (int i = 0; i < ARRAY_SIZE; i++)
                {
                    int num_to_add = rand() % 1000;

                    rc = stack_list_push(&stack_list, num_to_add);
                    if (rc != RETURN_SUCCESS)
                    {
                        printf("Ошибка выделения памяти\n");
                        break;
                    }
                    else
                    {
                        stack_array[i] = num_to_add;
                    }
                }
            }*/
            else if (strcmp(input, "F") == 0)
            {
                int num_to_add;
                FILE *f = NULL;

                printf("Введите путь к файлу:\n");

                rc = get_input(input, INPUT_BUFFER);
                if (rc == RETURN_SUCCESS)
                    f = fopen(input, "r");
                if (f != NULL)
                {
                    rc = fscanf(f, "%d", &num_to_add);
                    while (!feof(f) && rc == 1)
                    {
                        if (queue_arr.total < QUEUE_SIZE)
                        {
                            rc = queue_list_push(&queue_list, num_to_add);
                            if (rc != RETURN_SUCCESS)
                            {
                                printf("Ошибка выделения памяти\n");
                            }
                            else
                            {
                                queue_array_push(&queue_arr, num_to_add);
                            }
                        }
                        else
                        {
                            printf("\033[0;34mОчередь переполнена\033[0m\n");
                        }
                        rc = fscanf(f, "%d", &num_to_add);
                    }
                    if (!feof(f) || queue_arr.total == 0)
                    {
                        printf("\033[0;34mОшибка в содержимом файла\033[0m\n");
                        queue_arr.total = 0;
                        double tmp;
                        while (queue_list.total > 0)
                            queue_list_pop(&queue_list, &tmp);
                    }
                }
                else
                {
                    printf("\033[0;34mОшибка открытия файла\033[0m\n");
                }
            }
        }
    }

    /*queue_arr_t queue_t1_arr;
    queue_arr_t queue_t2_arr;

    list_t queue_t1_list;
    list_t queue_t2_list;

    process_list_t arr_process;
    arr_process.get_total = get_total_array;
    arr_process.pop_func = queue_array_pop;
    arr_process.push_func = queue_array_push;
    arr_process.calc_info = calc_info_array;

    process_list_t list_process;
    list_process.get_total = get_total_list;
    list_process.pop_func = queue_list_pop;
    list_process.push_func = queue_list_push;
    list_process.calc_info = calc_info_list;

    if (init_list(&queue_t1_list) != RETURN_SUCCESS || init_list(&queue_t2_list) != RETURN_SUCCESS)
    {
        terminate_program(RETURN_MEMORY_ERROR);
    }

    if (init_queue_array(&queue_t1_arr) != RETURN_SUCCESS || init_queue_array(&queue_t2_arr) != RETURN_SUCCESS)
        terminate_program(RETURN_MEMORY_ERROR);

    printf("Массив: \n");
    rc = calc_ao(&queue_t1_arr, &queue_t2_arr, &arr_process);
    if (rc != RETURN_SUCCESS)
        terminate_program(rc);

    printf("\n\nСпысок: \n");
    calc_ao(&queue_t1_list, &queue_t2_list, &list_process);
    if (rc != RETURN_SUCCESS)
        terminate_program(rc);

    printf("+------------+------------------------+------------------------+\n");
    printf("|            |          LIST          |          ARRAY         |\n");
    printf("|   READY    |------------+-----------|------------+-----------|\n");
    printf("|            |    TIME    |   MEMORY  |    TIME    |   MEMORY  |\n");
    printf("+------------+------------+-----------+------------+-----------+\n");

    for (int i = 0; i < 10; i++)
    {
        print_table_middle((i + 1) * 100, list_process.time[i], arr_process.time[i], list_process.memory[i],
                           arr_process.memory[i]);
    }

    printf("+------------+------------+-----------+------------+-----------+\n");*/

    terminate_program(RETURN_SUCCESS);
}