#include <stdlib.h>

#ifndef __DYNAMIC_DATA__

// trc-ignore
#define __DYNAMIC_DATA__

/*
Информационная часть списка
*/
typedef struct list_node list_node;
/*
Информационная часть списка
*/
struct list_node
{
    int value;       // Значение узла
    list_node *next; // Указатель на следующий узел
};

/*
Метаданные списка
*/
typedef struct list_t
{
    list_node *head; // Голова списка

    int total; // Кол-во элементов в списке
} list_t;

// SYSTEM FUNCS
// trc-ignore
void free_matrix(int **ptrs);
// trc-ignore
void free_memory(int index);
// trc-ignore
void free_list(list_t *list);
// trc-ignore
int add_global_data(void *ptr, int type);

// USAGE FUNCS
// trc-ignore
int init_global_data(void); //Использовать после запуска

// trc-ignore
void *my_malloc(size_t size); //Одномерный массив
// trc-ignore
int **allocate_matrix(int n, int m); //Матрица, объедененный подход 2
// trc-ignore
int init_list(list_t *ptr); //Лист

// trc-ignore
void free_memory_index(int index); //Освобождает по индексу в списке динамических данных
// trc-ignore
void free_memory_value(void *ptr); //Освобождает по указателю из списка
// trc-ignore
void free_memory_all(void); //Освобождает ВСЮ динамическую память

// trc-ignore
int list_add_last(list_t *list, int value); //Работа со списками
// trc-ignore
void list_remove_index(list_t *list, int index);
// trc-ignore
void list_remove_last(list_t *list);
// trc-ignore
void list_get_info(list_t *list, int index, int *val, void **adress);

// trc-ignore
void terminate_program(int rc); //Выход из программы, включая освобождение памяти

#endif