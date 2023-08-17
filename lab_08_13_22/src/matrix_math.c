#include "../inc/matrix_math.h"
#include "../inc/matrix_funcs.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void matrix_addition(double **arr1, double **arr2, double ***arr3, int height, int width)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            (*arr3)[j][i] = arr1[j][i] + arr2[j][i];
        }
    }
}

void matrix_multiplication(double **arr1, double **arr2, double ***arr3, int height[], int width[])
{
    for (int j = 0; j < height[0]; j++)
    {
        for (int i = 0; i < width[1]; i++)
        {
            double sum = 0;

            for (int k = 0; k < height[1]; k++)
            {
                sum += arr2[k][i] * arr1[j][k];
            }

            (*arr3)[j][i] = sum;
        }
    }
}

int calc_determinant(double **arr, size_t size, double *det)
{
    if (size == 2)
    {
        *det = arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];
    }
    else if (size == 1)
    {
        *det = arr[0][0];
    }
    else
    {
        int sum = 0;

        for (size_t i = 0; i < size; i++)
        {
            double **minor = allocate_matrix(size - 1, size - 1);
            int index = 0;
            if (minor == NULL)
            {
                return RETURN_MEMORY_ERROR;
            }
            for (size_t k = 0; k < i; k++)
                for (size_t j = 1; j < size; j++)
                {
                    minor[0][index] = arr[k][j];
                    index++;
                }
            for (size_t k = i + 1; k < size; k++)
                for (size_t j = 1; j < size; j++)
                {
                    minor[0][index] = arr[k][j];
                    index++;
                }
            int sign = i % 2 == 0 ? 1 : -1;

            double my_det;
            int rc = calc_determinant(minor, size - 1, &my_det);
            free_matrix(minor);
            if (rc != RETURN_SUCCESS)
            {
                return rc;
            }
            sum += (double)arr[i][0] * sign * my_det;
        }
        *det = sum;
    }

    return RETURN_SUCCESS;
}