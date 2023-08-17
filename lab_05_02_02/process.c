#include <stdio.h>
#include "process.h"
#include "my_defines.h"

int process(FILE *f, double *out_disp)
{
    double num;
    double avg = 0;
    size_t total = 0;
    double mwait = 0;
    double disp;

    while (fscanf(f, "%lf", &num) == 1)
    {
        total++;
        avg += num;
    }

    if (total < 2)
        return RETURN_NOT_ENOUGH;

    rewind(f);
    avg = avg / (total);

    while (fscanf(f, "%lf", &num) == 1)
    {
        mwait = mwait + (num - avg) * (num - avg);
    }

    disp = mwait / total;
    *out_disp = disp;

    return RETURN_SUCCESS; 
}