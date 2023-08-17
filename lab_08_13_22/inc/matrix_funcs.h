#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __MATRIX_FUNCS__

#define __MATRIX_FUNCS__

void print_matrix(double **arr_ptr, int height, int width);
void free_matrix(double **ptrs);
double **allocate_matrix(int n, int m);

#endif