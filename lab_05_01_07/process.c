#include <stdio.h>
#include "process.h"
#include "my_defines.h"

int process(FILE *f_in, long long int *output)
{
    //printf("Введите числа: ");
    long long int valid, n, prev_n, prev_prev_n;
    long long int count = 0;
    long long int num = 0;
    valid = fscanf(f_in, "%lld", &n);

    while (valid == 1)
    {
        if (num >= 2 && prev_n > n && prev_n > prev_prev_n)
        {
            count ++;
        }
        
        if (num >= 1)
            prev_prev_n = prev_n;
        prev_n = n;
        valid = fscanf(f_in, "%lld", &n);
        num ++;
    }

    *output = count;

    if (num < 3)
        return RETURN_NOT_ENOUGH;
    return RETURN_SUCCESS;
}