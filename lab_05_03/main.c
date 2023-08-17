#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#include "my_defines.h"
#include "file_funcs.h"



/*
Тип int
Сортировка bubble sort
Направление прямое
*/


int is_number(char num[])
{
    size_t len = strlen(num);
    for (size_t i = 0; i < len; i ++)
    {
        if (isdigit(num[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}


int main(int argc, char **argv)
{
    FILE *f;
    int str_check, count, done, debug;
    (void) debug;

    srand(time(NULL));

    if (argc < 3)
        return RETURN_NOT_ENOUGH_KEYS;

    str_check = strcmp(argv[1], "c");

    if (str_check == 0)
    {
        if (argc != 4)
            return RETURN_NOT_ENOUGH_KEYS;

        f = fopen(argv[3], "wb");
        if (f == NULL)
            return RETURN_NO_FILE;              

        if (!is_number(argv[2]))
        {
            return RETURN_INCORRECT_KEYS;
        }

        count = atoi(argv[2]);

        fill_with_number(f, count);
        fclose(f);

        return RETURN_SUCCESS;
    }
    
    str_check = strcmp(argv[1], "p");
    if (str_check == 0)
    {
        f = fopen(argv[2], "rb");
        if (f == NULL)
            return RETURN_NO_FILE;    
   
        done = print_file(f);

        fclose(f);

        if (done != 0)
            return RETURN_NO_FILE;
        return RETURN_SUCCESS;
    }

    str_check = strcmp(argv[1], "s");
    if (str_check == 0)
    {
        f = fopen(argv[2], "r+b");
        if (f == NULL)
            return RETURN_NO_FILE;    
   
        done = sort_file(f);

        if (done != 0)
            return RETURN_NO_FILE;

        fclose(f);

        return RETURN_SUCCESS;
    }

    return RETURN_INCORRECT_KEYS;
}