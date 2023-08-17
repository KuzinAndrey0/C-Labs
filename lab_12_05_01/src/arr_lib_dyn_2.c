#include "../inc/arr_lib_dyn_2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_to_file(FILE *f, int *arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        fprintf(f, "%d ", *(arr + i));
    }
}

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void swap_bytes(char *ptr1, char *ptr2, int size)
{
    for (int i = 0; i < size; i++)
    {
        char chr = *ptr2;
        *(ptr2) = *(ptr1);
        *(ptr1) = chr;

        ptr1++;
        ptr2++;
    }
}

void print_arr(int *base, size_t nitems)
{
    for (size_t i = 0; i < nitems; i++)
    {
        printf("%d ", *(base + i));
    }
    printf("\n");
}

void mysort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))
{

    if (nitems == 0 || size == 0)
    {
        return;
    }

    char *base_ptr = (char *)base;
    long new_border = 1;

    size_t left_border = 0;
    size_t right_border = nitems - 1;

    size_t start = left_border;
    size_t end = right_border;
    int step = 1;

    while (new_border != -1)
    {
        new_border = -1;
        for (size_t i = start; i != end; i = i + step)
        {
            char *a = base_ptr + i * size;
            char *b = base_ptr + (i + 1) * size;
            if (compar(a, b) > 0)
            {
                // swap_bytes(a, b, size);
                for (size_t j = 0; j < size; j++)
                {
                    char chr = *b;
                    *(b) = *(a);
                    *(a) = chr;

                    a++;
                    b++;
                }
                new_border = i;
            }
        }

        if (step == 1)
        {
            if (new_border != -1)
                right_border = new_border;
            start = right_border - 1;
            end = left_border - 1;
            step = -1;
        }
        else
        {
            if (new_border != -1)
                left_border = new_border;
            start = left_border;
            end = right_border;
            step = 1;
        }
    }
}