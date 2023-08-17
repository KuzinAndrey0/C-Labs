#include "../inc/matrix_funcs.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>

int read_header(FILE *f, int *height, int *width)
{
    int rc = fscanf(f, "%d%d", height, width);
    char new_line;
    fread(&new_line, sizeof(char), 1, f);

    if (!feof(f) && new_line == '\r')
        fread(&new_line, sizeof(char), 1, f);

    if (rc != 2 || (new_line != '\n' && !feof(f)))
    {
        return RETURN_WRONG_HEADER;
    }

    return RETURN_SUCCESS;
}

int read_matrix(FILE *f, int ***arr_ptr, int *height, int *width)
{
    int rc, total;

    rc = read_header(f, height, width);

    if (rc != RETURN_SUCCESS)
    {
        return rc;
    }

    *arr_ptr = matrix_create(*height, *width);
    if (*arr_ptr == NULL)
        return RETURN_MEMORY_ERROR;

    total = (*height) * (*width);
    for (int i = 0; i < (total); i++)
    {
        int val;
        rc = fscanf(f, "%d", &val);
        if (rc != 1)
        {
            matrix_free(*arr_ptr);
            return RETURN_WRONG_FORMAT;
        }
        else
            (*arr_ptr)[0][i] = val;
    }

    return RETURN_SUCCESS;
}