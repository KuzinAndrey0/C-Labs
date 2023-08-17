#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "file_funcs.h"
#include "my_defines.h"

void change_val(FILE *f, long pos, int val)
{
    fseek(f, pos, SEEK_SET);
    fwrite(&val, sizeof(int), 1, f);
}

size_t file_size(FILE *f, size_t *size)
{
    long new_size;

    if (fseek(f, 0L, SEEK_END))
        return 1;

    new_size = ftell(f);
    if (new_size < 0)
        return 1;

    *size = new_size;

    return fseek(f, 0L, SEEK_SET);
}


long get_pos(FILE *f, int sign)
{
    int num, not_correct, read;

    if (sign == 0)
        return RETURN_ZERO;

    fseek(f, 0L, SEEK_SET);
    size_t size;
    not_correct = file_size(f, &size);

    if (not_correct)
        return RETURN_NO_FILE;

    for (size_t i = 0; !not_correct && i < size / sizeof(int); i ++)
    {
        read = fread(&num, sizeof(int), 1, f);
        if (read == 1)
        {      
            if (num * sign > 0)
            {
                return ftell(f) - sizeof(int);
            }   
        }
        else
        {
            not_correct = 1;

        }
    }  

    return RETURN_ZERO;


    

}

int fill_with_number(FILE *f, size_t count)
{

    int num;
    //int numarr[] = {-5, -5, 5, 6, 100, -6};
    int numarr[] = {0, 0, 0, -2, 0, 0};
    int len = 6;
    count = len;


    for (size_t i = 0; i < count; i ++)
    {
        num = numarr[i];//(int) i;

        if (i % 2 == 0)
            num *= -1;
        fwrite(&num, sizeof(int), 1, f);
    }
    return 0;
}

int get_sum(FILE *f)
{
    int num, not_correct, read;
    int sum = 0;

    size_t size;
    not_correct = file_size(f, &size);

    for (size_t i = 0; !not_correct && i < size / sizeof(int); i ++)
    {
        read = fread(&num, sizeof(int), 1, f);
        if (read == 1)
        {         
            sum += num;
        }
        else
        {
            not_correct = 1;
        }
    }  
    
    return sum;
}

int print_file(FILE *f)
{
    int num, correct, read;

    size_t size;
    correct = file_size(f, &size);

    if (correct == 1)
        return RETURN_NO_FILE;

    correct = 1;

    for (size_t i = 0; correct && i < size / sizeof(int); i ++)
    {
        read = fread(&num, sizeof(int), 1, f);

        if (read == 1)
            printf("%d ", num);
        else
            correct = 0;
    }

    printf("\n");
    return RETURN_SUCCESS;
}