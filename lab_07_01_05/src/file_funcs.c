#include "../inc/file_funcs.h"
#include "../inc/array_funcs.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_num(FILE *file, int *arr, size_t count)
{
    fseek(file, SEEK_SET, 0);
    for (size_t i = 0; i < count; i++)
    {
        fscanf(file, "%d", (arr + i));
        // printf("Writing num: %d\n", *(arr + i));
    }
}

int get_num_count(FILE *file, size_t *count)
{
    int correct;
    int num;
    fseek(file, SEEK_SET, 0);
    while (!feof(file))
    {
        correct = fscanf(file, "%d", &num);
        // printf("Found num: %d\n", num);
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

    return RETURN_SUCCESS;
}