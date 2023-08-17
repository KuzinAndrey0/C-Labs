
#include "../inc/queue_funcs.h"
#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

double random_range(double min, double max)
{
    double diff = max - min;
    double frac = (float)rand() / (float)(RAND_MAX / diff);

    return frac + min;
}

unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long)-1;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

unsigned long calc_info_array(void *queue_p)
{
    queue_arr_t *queue = (queue_arr_t *)queue_p;
    (void)queue;

    return sizeof(double) * queue->max + sizeof(queue_arr_t);
}

unsigned long calc_info_list(void *queue_p)
{
    list_t *queue = (list_t *)queue_p;

    return sizeof(list_t) + queue->total * sizeof(list_node);
}

int queue_array_push(void *queue_p, double val)
{
    queue_arr_t *queue = (queue_arr_t *)queue_p;
    if (queue->total >= queue->max)
        return RETURN_QUEUE_OVERFLOW;

    *(queue->ptr_end) = val;
    queue->ptr_end++;

    if ((queue->ptr_end - queue->val) >= queue->max)
        queue->ptr_end -= queue->max;

    queue->total++;

    return RETURN_SUCCESS;
}

int queue_array_pop(void *queue_p, double *val)
{
    queue_arr_t *queue = (queue_arr_t *)queue_p;
    if (queue->total <= 0)
        return RETURN_QUEUE_OVERFLOW;

    *val = *(queue->ptr_start);
    queue->ptr_start++;

    if ((queue->ptr_start - queue->val) >= QUEUE_SIZE)
        queue->ptr_start -= QUEUE_SIZE;
    queue->total--;

    return RETURN_SUCCESS;
}

int init_queue_array(queue_arr_t *queue, size_t size)
{
    double *queue_array_vals;
    queue_array_vals = my_malloc(size * sizeof(double));
    if (queue_array_vals == NULL)
        return RETURN_MEMORY_ERROR;
    queue->val = queue_array_vals;
    queue->ptr_start = queue->val;
    queue->ptr_end = queue->ptr_start;
    queue->total = 0;
    queue->max = size;

    return RETURN_SUCCESS;
}

void print_queue_array(queue_arr_t queue)
{
    // printf("TOTAL: %d\n", queue.total);

    double *tmp_ptr;
    tmp_ptr = queue.ptr_start;

    printf("\033[0;34m");
    for (int i = 0; i < queue.total; i++)
    {
        double val = *(tmp_ptr);
        tmp_ptr++;

        if ((tmp_ptr - queue.val) >= QUEUE_SIZE)
            tmp_ptr -= QUEUE_SIZE;

        printf("%.0f ", val);
    }
    printf("\033[0m\n");
}

int queue_list_push(void *queue_p, double val)
{
    list_t *queue = (list_t *)queue_p;
    list_node *new_node = malloc(sizeof(list_node));

    if (new_node == NULL)
    {
        return RETURN_MEMORY_ERROR;
    }
    new_node->next = NULL;
    new_node->data = val;

    if (queue->tail == NULL)
    {
        queue->head = new_node;
    }
    else
    {
        queue->tail->next = new_node;
    }
    queue->tail = new_node;
    queue->total++;

    return RETURN_SUCCESS;
}

int queue_list_pop(void *queue_p, double *val)
{
    list_t *queue = (list_t *)queue_p;
    if (queue->total == 0)
        return RETURN_QUEUE_OVERFLOW;

    *val = queue->head->data;

    list_node *ptr = queue->head;

    queue->head = queue->head->next;
    queue->total--;
    if (queue->total == 0)
        queue->tail = NULL;

    free(ptr);

    return RETURN_SUCCESS;
}

void print_queue_list(list_t queue)
{
    // printf("TOTAL: %d\n", queue.total);
    list_node *ptr = queue.head;
    printf("\033[0;34m");
    while (ptr != NULL)
    {
        printf("%.0f ", ptr->data);
        ptr = ptr->next;
    }
    printf("\033[0m\n");
}

int get_total_array(void *arr)
{
    return ((queue_arr_t *)arr)->total;
}

int get_total_list(void *list)
{
    return ((list_t *)list)->total;
}

