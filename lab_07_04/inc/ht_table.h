#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"

#ifndef __HT_TABLE__

// trc-ignore
#define __HT_TABLE__

// Строка хэш таблицы
typedef struct ht_item ht_item;
// Строка хэш таблицы
struct ht_item
{
    char *key;
    char *value;
    ht_item *next;
};

// Хэш таблица
typedef struct hash_table hash_table;
// Хэш таблица
struct hash_table
{
    ht_item **items;
    int size;
    int count;
};

// trc-ignore
ht_item *create_item(char *key, char *value);
// trc-ignore
hash_table *create_table(int size);
// trc-ignore
void free_item(ht_item *item);
// trc-ignore
void free_table(hash_table *table);
/*
Коллизия при открытом хешировании - новый элемент связывается списком к существующему
*/
int handle_collision_open(hash_table *table, unsigned long index, ht_item *item);
/*
Коллизия при закрытом хешировании - ищется следующий неиспользуемый хэш, если такого нет - требуется реструктуризация
*/
int handle_collision_closed(hash_table *table, unsigned long index, ht_item *item);
/*
Добавление элемента в хэш таблицу
*/
int ht_insert(hash_table *table, char *key, char *value, int (*collision_func)(hash_table *, unsigned long, ht_item *));
/*
Поиск в хэш таблице
*/
char *ht_search(hash_table *table, char *key, int *cmpnum);
// trc-ignore
void print_search(hash_table *table, char *key);
// trc-ignore
void print_table(hash_table *table);
// trc-ignore
void file_to_string(FILE *f, char **str);
/*
Хэш-функция для хэш таблицы, использует полиномиальное хэширование строки и результат делится на размер таблицы
*/
unsigned long hash_function(char *str, int capacity);

#endif