#include <stdio.h>
#include "process.h"
#include "my_defines.h"


int main(int argc, char **argv)
{
    FILE *f;
    int success;
    double num;

    if (argc < 2)
        return RETURN_NO_FILE_NAME;    

    f = fopen(argv[1], "r");

    if (f == NULL)
        return RETURN_NO_FILE;

    success = process(f, &num);

    if (success == RETURN_SUCCESS)
        printf("%lf\n", num);
    return success;
}