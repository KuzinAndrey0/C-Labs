#include "find_struct.h"
#include "my_defines.h"
#include "sort_struct.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_line(FILE *f, char *str, int max_length)
{
    int i = 0;
    char chr = '\0';

    while (i <= max_length && chr != '\n')
    {
        fread(&chr, sizeof(char), 1, f);
        str[i] = chr;
        i++;

        if (chr == '\0')
            return 2;
    }

    str[i - (chr == '\n')] = '\0';
    if (i == 1 && chr == '\0')
        return 2;
    if (i == 1 && chr == '\n')
        return 3;
    return (i - 1) == max_length;
}

int read_struct(FILE *f, film_type *film)
{
    int correct;
    correct = read_line(f, film->title, TITLE_LENGTH + 1);
    if (correct != 0)
        return correct;
    correct = read_line(f, film->name, NAME_LENGTH + 1);
    if (correct != 0)
        return correct;
    correct = fscanf(f, "%d", &(film->year));
    if (correct != 1 || film->year < 0)
        return 1;
    fseek(f, sizeof(char), SEEK_CUR);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4)
        return RETURN_WRONG_FORMAT;

    FILE *f;
    f = fopen(argv[1], "r");
    if (f == NULL)
        return RETURN_NO_FILE;

    film_type films[ARRAY_SIZE];
    int total = 0;
    int correct = 0;
    int str_check = 0;
    int done = 1;
    int new_line_counter = 0;

    while (feof(f) == 0)
    {
        film_type dummy;

        correct = read_struct(f, &dummy);
        if (correct == 3)
            new_line_counter++;
        if (correct == 1)
        {
            fclose(f);
            return RETURN_WRONG_FORMAT;
        }
        if (correct == 0)
        {
            if (total < 15 && new_line_counter == 0)
            {
                films[total] = dummy;
                total++;
            }
            else
            {
                fclose(f);
                return RETURN_MANY_DATA;
            }
        }
    }
    fclose(f);

    // printf("TOTAL TOTAL: %d\n", total);
    if (total < 1)
    {
        return RETURN_EMPTY_DATA;
    }

    str_check = strcmp(argv[2], "title");

    if (str_check == 0)
    {
        sort_struct_title(films, total);

        if (argc == 3)
        {
            for (int i = 0; i < total; i++)
            {
                printf("%s\n", films[i].title);
                printf("%s\n", films[i].name);
                printf("%d\n", films[i].year);
            }
        }
        else if (argc > 3)
        {
            if (strlen(argv[3]) > TITLE_LENGTH)
                return RETURN_WRONG_FORMAT;
            int found = binary_search_title(films, argv[3], total);
            if (found == -1)
            {
                printf("Not found\n");
                // return RETURN_NOT_FOUND;
            }
            else
            {
                printf("%s\n", films[found].title);
                printf("%s\n", films[found].name);
                printf("%d\n", films[found].year);
            }
        }

        done = 0;
    }

    str_check = strcmp(argv[2], "name");

    if (str_check == 0)
    {
        sort_struct_name(films, total);

        if (argc == 3)
        {
            for (int i = 0; i < total; i++)
            {
                printf("%s\n", films[i].title);
                printf("%s\n", films[i].name);
                printf("%d\n", films[i].year);
            }
        }

        if (argc > 3)
        {
            if (strlen(argv[3]) > NAME_LENGTH)
                return RETURN_WRONG_FORMAT;
            int found = binary_search_name(films, argv[3], total);
            if (found == -1)
            {
                printf("Not found\n");
                // return RETURN_NOT_FOUND;
            }
            else
            {
                printf("%s\n", films[found].title);
                printf("%s\n", films[found].name);
                printf("%d\n", films[found].year);
            }
        }

        done = 0;
    }

    str_check = strcmp(argv[2], "year");

    if (str_check == 0)
    {
        sort_struct_year(films, total);

        if (argc == 3)
        {
            for (int i = 0; i < total; i++)
            {
                printf("%s\n", films[i].title);
                printf("%s\n", films[i].name);
                printf("%d\n", films[i].year);
            }
        }

        if (argc > 3)
        {
            if (atoi(argv[3]) < 0)
                return RETURN_WRONG_FORMAT;

            int datalen = strlen(argv[3]);

            for (int i = 0; i < datalen; i++)
                if (!isdigit(argv[3][i]))
                    return RETURN_WRONG_FORMAT;

            int found = binary_search_year(films, argv[3], total);
            if (found == -1)
            {
                printf("Not found\n");
                // return RETURN_NOT_FOUND;
            }
            else
            {
                printf("%s\n", films[found].title);
                printf("%s\n", films[found].name);
                printf("%d\n", films[found].year);
            }
        }

        done = 0;
    }

    return done;
}