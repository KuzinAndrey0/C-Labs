#include "../inc/file_funcs.h"
#include "../inc/matrix_funcs.h"
#include "../inc/matrix_math.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 4)
        return RETURN_NOT_ENOUGH_ARGUMENTS;

    int need_argc = strcmp(argv[1], "o") == 0 ? 4 : 5;
    if (argc != need_argc)
        return RETURN_WRONG_ARGUMENTS;

    int height[3];
    int width[3];
    int rc;
    int main_pointer = 0;
    int done = 1;
    (void)main_pointer;

    double **arr1, **arr2, **arr3;

    char *filename_out = strcmp(argv[1], "o") == 0 ? argv[3] : argv[4];

    FILE *f;

    f = fopen(argv[2], "r");
    if (f == NULL)
        return RETURN_NO_FILE;
    rc = read_matrix(f, &arr1, &(height[0]), &(width[0]));
    fclose(f);

    if (rc != RETURN_SUCCESS)
        return rc;

    if ((strcmp(argv[1], "o") != 0))
    {
        f = fopen(argv[3], "r");
        if (f == NULL)
        {
            free_matrix(arr1);
            return RETURN_NO_FILE;
        }
        rc = read_matrix(f, &arr2, &(height[1]), &(width[1]));
        fclose(f);
        if (rc != RETURN_SUCCESS)
        {
            free_matrix(arr1);
            return rc;
        }
    }

    if (strcmp(argv[1], "a") == 0)
    {
        if (height[0] != height[1] || width[0] != width[1])
        {
            free_matrix(arr1);
            free_matrix(arr2);
            return RETURN_NO_ADDITION_SETUP;
        }

        height[2] = height[0];
        width[2] = width[0];

        arr3 = allocate_matrix(height[2], width[2]);
        if (arr3 == NULL)
        {
            free_matrix(arr1);
            free_matrix(arr2);
            return RETURN_MEMORY_ERROR;
        }

        matrix_addition(arr1, arr2, &arr3, height[0], width[0]);
        done = 0;
    }

    if (strcmp(argv[1], "m") == 0)
    {
        if (height[1] != width[0])
        {
            free_matrix(arr1);
            free_matrix(arr2);
            return RETURN_NO_MULTIPLY_SETUP;
        }

        height[2] = height[0];
        width[2] = width[1];

        arr3 = allocate_matrix(height[2], width[2]);
        if (arr3 == NULL)
        {
            free_matrix(arr1);
            free_matrix(arr2);
            return RETURN_MEMORY_ERROR;
        }

        matrix_multiplication(arr1, arr2, &arr3, height, width);
        done = 0;
    }

    if (strcmp(argv[1], "o") == 0)
    {
        double det = 0;

        if (height[0] != width[0])
        {
            free_matrix(arr1);
            return RETURN_NO_DET_SETUP;
        }
        rc = calc_determinant(arr1, height[0], &det);
        free_matrix(arr1);

        if (rc != RETURN_SUCCESS)
        {
            return RETURN_WRONG_FORMAT;
        }

        f = fopen(filename_out, "w");
        if (f == NULL)
        {
            return RETURN_NO_FILE;
        }

        fprintf(f, "%lf", det);
        fclose(f);

        done = 0;
    }
    else if (done == 0)
    {
        free_matrix(arr1);
        free_matrix(arr2);

        f = fopen(filename_out, "w");
        if (f == NULL)
        {
            free_matrix(arr3);
            return RETURN_NO_FILE;
        }
        write_matrix(f, arr3, height[2], width[2]);
        fclose(f);

        free_matrix(arr3);
    }
    return done;
}