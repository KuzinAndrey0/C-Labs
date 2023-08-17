#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>

int **matrix_create(int height, int width)
{
    int **ptrs, *arr;

    ptrs = malloc(height * sizeof(int *));
    if (ptrs == NULL)
        return NULL;

    arr = calloc(height * width, sizeof(int));
    if (arr == NULL)
    {
        free(ptrs);
        return NULL;
    }

    for (int i = 0; i < height; i++)
        ptrs[i] = arr + i * width;
    return ptrs;
}

void matrix_free(int **ptrs)
{
    free(ptrs[0]);

    free(ptrs);
}