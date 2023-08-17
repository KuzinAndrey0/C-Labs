#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __LIST_STRINGS__

#define __LIST_STRINGS__

int read_line(FILE *f, char **str);
void print_list_string(list_t list_info);
void print_list_debug(list_t list_info);
void compact(list_t *list_info);
void remove_spaces(list_t *list_info);
int convert_to_list(char *input, list_t *list_info);
void concatenate_strings(list_t *list1, list_t *list_2);
int find_substring(list_t string_list, list_t substring_list);

#endif