int calc_ao(void *queue_t1, void *queue_t2, process_list_t *process_funcs, int print, int size)
{
    int (*pop_func)(void *, double *) = process_funcs->pop_func;
    int (*push_func)(void *, double) = process_funcs->push_func;
    int (*get_total)(void *) = process_funcs->get_total;
    size_t (*calc_info)(void *) = process_funcs->calc_info;

    double waiting_t1 = 0;
    double waiting_t2 = 0;
    double waiting_ao = 0;
    int ao_type = 0;
    double ao_time = 0;

    // Stats
    int in_t1 = 0;
    int in_t2 = 0;
    int ready_t1 = 0;
    int ready_t2 = 0;
    double total_time = 0;
    double time_t1 = 0;
    double time_t2 = 0;
    ///////

    unsigned long long real_time = milliseconds_now();

    double tmp;

    while (ready_t1 < size)
    {
        if (waiting_t1 <= 0)
        {
            waiting_t1 = random_range(process_funcs->t1_time[0], process_funcs->t1_time[1]);
        }
        if (waiting_t2 <= 0)
        {
            waiting_t2 = random_range(process_funcs->t2_time[0], process_funcs->t2_time[1]);
        }

        if (waiting_ao <= 0)
        {
            ao_type = 0;
            if (get_total(queue_t1) > 0)
            {
                pop_func(queue_t1, &tmp);
                waiting_ao = random_range(process_funcs->t1_ao_time[0], process_funcs->t1_ao_time[1]);
                ao_type = 1;
                ao_time = waiting_ao;
            }
            else if (get_total(queue_t2) > 0)
            {
                pop_func(queue_t2, &tmp);
                waiting_ao = random_range(process_funcs->t2_ao_time[0], process_funcs->t2_ao_time[1]);
                ao_type = 2;
                ao_time = waiting_ao;
            }
        }

        double min;

        if (waiting_t1 <= waiting_t2 && (waiting_t1 <= waiting_ao || waiting_ao == 0))
        {
            min = waiting_t1;
        }
        if (waiting_t2 <= waiting_t1 && (waiting_t2 <= waiting_ao || waiting_ao == 0))
        {
            min = waiting_t2;
        }

        if (waiting_ao <= waiting_t1 && waiting_ao <= waiting_t2 && waiting_ao > 0)
        {
            min = waiting_ao;
        }

        waiting_t1 -= min;
        waiting_t2 -= min;
        waiting_ao -= min;
        total_time += min;

        if (waiting_t1 <= 0)
        {
            in_t1++;
            int rc = push_func(queue_t1, random_range(1, 100));
            if (rc != RETURN_SUCCESS)
            {
                printf("Переполнение очереди 1\n");
                return RETURN_MEMORY_ERROR;
            }
        }
        if (waiting_t2 <= 0)
        {
            in_t2++;
            int rc = push_func(queue_t2, random_range(1, 100));
            if (rc != RETURN_SUCCESS)
            {
                printf("Переполнение очереди 2\n");
                return RETURN_MEMORY_ERROR;
            }
        }
        if (waiting_ao <= 0)
        {
            if (ao_type == 1)
            {
                time_t1 += ao_time;
                ready_t1++;
                if (ready_t1 % (size / 10) == 0)
                {
                    int index = ready_t1 / (size / 10) - 1;
                    process_funcs->time[index] += (milliseconds_now() - real_time);

                    process_funcs->memory[index] = calc_info(queue_t1);
                    process_funcs->memory[index] += calc_info(queue_t2);

                    if (print)
                    {
                        printf("%d:\n", ready_t1);
                        printf("Кол-во элементов в 1 очереди: %d\n", get_total(queue_t1));
                        printf("Кол-во элементов во 2 очереди: %d\n\n", get_total(queue_t2));
                    }

                    real_time = milliseconds_now();
                }
            }
            if (ao_type == 2)
            {
                time_t2 += ao_time;
                ready_t2++;
            }
            ao_type = 0;
        }
    }
    if (print)
    {
        printf("Всего затрачено времени: %lf\n\n", total_time);
        printf("Заявок 1 типа вошло: %d \n", in_t1);
        printf("Заявок 2 типа вошло: %d \n\n", in_t2);

        printf("Заявок 1 типа вышло: %d \n", ready_t1);
        printf("Заявок 2 типа вышло: %d \n\n", ready_t2);

        double ideal_t1 = (double)(process_funcs->t1_ao_time[0] + process_funcs->t1_ao_time[1]) / 2;
        double ideal_t2 = (double)(process_funcs->t2_ao_time[0] + process_funcs->t2_ao_time[1]) / 2;

        // printf("IDEAL T1: %lf\n", ideal_t1);

        double real_t1 = time_t1 / ready_t1;
        double real_t2 = time_t2 / ready_t2;

        // printf("REAL T1: %lf\n", real_t1);

        double diff_t1 = fabs(1 - real_t1 / ideal_t1) * 100;
        double diff_t2 = fabs(1 - real_t2 / ideal_t2) * 100;

        printf("Расхождение заявок 1 типа:\n\033[0;34m%.2lf%%\033[0m\n", diff_t1);
        printf("Расхождение заявок 2 типа:\n\033[0;34m%.2lf%%\033[0m\n\n", diff_t2);

        printf("Затрачено на обработку заявок 1 типа: %lf \n", time_t1);
        printf("Затрачено на обработку заявок 2 типа: %lf \n\n", time_t2);

        printf("Время простоя: %lf\n", total_time - time_t1 - time_t2);
    }

    return RETURN_SUCCESS;
}
