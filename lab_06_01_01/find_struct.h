#ifndef __FIND_STRUCT__

#define __FIND_STRUCT__

#include "my_defines.h"
#include <stddef.h>

int binary_search_title(film_type films[], char key[], int total);
int binary_search_name(film_type films[], char key[], int total);
int binary_search_year(film_type films[], char key[], int total);

#endif