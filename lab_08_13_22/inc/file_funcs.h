#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __FILE_FUNCS__

#define __FILE_FUNCS__

int read_matrix(FILE *f, double ***arr_ptr, int *height, int *width);
int read_coords(FILE *f, int *x, int *y, double *value);
int read_header(FILE *f, int *height, int *width, int *count);
void write_matrix(FILE *f, double **arr, int height, int width);

#endif