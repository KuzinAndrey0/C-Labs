#include "../inc/arr_lib_dyn_1.h"
#include <stdio.h>

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
            count++;
        }
    }

    if ((pb_dst) == NULL || (pe_dst) == NULL)
        return count;

    if (count == 0)
        return 3;

    sum = old_sum;
    count = 0;

    for (const int *i = pb_src; i < (pe_src - 1); i++)
    {
        val = *i;
        sum -= val;
        if (val > sum)
        {
            *(*pb_dst + count) = val;
            count++;
        }
    }
    *pe_dst = *pb_dst + count;

    return 0;
}