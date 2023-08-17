#include "../inc/dynamic_data.h"

#ifndef __STACK_HANDLE__

// trc-ignore
#define __STACK_HANDLE__

/*
Добавляет элемент в стек, представленный в виде списка
*/
int stack_list_push(list_t *list, int value);

/*
Удаляет и возвращает значение последнего элемента в стеке, представленного в виде списка
*/
int stack_list_pop(list_t *list);

/*
Добавляет элемент в стек, представленный в виде массива
*/
void stack_array_push(int *arr, int value, int *pos);

/*
Удаляет и возвращает значение последнего элемента в стеке, представленного в виде массива
*/
int stack_array_pop(int *arr, int *pos);

#endif