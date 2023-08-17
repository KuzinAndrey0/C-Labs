#include "sort_struct.h"
#include "my_defines.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap_structs(film_type *struct1, film_type *struct2)
{
    film_type struct3;

    struct3 = *(struct2);
    *(struct2) = *(struct1);
    *(struct1) = struct3;
}

void sort_struct_title(film_type films[], size_t total)
{
    int diff;
    for (size_t i = 0; i < (total - 1); i++)
    {
        for (size_t j = 0; j < (total - i - 1); j++)
        {
            diff = strcmp(films[j + 1].title, films[j].title);
            if (diff < 0)
            {
                swap_structs(&films[j + 1], &films[j]);
            }
        }
    }
}

void sort_struct_name(film_type films[], size_t total)
{
    int diff;
    for (size_t i = 0; i < (total - 1); i++)
    {
        for (size_t j = 0; j < (total - i - 1); j++)
        {
            diff = strcmp(films[j + 1].name, films[j].name);
            if (diff < 0)
            {
                swap_structs(&films[j + 1], &films[j]);
            }
        }
    }
}

void sort_struct_year(film_type films[], size_t total)
{
    for (size_t i = 0; i < (total - 1); i++)
    {
        for (size_t j = 0; j < (total - i - 1); j++)
        {
            if (films[j + 1].year < films[j].year)
            {
                swap_structs(&films[j + 1], &films[j]);
            }
        }
    }
}