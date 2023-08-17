#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"

#ifndef __QUEUE_FUNCS__

// trc-ignore
#define __QUEUE_FUNCS__

// trc-ignore
unsigned long calc_info_array(void *queue_p);
// trc-ignore
unsigned long calc_info_list(void *queue_p);
// Добавление элемента в очередь, представленную в виде массива
int queue_array_push(void *queue_p, double val);
// Удаление элемента из очереди, представленной в виде массива
int queue_array_pop(void *queue_p, double *val);
// trc-ignore
int init_queue_array(queue_arr_t *queue, size_t size);
// trc-ignore
void print_queue_array(queue_arr_t queue);
// Добавление элемента в очередь, представленную в виде списка
int queue_list_push(void *queue_p, double val);
// Удаление элемента из очереди, представленной в виде списка
int queue_list_pop(void *queue_p, double *val);
// trc-ignore
void print_queue_list(list_t queue);
// trc-ignore
int get_total_array(void *arr);
// trc-ignore
int get_total_list(void *list);
// trc-ignore
int calc_ao(void *queue_t1, void *queue_t2, process_list_t *process_funcs, int print, int size);

// trc-ignore
double random_range(double min, double max);
// trc-ignore
unsigned long long milliseconds_now(void);

#endif
