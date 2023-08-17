#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "my_defines.h"
#include "file_funcs.h"

int get_number_by_pos(FILE *f, size_t pos)
{
    int num;

    fseek(f, pos * sizeof(int), SEEK_SET);

    fread(&num, sizeof(int), 1, f);

    return num;
}

void put_number_by_pos(FILE *f, size_t pos, int num)
{
    fseek(f, pos * sizeof(int), SEEK_SET);
    fwrite(&num, sizeof(int), 1, f);
}

size_t file_size(FILE *f, size_t *size)
{
    long new_size;

    if (fseek(f, 0L, SEEK_END))
        return 1;

    new_size = ftell(f);
    if (new_size < 4 || (new_size % sizeof(int) != 0))
        return 1;

    *size = new_size;

    return fseek(f, 0L, SEEK_SET);
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

    return RETURN_SUCCESS;
}
    

int fill_with_number(FILE *f, size_t count)
{
    int num;
    for (size_t i = 0; i < count; i ++)
    {
        num = rand();
        fwrite(&num, sizeof(int), 1, f);
    }
    return 0;
}


int sort_file(FILE *f)
{
    int correct;
    size_t size;
    correct = file_size(f, &size);

    if (correct == 1)
        return RETURN_NO_FILE;

    size = size / sizeof(int);

    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t j = (size - 1); j > i; j--)
        {
            if (get_number_by_pos(f, j - 1) > get_number_by_pos(f, j))
            {
                int temp = get_number_by_pos(f, j - 1);
                put_number_by_pos(f, j - 1, get_number_by_pos(f, j));
                put_number_by_pos(f, j, temp);
            }
        }
    }

    return 0;
}
