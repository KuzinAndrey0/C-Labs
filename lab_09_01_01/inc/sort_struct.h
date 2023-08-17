#ifndef __SORT_STRUCT__

#define __SORT_STRUCT__

#include "my_defines.h"
#include <stddef.h>

void swap_structs(film_t **struct1, film_t **struct2);
void sort_struct_title(film_t **films, size_t total);
void sort_struct_name(film_t **films, size_t total);
void sort_struct_year(film_t **films, size_t total);

#endif