#define _GNU_SOURCE
#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"
#include "../inc/my_sprintf.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct allocated_data_s global_data;

int main(void)
{
    init_global_data();
    char *test = my_malloc(sizeof(char) * 100);

    // int t = 10;
    // snprintf(test, t, "Testing something...");

    // printf("%s\n", test);

    int num = my_snprintf(test, 10, "test");
    printf("'%s'\nnum: %d\n", test, num);
    num = snprintf(test, 10, "test");
    printf("'%s'\nnum: %d\n", test, num);
    terminate_program(RETURN_SUCCESS);
}
