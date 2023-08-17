#ifndef __MY_DEFINES__

// trc-ignore
#define __MY_DEFINES__

// trc-ignore
#define RETURN_SUCCESS 0
// trc-ignore
#define RETURN_WRONG_FORMAT 10
// trc-ignore
#define RETURN_EMPTY_FILE 20
// trc-ignore
#define RETURN_NO_FILE 30
// trc-ignore
#define RETURN_MEMORY_ERROR 40
// trc-ignore
#define RETURN_NOT_ENOUGH_ARGUMENTS 50
// trc-ignore
#define RETURN_EMPTY_FILE_AFTER 60
// trc-ignore
#define RETURN_WRONG_ARGUMENTS 70
// trc-ignore
#define RETURN_QUANTITY_NOT_NUM 80
// trc-ignore
#define RETURN_QUEUE_OVERFLOW 90
// trc-ignore
#define RETURN_INPUT_ERROR 100

// trc-ignore
#define INPUT_BUFFER 50

// Размер очереди
#define QUEUE_SIZE 1000

// trc-ignore
#define AO_WORKOUT 1000

// Структура очереди в виде массива
typedef struct queue_arr_t
{
    double *val;       //Память, выделенная под сами значения
    double *ptr_start; //Позиция первого элемента в памяти
    double *ptr_end;   //Позиция последнего элемента в памяти

    int total; //Общее кол-во элементов в памяти
    int max;   //Максимальное кол-во элементов в памяти
} queue_arr_t;

// trc-ignore
typedef struct process_list_t
{
    int (*pop_func)(void *, double *);
    int (*push_func)(void *, double);
    int (*get_total)(void *);
    unsigned long (*calc_info)(void *);

    size_t time[10];
    size_t memory[10];

    double t1_time[2];
    double t2_time[2];

    double t1_ao_time[2];
    double t2_ao_time[2];
} process_list_t;

#endif