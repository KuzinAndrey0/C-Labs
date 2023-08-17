#ifndef __SORT_STRUCT__

#define __SORT_STRUCT__

#include "my_defines.h"
#include <stddef.h>

void swap_structs(film_type *struct1, film_type *struct2);
void sort_struct_title(film_type films[], size_t total);
void sort_struct_name(film_type films[], size_t total);
void sort_struct_year(film_type films[], size_t total);

#endif