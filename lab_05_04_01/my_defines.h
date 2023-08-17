#ifndef __MY_DEFINES_H__
#define __MY_DEFINES_H__

#define RETURN_SUCCESS 0
#define RETURN_WRONG_KEYS 53
#define RETURN_WRONG_FILE -1
#define RETURN_NO_FILE -2
#define RETURN_LONG_STR -3

#define ARRAY_SIZE 1000
#define KEY_SIZE 100

#define FIRST_NAME_LENGTH 11
#define LAST_NAME_LENGTH 26
#include <stdint.h>

typedef struct student
{
    char last_name[LAST_NAME_LENGTH];
    char first_name[FIRST_NAME_LENGTH];
    uint32_t mark[4];
} students_type;

#endif