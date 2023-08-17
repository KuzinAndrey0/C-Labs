#ifndef __MY_DEFINES__

// trc-ignore
#define __MY_DEFINES__

// trc-ignore
#define INPUT_BUFFER 50

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
#define RETURN_INPUT_ERROR 60
// trc-ignore
#define RETURN_QUEUE_OVERFLOW 70
// trc-ignore
#define RETURN_WRONG_HEADER 80
// trc-ignore
#define RETURN_HEADER_CALC 90
// trc-ignore
#define RETURN_WRONG_COORDS 100
// trc-ignore
#define RETURN_SAME_COORDS 110

// trc-ignore
#define QUEUE_SIZE 500

// Структура очереди в виде массива
typedef struct queue_arr_t
{
    int *val;       //Память, выделенная под сами значения
    int *ptr_start; //Позиция первого элемента в памяти
    int *ptr_end;   //Позиция последнего элемента в памяти

    int total; //Общее кол-во элементов в памяти
    int max;   //Максимальное кол-во элементов в памяти
} queue_arr_t;

#endif