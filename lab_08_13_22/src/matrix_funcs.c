#include "../inc/matrix_funcs.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double **allocate_matrix(int n, int m)
{
    double **ptrs, *data;
    ptrs = malloc(n * sizeof(double *));
    if (!ptrs)
        return NULL;
    data = calloc(n * m, sizeof(double));
    if (!data)
    {
        free(ptrs);
        return NULL;
    }
    for (int i = 0; i < n; i++)
        ptrs[i] = data + i * m;
    return ptrs;
}

void free_matrix(double **ptrs)
{
    free(ptrs[0]);

    free(ptrs);
}

void print_matrix(double **arr_ptr, int height, int width)
{
    int count = 0;
    int stop = height * width;

    while (count < stop)
    {
        printf("%f ", arr_ptr[0][count]);
        count++;
        if (count % width == 0)
        {
            printf("\n");
        }
    }
}