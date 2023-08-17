#include "../inc/array_funcs.h"
#include "../inc/file_funcs.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        return RETURN_NOT_ENOUGH_ARGUMENTS;
    }

    FILE *f_in, *f_out;
    size_t count = 0;
    int correct;
    int *arr, *arr2;
    int filter_enabled = argc == 4 && strcmp(argv[3], "f") == 0;

    if (!filter_enabled && argc >= 4)
        return RETURN_WRONG_ARGUMENTS;
    if (argc > 4)
        return RETURN_WRONG_ARGUMENTS;

    f_in = fopen(argv[1], "r");
    if (f_in == NULL)
    {
        return RETURN_NO_FILE;
    }

    correct = get_num_count(f_in, &count);
    // printf("count: %lu\n", count);
    if (correct == RETURN_WRONG_FORMAT)
    {
        return RETURN_WRONG_FORMAT;
    }
    if (count == 0)
    {
        return RETURN_EMPTY_FILE;
    }

    arr = (int *)malloc(count * sizeof(int));

    if (arr == NULL)
    {
        return RETURN_MEMORY_ERROR;
    }

    get_num(f_in, arr, count);

    fclose(f_in);

    if (filter_enabled)
    {
        int *arr1_end = arr + count;
        int *arr2_end;

        correct = key(arr, arr1_end, &arr2, &arr2_end);

        if (correct != 0)
        {
            free(arr);
            return RETURN_MEMORY_ERROR;
        }

        count = arr2_end - arr2;

        mysort(arr2, count, sizeof(int), cmpfunc);

        f_out = fopen(argv[2], "w");
        if (f_out == NULL)
        {
            free(arr);
            free(arr2);
            return RETURN_NO_FILE;
        }
        for (size_t i = 0; i < count; i++)
        {
            fprintf(f_out, "%d ", *(arr2 + i));
        }

        free(arr2);
    }
    else
    {
        mysort(arr, count, sizeof(int), cmpfunc);

        f_out = fopen(argv[2], "w");
        if (f_out == NULL)
        {
            free(arr2);
            return RETURN_NO_FILE;
        }
        for (size_t i = 0; i < count; i++)
        {
            fprintf(f_out, "%d ", *(arr + i));
        }
    }
    fclose(f_out);
    free(arr);
    return RETURN_SUCCESS;
}