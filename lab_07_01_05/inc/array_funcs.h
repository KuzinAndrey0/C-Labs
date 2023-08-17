#ifndef __ARRAY_FUNCS__

#define __ARRAY_FUNCS__

#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void *a, const void *b);
void swap_bytes(char *ptr1, char *ptr2, int size);
void print_arr(int *base, size_t nitems);
void mysort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *));
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#endif