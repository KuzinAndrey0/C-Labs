#include "../inc/arr_lib_stat.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Статическая библиотека

int get_num_count(FILE *file, size_t *count, int **arr)
{
    int correct;
    int num;
    fseek(file, SEEK_SET, 0);
    while (!feof(file))
    {
        correct = fscanf(file, "%d", &num);
        if (correct == 1)
        {
            *count += correct;
            if (feof(file))
                return RETURN_SUCCESS;
        }

        if (correct != 1 && !feof(file))
        {
            return RETURN_WRONG_FORMAT;
        }
    }

    if (count == 0)
        return RETURN_EMPTY_FILE;

    *arr = (int *)malloc((*count) * sizeof(int));

    if (arr == NULL)
    {
        return RETURN_MEMORY_ERROR;
    }

    fseek(file, SEEK_SET, 0);
    for (size_t i = 0; i < *count; i++)
    {
        fscanf(file, "%d", ((*arr) + i));
    }

    return RETURN_SUCCESS;
}