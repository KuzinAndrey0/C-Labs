#define _GNU_SOURCE
#include "../inc/dynamic_data.h"
#include "../inc/ht_table.h"
#include "../inc/menu_funcs.h"
#include "../inc/my_defines.h"
#include "../inc/search_tree.h"
#include <ctype.h>
#include <dirent.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

// trc-ignore
typedef DIR dir_t;

struct allocated_data_s global_data;

// trc-ignore
int init_manuel_ht(hash_table **manuel, int (*collision_func)(hash_table *, unsigned long, ht_item *))
{
    dir_t *d;
    struct dirent *dir;
    d = opendir("./keywords");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_type == DT_REG)
            {
                char temp_str[100] = "./keywords/";
                strcat(temp_str, dir->d_name);

                char *temp_ptr;
                FILE *f = fopen(temp_str, "r");
                file_to_string(f, &temp_ptr);
                fclose(f);
                int rc = ht_insert(*manuel, dir->d_name, temp_ptr, collision_func);
                free(temp_ptr);
                if (rc != RETURN_SUCCESS)
                {
                    closedir(d);
                    // printf("ТРЕБУЕТСЯ РЕСТРУКТУРИЗАЦИЯыыы\n");
                    return RETURN_MEMORY_ERROR;
                }
            }
        }
        closedir(d);
    }
    return RETURN_SUCCESS;
}
// trc-ignore
void init_manuel_tree(tree_node **manuel)
{
    dir_t *d;
    struct dirent *dir;
    d = opendir("./keywords");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_type == DT_REG)
            {
                char temp_str[100] = "./keywords/";
                strcat(temp_str, dir->d_name);

                char *temp_ptr;
                FILE *f = fopen(temp_str, "r");
                file_to_string(f, &temp_ptr);
                fclose(f);

                int len = strlen(dir->d_name);
                char *name_str = calloc(len + 1, sizeof(char));
                // strcpy(name_str, dir->d_name);
                for (int i = 0; i < len; i++)
                    name_str[i] = dir->d_name[i];
                name_str[len] = 0;

                // insert(manuel, name_str, temp_ptr);
                // insert_balanced(manuel, name_str, temp_ptr);
                *manuel = insert_balanced(*manuel, name_str, temp_ptr);
            }
        }
        closedir(d);
    }
}
// trc-ignore
void init_manuel_ddptree(tree_node **manuel)
{
    dir_t *d;
    struct dirent *dir;
    d = opendir("./keywords");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_type == DT_REG)
            {
                char temp_str[100] = "./keywords/";
                strcat(temp_str, dir->d_name);

                char *temp_ptr;
                FILE *f = fopen(temp_str, "r");
                file_to_string(f, &temp_ptr);
                fclose(f);

                int len = strlen(dir->d_name);
                char *name_str = calloc(len + 1, sizeof(char));
                // strcpy(name_str, dir->d_name);
                for (int i = 0; i < len; i++)
                    name_str[i] = dir->d_name[i];
                name_str[len] = 0;

                // insert(manuel, name_str, temp_ptr);
                // insert_balanced(manuel, name_str, temp_ptr);
                insert(manuel, name_str, temp_ptr);
            }
        }
        closedir(d);
    }
}

// trc-ignore
unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long)-1;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}
// trc-ignore
void print_help_ht(hash_table *table, char *key)
{
    char *val;
    int dummy;
    if ((val = ht_search(table, key, &dummy)) == NULL)
    {
        printf("Данное ключевое слово не найдено\n");
        return;
    }
    else
    {
        printf("\033[0;34mКлючевое слово: %s\033[0m\n%s\n", key, val);
    }
}
// trc-ignore
void print_help_ddp(tree_node *table, char *key)
{
    tree_node *val;
    int dummy;
    val = tree_search(table, key, &dummy);

    if (val == NULL)
    {
        printf("Данное ключевое слово не найдено\n");
        return;
    }
    else
    {
        printf("\033[0;34mКлючевое слово: %s\033[0m\n%s\n", key, val->desc);
    }
}
// trc-ignore
char *gen_str(char *str, int charsum)
{
    int len = 0;
    str = calloc(charsum, sizeof(char));

    while (charsum > 0)
    {
        char c = (rand() % 125) + 1;
        if (c > charsum)
            c = charsum;
        str[len] = c;
        len++;
        charsum -= c;
    }

    str = realloc(str, (len + 1) * sizeof(char));
    // int sum = 0;
    // for (int i = 0; i < (int)strlen(str); i++)
    // {
    //     sum += (int)str[i];
    //     printf("%d ", str[i]);
    // }
    // printf("\nsum: %d\n", sum);
    return str;
}
// trc-ignore
char *gen_str_rand(char *str)
{
    int len = rand() % 9 + 2;

    str = malloc((len + 1) * sizeof(char));

    for (int i = 0; i < len; i++)
    {
        str[i] = 48 + (rand() % (90 - 48));
    }
    str[len] = 0;
    return str;
}
// trc-ignore
double collision_count(hash_table *table)
{
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
                item = item->next;
                check_count++;
            }
        }
    }
    if (size != 0)
    {
        collision_percent = (double)check_count / size;
        return collision_percent;
    }
    return 0;
}

