#include "find_struct.h"
#include "my_defines.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binary_search_title(film_type films[], char key[], int total)
{
    int low = 0;
    int high = total - 1;
    int diff;

    while (low <= high)
    {
        unsigned int mid = (low + high) >> 1;

        diff = strcmp(films[mid].title, key);
        if (diff < 0)
            low = mid + 1;
        else if (diff > 0)
            high = mid - 1;
        else
            return mid;
    }
    return -1;
}

int binary_search_name(film_type films[], char key[], int total)
{
    int low = 0;
    int high = total - 1;
    int diff;

    while (low <= high)
    {
        unsigned int mid = (low + high) >> 1;

        diff = strcmp(films[mid].name, key);
        if (diff < 0)
            low = mid + 1;
        else if (diff > 0)
            high = mid - 1;
        else
            return mid;
    }
    return -1;
}

int binary_search_year(film_type films[], char key[], int total)
{
    int low = 0;
    int high = total - 1;
    int diff;
    int key_num = atoi(key);

    while (low <= high)
    {
        unsigned int mid = (low + high) >> 1;

        diff = films[mid].year - key_num;
        if (diff < 0)
            low = mid + 1;
        else if (diff > 0)
            high = mid - 1;
        else
            return mid;
    }
    return -1;
}
