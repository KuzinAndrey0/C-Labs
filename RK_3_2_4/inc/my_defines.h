#ifndef __MY_DEFINES__

#define __MY_DEFINES__

#define RETURN_SUCCESS 0
#define RETURN_ERROR_GENERIC 10
#define RETURN_NO_FILE 20
#define RETURN_WRONG_FILE 30
#define RETURN_NOT_DIGIT 40

typedef struct list_t list_t;

struct list_t
{
    int val;
    list_t *next;
};

#endif