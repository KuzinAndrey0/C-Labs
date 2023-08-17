#include "../inc/array_funcs.h"
#include "../inc/file_funcs.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (pb_src >= pe_src)
        return 1;

    int sum = 0;
    int val = 0;
    int count = 0;

    for (const int *i = pb_src; i < pe_src; i++)
    {
        sum += *i;
    }

    int old_sum = sum;

    for (const int *i = pb_src; i < (pe_src - 1); i++)
    {
        val = *i;
        sum -= val;
        if (val > sum)
        {
            //*(*pb_dst + count) = val;
            count++;
        }
    }
    // printf("CUNT: %d\n", count);

    if (count == 0)
        return 3;

    *pb_dst = malloc(count * sizeof(int));

    // printf("GETTING HERE\n");
    if (*pb_dst == NULL)
        return 4;

    sum = old_sum;
    count = 0;

    for (const int *i = pb_src; i < (pe_src - 1); i++)
    {
        val = *i;
        // printf("VAL: %d\n", val);
        sum -= val;
        if (val > sum)
        {
            // printf("^ ADDING (count: %d) p: %p\n", count, (void *)(*pb_dst + count));
            *(*pb_dst + count) = val;
            count++;
        }
    }
    // for (int i = 0; i < count; i++)
    // {
    //     printf("%d ", *(*pb_dst + i));
    // }
    *pe_dst = *pb_dst + count;
    // printf("COUNT: %d\n", count);

    return 0;
}