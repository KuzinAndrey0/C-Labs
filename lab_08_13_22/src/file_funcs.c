#include "../inc/file_funcs.h"
#include "../inc/matrix_funcs.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_matrix(FILE *f, double **arr, int height, int width)
{
    int zero_count = 0;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (arr[j][i] != 0)
                zero_count++;
        }
    }

    fprintf(f, "%d %d %d\n", height, width, zero_count);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (arr[i][j] != 0)
            {
                fprintf(f, "%d %d %lf\n", i + 1, j + 1, arr[i][j]);
            }
        }
    }
}

int read_header(FILE *f, int *height, int *width, int *count)
{
    int rc = fscanf(f, "%d%d%d", height, width, count);
    char new_line;
    fread(&new_line, sizeof(char), 1, f);
    if (!feof(f) && new_line == '\r')
        fread(&new_line, sizeof(char), 1, f);

    if (rc != 3 || (new_line != '\n' && !feof(f)))
    {
        /*printf("newline code: %d\n", '\n');
        printf("err:\n");
        printf("rc: %d\nnl: '%d'", rc, new_line);*/
        return RETURN_WRONG_HEADER;
    }

    return RETURN_SUCCESS;
}

int read_coords(FILE *f, int *x, int *y, double *value)
{
    int rc = fscanf(f, "%d%d%lf", y, x, value);
    char new_line;
    fread(&new_line, sizeof(char), 1, f);
    if (!feof(f) && new_line == '\r')
        fread(&new_line, sizeof(char), 1, f);

    if (rc != 3 || (!feof(f) && new_line != '\n') || *x <= 0 || *y <= 0 || *value == 0)
    {
        /*printf("getting here\n");
        printf("rc: %d\n", rc);
        printf("x: %d, y: %d\n", *x, *y);
        printf("newline: '%c'", new_line);
*/
        return RETURN_WRONG_COORDS;
    }
    *x = *x - 1;
    *y = *y - 1;

    return RETURN_SUCCESS;
}

int read_matrix(FILE *f, double ***arr_ptr, int *height, int *width)
{
    int rc, count, x, y;
    double val;

    rc = read_header(f, height, width, &count);
    if (rc != RETURN_SUCCESS)
        return rc;
    if (*height <= 0 || *width <= 0 || count > *height * *width)
    {
        return RETURN_HEADER_CALC;
    }
    *arr_ptr = allocate_matrix(*height, *width);
    if (*arr_ptr == NULL)
        return RETURN_MEMORY_ERROR;

    for (size_t i = 0; i < (size_t)count; i++)
    {
        rc = read_coords(f, &x, &y, &val);
        if (rc != RETURN_SUCCESS)
        {
            free_matrix(*arr_ptr);
            return rc;
        }
        if (x >= *width || y >= *height)
        {
            free_matrix(*arr_ptr);
            return RETURN_WRONG_COORDS;
        }

        if ((*arr_ptr)[y][x] != 0)
        {
            free_matrix(*arr_ptr);
            return RETURN_SAME_COORDS;
        }
        // printf("[%d,%d]\n", x, y);
        (*arr_ptr)[y][x] = val;
    }
    return RETURN_SUCCESS;
}