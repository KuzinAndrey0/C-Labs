#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef __FILE_FUNCS__

#define __FILE_FUNCS__

int read_header(FILE *f, int *height, int *width);
int read_matrix(FILE *f, int ***arr_ptr, int *height, int *width);

#endif