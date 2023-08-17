#define _GNU_SOURCE
#include "../inc/find_struct.h"
#include "../inc/my_defines.h"
#include "../inc/sort_struct.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_line(FILE *f, char **str)
{
    ssize_t size = 0;
    size_t len = 0;

    size = getline(str, &len, f);

    if (size <= 0)
    {
        free(*str);
        return 1;
    }

    if ((*str)[size - 1] == '\n')
    {
        (*str)[size - 1] = '\0';
        size--;

        if (size == 0)
        {
            free(*str);
            return 1;
        }
    }

    if ((*str)[size - 1] == '\r')
    {
        (*str)[size - 1] = '\0';
        size--;

        if (size == 0)
        {
            free(*str);
            return 1;
        }
    }
    
    return 0;
}

film_t *film_create()
{
    film_t *new_film;

    new_film = calloc(1, sizeof(film_t));

    if (new_film == NULL)
    {
        return NULL;
    }

    return new_film;
}

void film_free(film_t *film)
{
    free(film->name);
    free(film->title);
    free(film);
}

int film_init(film_t *film, const char *title, const char *name, int year)
{
    char *new_title, *new_name;

    new_title = strdup(title);
    new_name = strdup(name);

    if (new_title == NULL || new_name == NULL)
    {
        free(new_name);
        free(new_title);

        return RETURN_MEMORY_ERROR;
    }

    film->name = new_name;
    film->title = new_title;
    film->year = year;

    return RETURN_SUCCESS;
}

int film_copy(const film_t *film_src, film_t *film_dst)
{
    film_dst = film_create();
    if (film_dst == NULL)
    {
        return RETURN_MEMORY_ERROR;
    }
    int rc = film_init(film_dst, film_src->title, film_src->name, film_src->year);

    return rc;
}

int film_read_ex(FILE *f, film_t **film)
{
    int correct;
    char *tmp_str[2];
    tmp_str[0] = NULL;
    tmp_str[1] = NULL;
    int tmp_year;
    film_t *tmp_film;

    correct = read_line(f, &(tmp_str[0]));
    if (correct != 0)
    {
        return correct;
    }

    correct = read_line(f, &(tmp_str[1]));

    if (correct != 0)
    {
        free(tmp_str[0]);
        return correct;
    }

    correct = fscanf(f, "%d", &tmp_year);

    if (correct != 1 || tmp_year < 0)
    {
        free(tmp_str[0]);
        free(tmp_str[1]);
        return 1;
    }

    char test_newline;
    int test_num;
    test_num = fread(&test_newline, sizeof(char), 1, f);
    if (test_num != 0)
    {
        if (test_newline == '\r')
            fread(&test_newline, sizeof(char), 1, f);
        if (test_newline != '\n')
        {
            free(tmp_str[0]);
            free(tmp_str[1]);
            printf("Wrong format\n");
            return 1;
        }
    }

    tmp_film = film_create();
    if (tmp_film == NULL)
    {
        free(tmp_str[0]);
        free(tmp_str[1]);
        return 2;
    }

    correct = film_init(tmp_film, tmp_str[0], tmp_str[1], tmp_year);

    if (correct != 0)
    {
        free(tmp_str[0]);
        free(tmp_str[1]);
        film_free(tmp_film);
        return 3;
    }

    free(tmp_str[0]);
    free(tmp_str[1]);
    *film = tmp_film;
    return RETURN_SUCCESS;
}

