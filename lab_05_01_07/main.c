#include <stdio.h>

#include "my_defines.h"
#include "process.h"

int main(void)
{
    FILE *f_in = stdin;

    int success;
    long long int num;

    success = process(f_in, &num);

    if (success == 0)
        printf("%lld\n", num);
    return success;
}