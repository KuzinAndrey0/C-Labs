#define _GNU_SOURCE
#include "../inc/ht_table.h"
#include "../inc/menu_funcs.h"
#include "../inc/my_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

unsigned long hash_function(char *str, int capacity)
{
    int p = 3;
    long long p_pow = 1;
    unsigned long i = 0;
    for (int j = 0; str[j]; j++)
    {
        i += str[j] * p_pow;
        p_pow *= p;
    }
    return i % capacity;
}

ht_item *create_item(char *key, char *value)
{
    // Creates a pointer to a new hash table item
    ht_item *item = (ht_item *)malloc(sizeof(ht_item));
    item->key = (char *)malloc(strlen(key) + 1);
    item->value = (char *)malloc(strlen(value) + 1);
    item->next = NULL;
    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

hash_table *create_table(int size)
{
    // Creates a new HashTable
    hash_table *table = (hash_table *)malloc(sizeof(hash_table));
    table->size = size;
    table->count = 0;
    table->items = (ht_item **)calloc(table->size, sizeof(ht_item *));
    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL;

    return table;
}

void free_item(ht_item *item)
{
    if (item->next != NULL)
    {
        free_item(item->next);
    }
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(hash_table *table)
{
    for (int i = 0; i < table->size; i++)
    {
        ht_item *item = table->items[i];
        if (item != NULL)
            free_item(item);
    }

    free(table->items);
    free(table);
}

int ht_insert(hash_table *table, char *key, char *value, int (*collision_func)(hash_table *, unsigned long, ht_item *))
{
    ht_item *item = create_item(key, value);

    unsigned long index = hash_function(key, table->size);

    ht_item *current_item = table->items[index];
    if (current_item == NULL)
    {
        if (table->count == table->size)
        {
            free_item(item);
            return RETURN_SUCCESS;
        }
        table->items[index] = item;
        table->count++;
    }
    else
    {
        if (strcmp(current_item->key, key) == 0)
        {
            strcpy(table->items[index]->value, value);
            return RETURN_SUCCESS;
        }
        else
        {
            return collision_func(table, index, item);
        }
    }
    return RETURN_SUCCESS;
}

int handle_collision_open(hash_table *table, unsigned long index, ht_item *item)
{
    // printf("A collision has been detected!\n");
    ht_item *current_item = table->items[index];
    while (current_item->next != NULL)
        current_item = current_item->next;
    current_item->next = item;

    return RETURN_SUCCESS;
    // while(strcmp(item->key, current_item->key) != NULL)
}

int handle_collision_closed(hash_table *table, unsigned long index, ht_item *item)
{
    // printf("A collision has been detected!\n");
    // printf("name: '%s'\n", item->key);
    ht_item *current_item = table->items[index];
    while (current_item != NULL && (table->size - 1) > (int)index)
    {
        index++;
        current_item = table->items[index];
    }
    if ((int)index == (table->size - 1) && current_item != NULL)
    {
        // free(item);
        free_item(item);
        return RETURN_QUEUE_OVERFLOW;
    }
    // printf("INDEX: %lu\n", index);
    table->items[index] = item;
    return RETURN_SUCCESS;
    // while(strcmp(item->key, current_item->key) != NULL)
}

char *ht_search(hash_table *table, char *key, int *cmpnum)
{
    (*cmpnum) = 0;
    int index = hash_function(key, table->size);
    ht_item *item = table->items[index];

    if (item != NULL)
    {
        while (item != NULL)
        {
            (*cmpnum)++;
            if (strcmp(item->key, key) == 0)
                return item->value;
            item = item->next;
        }
    }
    item = table->items[index];
    while (item != NULL)
    {
        (*cmpnum)++;
        if (strcmp(item->key, key) == 0)
            return item->value;
        index++;
        item = table->items[index];
    }
    return NULL;
}

void print_search(hash_table *table, char *key)
{
    char *val;
    int dummy;
    if ((val = ht_search(table, key, &dummy)) == NULL)
    {
        printf("Key: '%s' does not exist\n", key);
        return;
    }
    else
    {
        printf("Key: '%s', Value: '%s'\n", key, val);
    }
}

void print_table(hash_table *table)
{
    // printf("\nHash Table\n-------------------\n");
    printf("+------------+------------+\n");
    printf("|    INDEX   |     KEY    |\n");
    printf("+------------+------------+\n");
    int check_count = 0;
    double collision_percent = 0;
    int size = 0;
    for (int i = 0; i < table->size; i++)
    {
        if (table->items[i])
        {
            size++;
            ht_item *item = table->items[i];
            while (item != NULL)
            {
                // printf("Index:%d, Key:%s, Value:%s\n", i, item->key, item->value);
                print_table_middle(i, item->key, item->value);
                item = item->next;
                check_count++;
            }
        }
    }

    printf("+------------+------------+\n");
    if (size != 0)
    {
        collision_percent = (double)check_count / size;
        printf("Среднее кол-во сравнений: %.2lf\n\n", collision_percent);
    }
}

void file_to_string(FILE *f, char **str)
{
    int size = 0;
    char temp;
    while (!feof(f))
    {
        size++;
        fread(&temp, sizeof(char), 1, f);
    }
    *str = malloc(size);
    fseek(f, 0, SEEK_SET);
    fread(*str, sizeof(char), size - 1, f);
    (*str)[size - 1] = 0;
}
