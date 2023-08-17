#define _GNU_SOURCE
#include "../inc/my_defines.h"
#include <ctype.h>
#include <dirent.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

void center_text(char *text, int width)
{
    int pad1 = (width - strlen(text)) / 2;
    int pad2 = width - pad1 - strlen(text);
    printf("%*s%s%*s", pad1, " ", text, pad2, " ");
}

void left_text(char *text, int width)
{
    int pad = width - strlen(text);
    printf("%s%*s", text, pad, " ");
}

void print_table_middle(char *fname, int words, int newlines)
{
    char temp_str[100];
    printf("|");
    center_text(fname, 30);

    printf("|");
    sprintf(temp_str, "%d", words);
    center_text(temp_str, 15);

    printf("|");
    sprintf(temp_str, "%d", newlines);
    center_text(temp_str, 15);

    printf("|\n");
}

void print_table_dir(char *fname)
{
    char temp_str[100];
    printf("\033[0;34m|");
    left_text(fname, 30);

    printf("|");
    temp_str[0] = 0;
    center_text(temp_str, 15);

    printf("|");
    temp_str[0] = 0;
    center_text(temp_str, 15);

    printf("|\033[0m\n");
}

int read_newlines(FILE *f)
{
    int count = -1;

    char temp;
    fseek(f, 0, SEEK_SET);
    while (!feof(f))
    {
        fread(&temp, sizeof(char), 1, f);
        if (temp == '\n')
            count++;
    }

    return count;
}

int read_words(FILE *f)
{
    int count = 0;

    char temp;
    int in_word = 1;
    fseek(f, 0, SEEK_SET);
    while (!feof(f))
    {
        fread(&temp, sizeof(char), 1, f);

        if (isspace(temp))
        {
            if (in_word)
            {
                count++;
                in_word = 0;
            }
        }
        else
        {
            if (!in_word)
            {
                in_word = 1;
            }
        }
    }

    if (in_word)
        count++;

    return count;
}

int get_file_info(FILE *f, int *words_count, int *new_line_count)
{
    *words_count = read_words(f);
    *new_line_count = read_newlines(f);

    return RETURN_SUCCESS;
}

int read_dir(char *folder)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(folder);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_type == DT_REG)
            {
                char temp_str[100];
                strcpy(temp_str, folder);
                strcat(temp_str, "/");
                strcat(temp_str, dir->d_name);

                FILE *f = fopen(temp_str, "r");
                int words_count, new_line_count;

                int rc = get_file_info(f, &words_count, &new_line_count);
                fclose(f);

                // printf("file: %s lines: %d words: %d\n", dir->d_name, new_line_count, words_count);
                print_table_middle(dir->d_name, words_count, new_line_count);

                if (rc != RETURN_SUCCESS)
                {
                    closedir(d);
                    return RETURN_MEMORY_ERROR;
                }
            }
        }
        closedir(d);
    }
    return RETURN_SUCCESS;
}

int read_dirs(int count, ...)
{
    va_list args;
    va_start(args, count);

    printf("+------------------------------+---------------+---------------+\n");
    printf("|      Filename                |  Word count   | Newline Count |\n");
    printf("+------------------------------+---------------+---------------+\n");
    for (int i = 0; i < count; i++)
    {
        char *dir = va_arg(args, char *);
        print_table_dir(dir);
        read_dir(dir);
    }

    va_end(args);
    printf("+------------------------------+---------------+---------------+\n");
    return RETURN_SUCCESS;
}

int main(void)
{
    read_dirs(2, "./inc", "./src");

    return RETURN_SUCCESS;
}