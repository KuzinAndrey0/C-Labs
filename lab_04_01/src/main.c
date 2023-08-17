#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"
#include "../inc/stack_handle.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

//#define UNNECESSARY_PRINT 0

#define ARRAY_SIZE 40

// trc-ignore
void print_menu(void)
{
    printf("\n");

    printf("1 - Вывод стека\n");
    printf("2 - Добавить элемент\n");
    printf("3 - Удалить элемент\n");
    printf("4 - Убывающие серии последовательности чисел в обратном порядке\n");
    printf("5 - Провести тестирование\n");

    printf("0 - Выход из программы\n\n");

    printf("D - Генерация стека\n");
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
        if (is_integer(str))
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

// trc-ignore
void print_sequence_list(list_t *stack_list, int do_print)
{
    int *array_tmp;
    int array_tmp_pos = 0;

    array_tmp = my_malloc(stack_list->total * sizeof(int));
    if (array_tmp == NULL)
        terminate_program(RETURN_MEMORY_ERROR);

    // list_t stack_tmp;
    // list_t stack_rev;

    // int rc = init_list(&stack_tmp);
    // if (rc != RETURN_SUCCESS)
    //     terminate_program(RETURN_MEMORY_ERROR);

    // rc = init_list(&stack_rev);
    // if (rc != RETURN_SUCCESS)
    //     terminate_program(RETURN_MEMORY_ERROR);

    // while (stack_list->total > 0)
    // {
    //     stack_list_push(&stack_rev, stack_list_pop(stack_list));
    // }

    int last_val = 0;
    if (do_print)
        printf("\033[0;34m");
    while (stack_list->total > 0)
    {
        int new_val = stack_list_pop(stack_list);
        // printf("%d < %d ?\n", last_val, new_val);

        if (array_tmp_pos == 0 || last_val < new_val)
        {
            // printf("adding %d\n", new_val);
            array_tmp[array_tmp_pos] = new_val;
            array_tmp_pos++;
        }
        else
        {

            if (array_tmp_pos == 1)
            {
                array_tmp_pos = 0;
                array_tmp[array_tmp_pos] = new_val;
                array_tmp_pos++;
            }
            else
            {
                if (do_print)
                {
                    for (int i = 0; i < array_tmp_pos; i++)
                    {
                        printf("%d ", array_tmp[array_tmp_pos - i - 1]);
                    }
                }
                if (do_print)
                    printf("\n");
                array_tmp_pos = 0;
                array_tmp[array_tmp_pos] = new_val;
                array_tmp_pos++;
            }
        }
        last_val = new_val;
    }
    if (do_print && array_tmp_pos <= 1)
        printf("\033[0m\n");

    if (array_tmp_pos > 1)
    {
        if (do_print)
        {
            for (int i = 0; i < array_tmp_pos; i++)
            {
                printf("%d ", array_tmp[array_tmp_pos - i - 1]);
            }
            printf("\n");
        }
    }
    if (do_print)
        printf("\033[0m\n");
    free_memory_value(array_tmp);
    // free_memory_value(&stack_rev);
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
void print_sequence_array(int *stack_array, int *stack_pos, int do_print)
{
    int *array_tmp;
    int array_tmp_pos = 0;

    array_tmp = my_malloc(*stack_pos * sizeof(int));
    if (array_tmp == NULL)
        terminate_program(RETURN_MEMORY_ERROR);

    int last_val = 0;
    if (do_print)
        printf("\033[0;34m");
    while (*stack_pos > 0)
    {
        int new_val = stack_array_pop(stack_array, stack_pos);

        if (array_tmp_pos == 0 || last_val < new_val)
        {
            array_tmp[array_tmp_pos] = new_val;
            array_tmp_pos++;
        }
        else
        {

            if (array_tmp_pos == 1)
            {
                array_tmp_pos = 0;
                array_tmp[array_tmp_pos] = new_val;
                array_tmp_pos++;
            }
            else
            {
                if (do_print)
                {
                    for (int i = 0; i < array_tmp_pos; i++)
                    {
                        printf("%d ", array_tmp[array_tmp_pos - i - 1]);
                    }
                    if (do_print)
                        printf("\n");
                }
                array_tmp_pos = 0;
                array_tmp[array_tmp_pos] = new_val;
                array_tmp_pos++;
            }
        }
        last_val = new_val;
    }
    if (do_print && array_tmp_pos <= 1)
        printf("\033[0m\n");

    if (array_tmp_pos > 1)
    {
        if (do_print)
        {
            for (int i = 0; i < array_tmp_pos; i++)
            {
                printf("%d ", array_tmp[array_tmp_pos - i - 1]);
            }
            printf("\n");
        }
    }
    if (do_print)
        printf("\033[0m\n");

    free_memory_value(array_tmp);
}

int main(void)
{
    srand(time(NULL));
    int rc = init_global_data();
    if (!rc)
        terminate_program(RETURN_MEMORY_ERROR);

    list_t stack_list;
    int *stack_array;
    int stack_array_pos = 0;
    int working = 1;
    char input[INPUT_BUFFER];

    int *list_free_val;
    void **list_free_adr;
    int list_free_total = 0;

    rc = init_list(&stack_list);
    if (rc != RETURN_SUCCESS)
        terminate_program(RETURN_MEMORY_ERROR);

    list_free_val = my_malloc(100 * sizeof(int));
    if (!list_free_val)
        terminate_program(RETURN_MEMORY_ERROR);

    list_free_adr = my_malloc(100 * sizeof(void *));
    if (!list_free_adr)
        terminate_program(RETURN_MEMORY_ERROR);

    stack_array = my_malloc(ARRAY_SIZE * sizeof(int));
    if (!stack_array)
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
                printf("Размер списка: %d\n", stack_list.total);

                if (stack_list.total > 0)
                {
                    printf("Список:\n");

                    list_node *ptr = stack_list.head;
                    while (ptr != NULL)
                    {
                        list_node *tmp = ptr->next;

                        printf("\033[0;34m%5d\033[0m\n     (адрес: %p)\n", ptr->value, (void *)ptr);

                        ptr = tmp;
                    }
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

                printf("\nРазмер массива: %d\n", stack_array_pos);

                if (stack_array_pos > 0)
                {
                    printf("Массив:\n");

                    for (int i = stack_array_pos - 1; i >= 0; i--)
                    {
                        printf("\033[0;34m%5d\033[0m\n     (адрес: %p)\n", stack_array[i], (void *)&stack_array[i]);
                    }

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
                    if (stack_array_pos < ARRAY_SIZE)
                    {
                        rc = stack_list_push(&stack_list, num_to_add); // list_add_last(&stack_list, num_to_add);
                        if (rc != RETURN_SUCCESS)
                        {
                            printf("Ошибка выделения памяти\n");
                        }
                        else
                        {
                            stack_array[stack_array_pos] = num_to_add;
                            stack_array_pos++;
                        }
                    }
                    else
                    {
                        printf("\033[0;34mСтек переполнен\033[0m\n");
                    }
                }
                else
                {
                    printf("\033[0;34mНеверный ввод\033[0m\n");
                }
            }
            else if (strcmp(input, "3") == 0)
            {
                if (stack_list.total > 0)
                {
                    int val;
                    void *adress;
                    list_get_info(&stack_list, 0, &val, &adress);

                    // list_remove_last(&stack_list);
                    stack_list_pop(&stack_list);

                    stack_array[stack_array_pos - 1] = 0;
                    stack_array_pos--;

                    printf("В списке удалён элемент со значением %d, по адресу %p\n", val, adress);

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
                    printf("\033[0;34mСтек уже пуст\033[0m\n");
                }
            }
            else if (strcmp(input, "4") == 0)
            {
                unsigned long long time[2];
                unsigned long long start, end;

                printf("Последовательности (список):\n");

                start = milliseconds_now();
                print_sequence_list(&stack_list, 1);
                end = milliseconds_now();
                time[0] = end - start;

                printf("\nПоследовательности (массив):\n");

                start = milliseconds_now();
                print_sequence_array(stack_array, &stack_array_pos, 1);
                end = milliseconds_now();
                time[1] = end - start;

                printf("Время работы со списком: %llu\n", time[0]);
                printf("Время работы с массивом: %llu\n", time[1]);
            }
            else if (strcmp(input, "5") == 0)
            {
                unsigned long long time[2];
                unsigned long long memory[2];
                unsigned long long start, end;

                int rep_count = 10;

                free_memory_value(&stack_list);
                rc = init_list(&stack_list);
                if (rc != RETURN_SUCCESS)
                    terminate_program(RETURN_MEMORY_ERROR);

                stack_array_pos = 0;

                printf("+------------+------------------------+------------------------+\n");
                printf("|            |          LIST          |          ARRAY         |\n");
                printf("|    SIZE    |------------+-----------|------------+-----------|\n");
                printf("|            |    TIME    |   MEMORY  |    TIME    |   MEMORY  |\n");
                printf("+------------+------------+-----------+------------+-----------+\n");

                for (int size = ARRAY_SIZE / 10; size <= ARRAY_SIZE; size += ARRAY_SIZE / 10)
                {
                    FILE *f1, *f2;

                    time[0] = 0;
                    time[1] = 0;
                    for (int i = 0; i < rep_count; i++)
                    {
                        f1 = fopen("test1.txt", "w");
                        f2 = fopen("test2.txt", "w");

                        stack_array_pos = size;
                        for (int i = 0; i < size; i++)
                        {
                            int num_to_add = rand() % 1000;
                            stack_list_push(&stack_list, num_to_add);
                            stack_array[i] = num_to_add;
                        }

                        start = milliseconds_now();
                        print_sequence_list(&stack_list, 0);
                        end = milliseconds_now();
                        time[0] = time[0] + end - start;

                        start = milliseconds_now();
                        print_sequence_array(stack_array, &stack_array_pos, 0);
                        end = milliseconds_now();
                        time[1] = time[1] + end - start;

                        fclose(f1);
                        fclose(f2);
                    }

                    time[0] /= rep_count;
                    time[1] /= rep_count;

                    memory[0] = sizeof(list_t) + sizeof(list_node) * size;
                    memory[1] = sizeof(int) * size;

                    print_table_middle(size, time[0], time[1], memory[0], memory[1]);
                    // printf("%8llu %8llu %8llu %8llu\n", time[0], time[1], memory[0], memory[1]);
                }

                printf("+------------+------------+-----------+------------+-----------+\n\n");
                printf("Использование массива быстрее в %lf раз\n", (double)time[0] / time[1]);
                printf("Использование массива занимает меньше памяти в %lf раз\n", (double)memory[0] / memory[1]);
            }
            else if (strcmp(input, "D") == 0)
            {
                free_memory_value(&stack_list);
                rc = init_list(&stack_list);
                if (rc != RETURN_SUCCESS)
                    terminate_program(RETURN_MEMORY_ERROR);
                stack_array_pos = ARRAY_SIZE;

                for (int i = 0; i < ARRAY_SIZE; i++)
                {
                    int num_to_add = rand() % 1000;

                    rc = stack_list_push(&stack_list, num_to_add); // list_add_last(&stack_list, num_to_add);
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
            }
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
                        if (stack_array_pos < ARRAY_SIZE)
                        {
                            rc = stack_list_push(&stack_list, num_to_add); // list_add_last(&stack_list, num_to_add);
                            if (rc != RETURN_SUCCESS)
                            {
                                printf("Ошибка выделения памяти\n");
                            }
                            else
                            {
                                stack_array[stack_array_pos] = num_to_add;
                                stack_array_pos++;
                            }
                        }
                        else
                        {
                            printf("Стек переполнен\n");
                        }
                        rc = fscanf(f, "%d", &num_to_add);
                    }
                    if (!feof(f) || stack_array_pos == 0)
                    {
                        printf("\033[0;34mОшибка в содержимом файла\033[0m\n");
                        stack_array_pos = 0;
                        while (stack_list.total > 0)
                            stack_list_pop(&stack_list);
                    }
                }
                else
                {
                    printf("\033[0;34mОшибка открытия файла\033[0m\n");
                }
            }
        }
    }

    terminate_program(0);
}

/*if (strcmp(input, "2") == 0) //Добавление в список
{
    int num_to_add;
    printf("Введите число: ");
    rc = get_input_num(input, INPUT_BUFFER, &num_to_add); // scanf("%d", &num_to_add);
    if (rc == RETURN_SUCCESS)
    {
        rc = list_add_last(&stack_list, num_to_add);
        if (rc != RETURN_SUCCESS)
        {
            printf("Ошибка выделения памяти\n");
        }
    }
    else
    {
        printf("Неверный ввод\n");
    }
}
if (strcmp(input, "3") == 0) //Добавление в массив
{
    int num_to_add;
    printf("Введите число: ");
    rc = get_input_num(input, INPUT_BUFFER, &num_to_add);
    if (rc == RETURN_SUCCESS)
    {
        if (stack_array_pos < ARRAY_SIZE)
        {
            stack_array[stack_array_pos] = num_to_add;
            stack_array_pos++;
        }
        else
        {
            printf("Массив переполнен\n");
        }
    }
    else
    {
        printf("Неверный ввод\n");
    }
}*/