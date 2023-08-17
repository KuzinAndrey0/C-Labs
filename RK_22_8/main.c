#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "file_funcs.h"
#include "my_defines.h"

int main(int argc, char** argv)
{

    FILE *f;
    int sum, sign;
    size_t size;
    long pos;

    srand(time(NULL));

    if (argc < 2)
        return RETURN_NO_FILE_NAME;

    //fclose(fopen(argv[1], "a"));
    

    f = fopen(argv[1], "r+b");


    if (f == NULL)
        return RETURN_NO_FILE;   

    fill_with_number(f,10);

    file_size(f, &size);
    if (size <= 0)
        return RETURN_ZERO;


    printf("\nBEFORE: ");
    print_file(f);

    sum = get_sum(f);
    sign = (sum % 2 == 0) ? 1 : -1;
    pos = get_pos(f, sign);

    if(pos >= 0)
    {
        change_val(f, pos, sum);
    }    

    printf("\nAFTER: ");
    print_file(f);

    printf("\nSUM: %d\n", sum);
    printf("SIGN: %d\n", sign);
    printf("POS: %ld \n", pos);


    fclose(f);
    return RETURN_SUCCESS;
}