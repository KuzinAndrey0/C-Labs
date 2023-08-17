#include <stdlib.h>

#ifndef __MY_SPRINTF__

#define __MY_SPRINTF__

char *int_to_str(int num);
char *long_to_str(long num);
int my_snprintf(char *s, size_t n, const char *format, ...);

#endif