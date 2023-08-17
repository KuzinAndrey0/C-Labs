#ifndef __MY_DEFINES__

#define __MY_DEFINES__

#define RETURN_SUCCESS 0
#define RETURN_WRONG_FORMAT 10
#define RETURN_EMPTY_FILE 20
#define RETURN_NO_FILE 30
#define RETURN_MEMORY_ERROR 40
#define RETURN_NOT_ENOUGH_ARGUMENTS 50
#define RETURN_EMPTY_FILE_AFTER 60
#define RETURN_WRONG_ARGUMENTS 70
#define RETURN_QUANTITY_NOT_NUM 80

typedef struct product_t
{
    char *name;
    char *category;
    int quantity;
    int cost;
} product_t;

//Название товара
//Категория товара
//Кол-во
//Цена

#endif