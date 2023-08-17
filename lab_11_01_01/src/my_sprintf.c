#include "../inc/my_defines.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *int_to_str(int num)
{
    size_t len = 0;
    int num_copy = num;
    int num_rev = 0;
    if (num == 0)
        len = 1;
    if (num < 0)
        len++;
    while (num_copy != 0)
    {
        len++;
        num_rev *= 10;
        num_rev += num_copy % 10;
        num_copy /= 10;
    }
    if (num_rev < 0)
        num_rev *= -1;

    char *output = malloc(sizeof(char) * len + 1);
    size_t pos = 0;
    if (num < 0)
    {
        len--;
        output[pos] = '-';
        pos++;
    }
    for (size_t i = 0; i < len; i++)
    {
        output[pos] = '0' + num_rev % 10;
        num_rev /= 10;
        pos++;
    }
    output[pos] = '\0';

    return output;
}

char *long_to_str(long num)
{
    size_t len = 0;
    long num_copy = num;
    long num_rev = 0;
    if (num == 0)
        len = 1;
    if (num < 0)
        len++;
    while (num_copy != 0)
    {
        len++;
        num_rev *= 10;
        num_rev += num_copy % 10;
        num_copy /= 10;
    }
    if (num_rev < 0)
        num_rev *= -1;

    char *output = malloc(sizeof(char) * len + 1);
    size_t pos = 0;
    if (num < 0)
    {
        len--;
        output[pos] = '-';
        pos++;
    }
    for (size_t i = 0; i < len; i++)
    {
        output[pos] = '0' + num_rev % 10;
        num_rev /= 10;
        pos++;
    }
    output[pos] = '\0';

    return output;
}

int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...)
{
    va_list args;
    va_start(args, format);
    size_t i = 0;
    size_t pos = 0;
    size_t count = 0;
    if (n == 0)
        n = 1;
    while (format[i] != '\0')
    {
        if (format[i] != '%')
        {
            // printf("pos: %lu, n - 1: %lu\n", pos, n - 1);
            if (pos < (n - 1) && s != NULL)
            {
                s[pos] = format[i];
                pos++;
            }
            count++;
        }
        else
        {
            if (format[i + 1] == 's')
            {
                char *substr = va_arg(args, char *);
                size_t len = strlen(substr);
                int copy_count = (n - pos - 1) < len ? n - pos - 1 : len;
                for (int j = 0; j < copy_count && s != NULL; j++)
                {
                    s[pos] = substr[j];
                    pos++;
                }
                count += len;
                i++;
            }
            // else if (format[i + 1] == 'i')
            // {
            //     int subnum = va_arg(args, int);
            //     char *substr = int_to_str(subnum);
            //     size_t len = strlen(substr);
            //     int copy_count = (n - pos - 1) < len ? n - pos - 1 : len;
            //     for (int j = 0; j < copy_count && s != NULL; j++)
            //     {
            //         s[pos] = substr[j];
            //         pos++;
            //     }
            //     count += len;
            //     i++;
            //     free(substr);
            // }
            else if (format[i + 1] == 'l' && format[i + 2] == 'i')
            {
                long subnum = va_arg(args, long);
                char *substr = long_to_str(subnum);
                size_t len = strlen(substr);
                int copy_count = (n - pos - 1) < len ? n - pos - 1 : len;
                for (int j = 0; j < copy_count && s != NULL; j++)
                {
                    s[pos] = substr[j];
                    pos += 1;
                }
                count += len;
                i += 2;
                free(substr);
            }
            // else if (format[i + 1] == '%')
            // {
            //     if (pos < (n - 1) && s != NULL)
            //     {
            //         s[pos] = '%';
            //         pos++;
            //     }
            //     i++;
            //     count++;
            //}
        }
        i++;
    }
    if (s != NULL)
    {
        // printf("POS: %lu\n", pos);
        s[pos] = '\0';
    }
    va_end(args);
    return count;
}