#define _GNU_SOURCE
#include "../inc/dynamic_data.h"
#include "../inc/list_strings.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct allocated_data_s global_data;

int main(void)
{
    int rc = init_global_data();
    if (!rc)
        terminate_program(rc);

    list_t string_list, string_list2;

    rc = init_list(&string_list);
    if (rc != RETURN_SUCCESS)
        terminate_program(rc);

    rc = init_list(&string_list2);
    if (rc != RETURN_SUCCESS)
        terminate_program(rc);

    char *input = NULL;

    rc = read_line(stdin, &input);

    if (rc != RETURN_SUCCESS)
    {
        terminate_program(rc);
    }

    if (strcmp(input, "out") == 0)
    {
        rc = read_line(stdin, &input);
        if (rc != RETURN_SUCCESS)
            terminate_program(rc);

        rc = convert_to_list(input, &string_list);
        if (rc != RETURN_SUCCESS)
            terminate_program(rc);

        print_list_string(string_list);
        printf("\n");
    }
    else if (strcmp(input, "sps") == 0)
    {
        rc = read_line(stdin, &input);
        if (rc != RETURN_SUCCESS)
            terminate_program(rc);

        rc = convert_to_list(input, &string_list);
        if (rc != RETURN_SUCCESS)
            terminate_program(rc);

        remove_spaces(&string_list);
        print_list_string(string_list);
        printf("\n");
    }
    else if (strcmp(input, "cat") == 0)
    {
        rc = read_line(stdin, &input);
        if (rc != RETURN_SUCCESS)
            terminate_program(rc);

        rc = convert_to_list(input, &string_list);
        if (rc != RETURN_SUCCESS)
            terminate_program(rc);

        rc = read_line(stdin, &input);
        if (rc != RETURN_SUCCESS)
            terminate_program(rc);

        rc = convert_to_list(input, &string_list2);
        if (rc != RETURN_SUCCESS)
            terminate_program(rc);

        concatenate_strings(&string_list, &string_list2);

        print_list_string(string_list);
        printf("\n");
    }
    else if (strcmp(input, "pos") == 0)
    {
        rc = read_line(stdin, &input);
        if (rc != RETURN_SUCCESS)
            terminate_program(rc);

        rc = convert_to_list(input, &string_list);
        if (rc != RETURN_SUCCESS)
            terminate_program(rc);

        rc = read_line(stdin, &input);
        if (rc != RETURN_SUCCESS)
            terminate_program(rc);

        rc = convert_to_list(input, &string_list2);
        if (rc != RETURN_SUCCESS)
            terminate_program(rc);

        int pos = find_substring(string_list, string_list2);
        // if (pos != -1)
        //{
        printf("%d\n", pos);
        //}
        // else
        // {
        //     terminate_program(RETURN_NO_SUBSTR);
        // }
    }
    else
    {
        terminate_program(RETURN_WRONG_FORMAT);
    }

    terminate_program(RETURN_SUCCESS);
}