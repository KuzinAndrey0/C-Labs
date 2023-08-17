#include <stdio.h>
#include <stdlib.h>

#ifndef __DYNAMIC_DATA__

// trc-ignore
#define __DYNAMIC_DATA__

// trc-ignore
#define TYPE_ARRAY 0
// trc-ignore
#define TYPE_MATRIX 1
// trc-ignore
#define TYPE_LIST 2
// trc-ignore
#define TYPE_FILE 3

// trc-ignore
#define DYN_START_MEM 100
// trc-ignore
#define DYN_STEP_MEM 100

// trc-ignore
struct allocated_data_s
{
    void **ptr;
    int *type;
    int total;

    int create_mem;
    int step_mem;
    int current_mem;
};

extern struct allocated_data_s global_data;

// Информационная часть списка
typedef struct list_node list_node;
// Информационная часть списка
struct list_node
{
    double data;     //Значение узла
    list_node *next; //Следующий элемент
};

// Односвязный список, использующйся для реализации очереди
typedef struct list_t
{
    list_node *head; //Указатель на голову списка

    int total; //Общее кол-во элементов

    list_node *tail; //Указатель на хвост списка
} list_t;

// trc-ignore
void free_matrix(int **ptrs);
// trc-ignore
void free_memory(int index);
// trc-ignore
void free_list(list_t *list);
// trc-ignore
int add_global_data(void *ptr, int type);

// trc-ignore
int init_global_data(void); //Использовать после запуска

// trc-ignore
void *my_malloc(size_t size); //Одномерный массив
// trc-ignore
int init_list(list_t *ptr); //Лист

// trc-ignore
void free_memory_index(int index); //Освобождает по индексу в списке динамических данных
// trc-ignore
void free_memory_value(void *ptr); //Освобождает по указателю из списка
// trc-ignore
void free_memory_all(void); //Освобождает ВСЮ динамическую память

// trc-ignore
int list_add_last(list_t *list, double value); //Работа со списками
// trc-ignore
void list_remove_index(list_t *list, int index);
// trc-ignore
void list_remove_last(list_t *list);
// trc-ignore
void list_get_info(list_t *list, int index, double *val, void **adress);

// trc-ignore
void terminate_program(int rc); //Выход из программы, включая освобождение памяти

#endif