int is_eof(FILE *f)
{
    char buf;
    long prev = ftell(f);
    int num;

    num = fread(&buf, sizeof(char), 1, f);
    fseek(f, prev, SEEK_SET);
    if (feof(f) || num == 0 || buf == 0)
    {
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4)
        return RETURN_WRONG_FORMAT;

    int rc;
    int total = 0;
    int memory_total = 10;
    int memory_step = 10;
    int done = 1;

    film_t **films = malloc(memory_total * sizeof(film_t *));
    if (films == NULL)
        return RETURN_MEMORY_ERROR;

    FILE *f;

    f = fopen(argv[1], "r");
    if (f == NULL)
    {
        free(films);
        return RETURN_NO_FILE;
    }

    rc = 0;
    while (rc == 0)
    {
        rc = film_read_ex(f, &(films[total]));
        if (rc == 0)
        {
            total++;
            if (is_eof(f))
                break;
            if (total >= memory_total)
            {
                film_t **test_ptr;
                test_ptr = realloc(films, (memory_step + memory_total) * sizeof(film_t *));
                if (test_ptr == NULL)
                {
                    for (int i = 0; i < total; i++)
                    {
                        film_free(films[i]);
                    }
                    rc = 1;
                }
                films = test_ptr;
                memory_total += memory_step;
            }
        }
    }
    fclose(f);

    if (rc != 0)
    {
        for (int i = 0; i < total; i++)
        {
            film_free(films[i]);
        }
        free(films);
        return rc;
    }

    if (total < 1)
    {
        for (int i = 0; i < total; i++)
        {
            film_free(films[i]);
        }
        free(films);
        return RETURN_EMPTY_DATA;
    }

    // for (int i = 0; i < total; i++)
    // {
    //     printf("%s\n", films[i]->title);
    //     printf("%s\n", films[i]->name);
    //     printf("%d\n", films[i]->year);
    // }

    if (strcmp(argv[2], "title") == 0)
    {
        // printf("Hello '%s'\n", argv[2]);
        sort_struct_title(films, total);

        if (argc == 3)
        {
            for (int i = 0; i < total; i++)
            {
                printf("%s\n", films[i]->title);
                printf("%s\n", films[i]->name);
                printf("%d\n", films[i]->year);
            }
        }
        else if (argc > 3)
        {
            int found = binary_search_title(films, argv[3], total);
            if (found == -1)
            {
                printf("Not found\n");
                // return RETURN_NOT_FOUND;
            }
            else
            {
                printf("%s\n", films[found]->title);
                printf("%s\n", films[found]->name);
                printf("%d\n", films[found]->year);
            }
        }

        done = 0;
    }

    if (strcmp(argv[2], "name") == 0)
    {
        sort_struct_name(films, total);

        if (argc == 3)
        {
            for (int i = 0; i < total; i++)
            {
                printf("%s\n", films[i]->title);
                printf("%s\n", films[i]->name);
                printf("%d\n", films[i]->year);
            }
        }

        if (argc > 3)
        {
            int found = binary_search_name(films, argv[3], total);
            if (found == -1)
            {
                printf("Not found\n");
                // return RETURN_NOT_FOUND;
            }
            else
            {
                printf("%s\n", films[found]->title);
                printf("%s\n", films[found]->name);
                printf("%d\n", films[found]->year);
            }
        }

        done = 0;
    }

    if (strcmp(argv[2], "year") == 0)
    {
        sort_struct_year(films, total);

        if (argc == 3)
        {
            for (int i = 0; i < total; i++)
            {
                printf("%s\n", films[i]->title);
                printf("%s\n", films[i]->name);
                printf("%d\n", films[i]->year);
            }
        }

        if (argc > 3)
        {
            if (atoi(argv[3]) < 0)
            {
                for (int i = 0; i < total; i++)
                {
                    film_free(films[i]);
                }
                free(films);
                return RETURN_WRONG_FORMAT;
            }

            int datalen = strlen(argv[3]);

            for (int i = 0; i < datalen; i++)
                if (!isdigit(argv[3][i]))
                {
                    for (int i = 0; i < total; i++)
                    {
                        film_free(films[i]);
                    }
                    free(films);
                    return RETURN_WRONG_FORMAT;
                }

            int found = binary_search_year(films, argv[3], total);
            if (found == -1)
            {
                printf("Not found\n");
                // return RETURN_NOT_FOUND;
            }
            else
            {
                printf("%s\n", films[found]->title);
                printf("%s\n", films[found]->name);
                printf("%d\n", films[found]->year);
            }
        }

        done = 0;
    }

    for (int i = 0; i < total; i++)
    {
        film_free(films[i]);
    }
    free(films);

    return done;
}