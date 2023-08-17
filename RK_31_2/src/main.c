#include "../inc/file_funcs.h"
#include "../inc/matrix_funcs.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>

int is_poly(int num)
{
    int temp = num;
    int reverse = 0;

    if (num < 0)
        return 0;

    while (temp > 0)
    {
        reverse *= 10;
        reverse += temp % 10;
        temp /= 10;
    }

    temp = num;
    while (temp > 0)
    {
        if ((temp % 10) != (reverse % 10))
        {
            return 0;
        }
        temp /= 10;
        reverse /= 10;
    }
    return 1;
}

int cmpfunc(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main(int argc, char **argv)
{

    FILE *f;
    int height, width;
    int rc;
    int count = 0;

    int **arr, *arr_poly;
    int **arr_pos;

    if (argc != 3)
        return RETURN_WRONG_ARGUMENTS;

    f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Файл отсутствует\n");
        return RETURN_NO_FILE;
    }

    rc = read_matrix(f, &arr, &height, &width);
    fclose(f);

    if (rc != RETURN_SUCCESS)
    {
        printf("Ошибка чтения файла: %d\n", rc);
        return rc;
    }

    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            if (is_poly(arr[i][j]))
            {
                count++;
            }
        }
    }

    if (count == 0)
    {
        printf("Палиндромов нет\n");
        matrix_free(arr);
        return RETURN_EMPTY_FILE_AFTER;
    }

    arr_poly = malloc(count * sizeof(int));
    if (arr_poly == NULL)
    {
        matrix_free(arr);
        printf("Ошибка выделения памяти\n");
        return RETURN_MEMORY_ERROR;
    }

    arr_pos = matrix_create(2, count);
    if (arr_pos == NULL)
    {
        matrix_free(arr);
        free(arr_poly);

        printf("Ошибка выделения памяти\n");
        return RETURN_MEMORY_ERROR;
    }

    count = 0;
    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            if (is_poly(arr[i][j]))
            {
                arr_poly[count] = arr[i][j];
                arr_pos[0][count] = i;
                arr_pos[1][count] = j;
                count++;
            }
        }
    }

    qsort(arr_poly, count, sizeof(int), cmpfunc);
    printf("sort: ");
    for (int i = 0; i < count; i++)
    {
        printf("%d ", arr_poly[i]);
    }
    printf("\n");
    for (int i = 0; i < count; i++)
    {
        int x, y;
        y = arr_pos[0][i];
        x = arr_pos[1][i];

        // printf("X: %d, Y: %d, VAL: %d\n", x, y, arr_poly[i]);
        arr[y][x] = arr_poly[i];
    }

    f = fopen(argv[2], "w");
    if (f == NULL)
    {
        matrix_free(arr);
        matrix_free(arr_pos);
        free(arr_poly);
        printf("Ошибка записи в файл\n");
        return RETURN_NO_FILE;
    }

    /*for (int i = 0; i < width * height; i++)
    {
        fprintf(f, "%d\n", arr[0][i]);
    }*/

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            fprintf(f, "%4d ", arr[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);

    matrix_free(arr);
    matrix_free(arr_pos);
    free(arr_poly);

    return RETURN_SUCCESS;
}