// trc-ignore
void print_table_info(unsigned long long time, double percent, double collisions)
{
    char temp_str[13];
    printf("|");
    sprintf(temp_str, "%.0lf", percent);
    center_text(temp_str, 12);

    printf("|");
    sprintf(temp_str, "%.2lf", collisions);
    center_text(temp_str, 12);

    printf("|");
    sprintf(temp_str, "%llu ms", time);
    center_text(temp_str, 12);

    printf("|\n");
}

int main(void)
{
    srand(time(NULL));
    int rc = init_global_data();
    if (!rc)
        terminate_program(rc);

    size_t table_capacity = 23;

    hash_table *ht_manuel = create_table(table_capacity);
    tree_node *avl_manuel = NULL;
    tree_node *ddp_manuel = NULL;

    int (*collision_func)(hash_table *, unsigned long, ht_item *) = handle_collision_closed;

    init_manuel_tree(&avl_manuel);
    init_manuel_ddptree(&ddp_manuel);

    rc = init_manuel_ht(&ht_manuel, collision_func);

    while (rc != RETURN_SUCCESS)
    {
        printf("При размере %lu требуется реструктуризация...\n", table_capacity);
        free_table(ht_manuel);
        table_capacity *= 2;
        ht_manuel = create_table(table_capacity);
        rc = init_manuel_ht(&ht_manuel, collision_func);
    }

    FILE *test_file = fopen("AVL.gv", "w");
    tree_export(test_file, "AVL", avl_manuel);
    fclose(test_file);

    test_file = fopen("DDP.gv", "w");
    tree_export(test_file, "DDP", ddp_manuel);
    fclose(test_file);

    int working = 1;
    char input[INPUT_BUFFER];

    while (working)
    {
        printf("\nРазмер Hash-Таблицы: %lu\n", table_capacity);
        print_menu();

        rc = get_input(input, INPUT_BUFFER);

        if (rc == RETURN_SUCCESS)
        {
            if (strcmp(input, "0") == 0)
            {
                working = 0;
            }
            else if (strcmp(input, "1") == 0)
            {
                printf("Введите ключевое слово: ");
                rc = get_input(input, INPUT_BUFFER);
                if (rc == RETURN_SUCCESS)
                {
                    print_help_ht(ht_manuel, input);
                }
            }
            else if (strcmp(input, "2") == 0)
            {
                printf("Введите ключевое слово: ");
                rc = get_input(input, INPUT_BUFFER);
                if (rc == RETURN_SUCCESS)
                {
                    print_help_ddp(avl_manuel, input);
                }
            }
            else if (strcmp(input, "3") == 0)
            {
                printf("Введите ключевое слово: ");
                rc = get_input(input, INPUT_BUFFER);
                if (rc == RETURN_SUCCESS)
                {
                    unsigned long long totaltime = 0;
                    int search_count;
                    for (int j = 0; j < 10; j++)
                    {
                        unsigned long long time = milliseconds_now();

                        for (int i = 0; i < 10000; i++)
                        {
                            ht_search(ht_manuel, input, &search_count);
                        }

                        totaltime += milliseconds_now() - time;
                    }
                    printf("Среднее время поиска: %llu мс\n", totaltime / 10);
                    unsigned long long memory = 0;
                    memory = ht_manuel->size * sizeof(ht_item) + sizeof(hash_table);
                    printf("Использованная память: %llu байт\n", memory);
                    printf("Кол-во сравнений: %d\n", search_count);
                }
            }
            else if (strcmp(input, "4") == 0)
            {
                printf("Введите ключевое слово: ");
                rc = get_input(input, INPUT_BUFFER);
                int search_count;
                if (rc == RETURN_SUCCESS)
                {
                    unsigned long long totaltime = 0;
                    for (int j = 0; j < 10; j++)
                    {
                        unsigned long long time = milliseconds_now();
                        for (int i = 0; i < 10000; i++)
                            tree_search(avl_manuel, input, &search_count);

                        totaltime += milliseconds_now() - time;
                    }
                    printf("Среднее время поиска: %llu мс\n", totaltime / 10);
                    unsigned long long memory = 0;
                    memory = ht_manuel->count * sizeof(tree_node);
                    printf("Использованная память: %llu байт\n", memory);
                    printf("Кол-во сравнений: %d\n", search_count);
                }
            }
            else if (strcmp(input, "5") == 0)
            {
                printf("Введите ключевое слово: ");
                rc = get_input(input, INPUT_BUFFER);
                int search_count;
                if (rc == RETURN_SUCCESS)
                {
                    unsigned long long totaltime = 0;
                    for (int j = 0; j < 10; j++)
                    {
                        unsigned long long time = milliseconds_now();
                        for (int i = 0; i < 10000000; i++)
                            tree_search(ddp_manuel, input, &search_count);

                        totaltime += milliseconds_now() - time;
                    }
                    printf("Среднее время поиска: %llu мс\n", totaltime / 10);
                    unsigned long long memory = 0;
                    memory = ht_manuel->count * sizeof(tree_node);
                    printf("Использованная память: %llu байт\n", memory);
                    printf("Кол-во сравнений: %d\n", search_count);
                }
            }
            else if (strcmp(input, "6") == 0)
            {
                print_table(ht_manuel);
            }
            else if (strcmp(input, "7") == 0)
            {
                printf("Введите новый размер таблицы: ");
                int temp_num;
                rc = get_input_num(input, INPUT_BUFFER, &temp_num);
                if (rc == RETURN_SUCCESS)
                {
                    table_capacity = temp_num;
                    free_table(ht_manuel);
                    ht_manuel = create_table(table_capacity);
                    rc = init_manuel_ht(&ht_manuel, collision_func);

                    while (rc != RETURN_SUCCESS)
                    {
                        printf("При размере %lu требуется реструктуризация...\n", table_capacity);
                        free_table(ht_manuel);
                        table_capacity *= 2;
                        ht_manuel = create_table(table_capacity);
                        rc = init_manuel_ht(&ht_manuel, collision_func);
                    }
                }
                else
                {
                    printf("Неверный ввод\n");
                }
            }
            else if (strcmp(input, "8") == 0)
            {
                printf("+------------+------------+------------+\n");
                printf("|ORIGINALITY | CHECK COUNT|    TIME    |\n");
                printf("+------------+------------+------------+\n");
                int test_capacity = 50;
                for (double percent = 1; percent >= 0; percent -= 0.25)
                {
                    int unique_names = test_capacity * percent;

                    if (unique_names < 1)
                        unique_names = 1;

                    hash_table *ht_testing = create_table(test_capacity);
                    char *name, *desc;

                    char *savename = NULL;
                    int rngname = rand() % test_capacity;
                    for (int i = 0; i < test_capacity; i++)
                    {
                        name = gen_str(name, (i % unique_names) + 1000);
                        desc = gen_str_rand(desc);
                        ht_insert(ht_testing, name, desc, handle_collision_open);
                        if (rngname)
                        {
                            free(savename);
                            savename = malloc((strlen(name) + 1) * sizeof(char));
                            for (int i = 0; i < (int)strlen(name); i++)
                            {
                                savename[i] = name[i];
                            }
                            savename[strlen(name)] = '\0';
                        }
                        free(name);
                        free(desc);
                    }
                    unsigned long long totaltime = 0;
                    int dummy;
                    (void)dummy;
                    for (int j = 0; j < 10; j++)
                    {
                        unsigned long long time = milliseconds_now();
                        for (int i = 0; i < 1000; i++)
                            ht_search(ht_testing, savename, &dummy);

                        totaltime += milliseconds_now() - time;
                    }
                    free(savename);
                    // printf("Среднее время поиска: %llu\n", totaltime / 10);
                    // printf("Уникальных имен: %.0lf%%\n", percent * 100);
                    double collisions = collision_count(ht_testing);
                    print_table_info(totaltime / 10, percent * 100, collisions);
                    free_table(ht_testing);
                }
                printf("+------------+------------+------------+\n");
                printf("\033[0;34mУспешно\033[0m\n");
            }
            else if (strcmp(input, "9") == 0)
            {
                if (collision_func == handle_collision_closed)
                {
                    printf("Теперь используется: открытое хэширование\n");
                    collision_func = handle_collision_open;
                    rc = 1;
                    while (rc != RETURN_SUCCESS)
                    {
                        free_table(ht_manuel);
                        table_capacity *= 2;
                        ht_manuel = create_table(table_capacity);
                        rc = init_manuel_ht(&ht_manuel, collision_func);
                    }
                }
                else if (collision_func == handle_collision_open)
                {
                    printf("Теперь используется: закрытое хэширование\n");
                    collision_func = handle_collision_closed;
                    rc = 1;
                    while (rc != RETURN_SUCCESS)
                    {
                        free_table(ht_manuel);
                        table_capacity *= 2;
                        ht_manuel = create_table(table_capacity);
                        rc = init_manuel_ht(&ht_manuel, collision_func);
                    }
                }
                printf("\033[0;34mУспешно\033[0m\n");
            }
        }
    }

    free_table(ht_manuel);
    free_tree(avl_manuel);
    free_tree(ddp_manuel);
    terminate_program(RETURN_SUCCESS);
}
