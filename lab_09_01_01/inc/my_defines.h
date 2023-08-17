#ifndef __MY_DEFINES__

#define RETURN_SUCCESS 0
#define RETURN_NO_FILE 100
#define RETURN_EMPTY_DATA 150
#define RETURN_MANY_DATA 175
#define RETURN_WRONG_FORMAT 200
#define RETURN_NOT_FOUND 250
#define RETURN_MEMORY_ERROR 260

//#define TITLE_LENGTH 25
//#define NAME_LENGTH 25
//#define ARRAY_SIZE 15

typedef struct film
{
    char *title;
    char *name;
    int year;
} film_t;

#define __MY_DEFINES__

#endif