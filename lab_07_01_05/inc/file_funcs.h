

#ifndef __FILE_FUNCS__

#define __FILE_FUNCS__

#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>

void get_num(FILE *file, int *arr, size_t count);
int get_num_count(FILE *file, size_t *count);

#endif