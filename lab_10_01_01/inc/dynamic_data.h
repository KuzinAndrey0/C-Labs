#include <stdio.h>
#include <stdlib.h>

#ifndef __DYNAMIC_DATA__

#define __DYNAMIC_DATA__

#define TYPE_ARRAY 0
#define TYPE_MATRIX 1
#define TYPE_LIST 2
#define TYPE_FILE 3

#define DYN_START_MEM 100
#define DYN_STEP_MEM 100

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

typedef struct list_node list_node;

struct list_node
{
    void *data;
    list_node *next;
};

typedef struct list_t
{
    list_node *head;

    int total;
} list_t;

// SYSTEM FUNCS
void free_matrix(int **ptrs);
void free_memory(int index);
void free_list(list_t *list);
int add_global_data(void *ptr, int type);

// USAGE FUNCS
int init_global_data(void); //Использовать после запуска

void *my_malloc(size_t size);                            //Одномерный массив
int **allocate_matrix(int n, int m);                     //Матрица, объедененный подход 2
int init_list(list_t *ptr);                              //Лист
FILE *my_fopen(const char *filename, const char *modes); //Файл

void free_memory_index(int index); //Освобождает по индексу в списке динамических данных
void free_memory_value(void *ptr); //Освобождает по указателю из списка
void free_memory_all(void);        //Освобождает ВСЮ динамическую память

int list_add_last(list_t *list, void *value); //Работа со списками
void list_remove_index(list_t *list, int index);
void list_remove_last(list_t *list);
void list_get_info(list_t *list, int index, void **val, void **adress);

void terminate_program(int rc); //Выход из программы, включая освобождение памяти

#endif