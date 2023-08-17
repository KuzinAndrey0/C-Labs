#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_SIZE 1000

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("Not enough arguments, the format is \"*.exe [format] [source] [destination].\"\n");
        return 1;
    }

    FILE *f, *f_out, *f_data;

    char cur_type[STRING_SIZE];
    int correct;
    int str_len;

    //Init types
    char cur_str[STRING_SIZE];
    int cur_int;
    double cur_double;

    f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Wrong format path.\n");
        return 1;
    }
    f_data = fopen(argv[2], "r");
    if (f_data == NULL)
    {
        printf("Wrong input path.\n");
        return 1;
    }
    f_out = fopen(argv[3], "wb");
    if (f_data == NULL)
    {
        printf("Wrong output path.\n");
        return 1;
    }

    while (feof(f) == 0)
    {
        correct = fscanf(f, "%s", cur_type);
        if (correct && feof(f) == 0)
        {
            if (strcmp(cur_type, "int") == 0)
            {
                fscanf(f_data, "%d", &cur_int);
                fwrite(&cur_int, sizeof(int), 1, f_out);
            }

            if (strcmp(cur_type, "double") == 0)
            {
                fscanf(f_data, "%lf", &cur_double);
                fwrite(&cur_double, sizeof(double), 1, f_out);
            }            

            if (strncmp(cur_type, "char", 4) == 0)
            {
                str_len = atoi(&(cur_type[4]));
                fscanf(f_data, "%s", cur_str);
                fwrite(&cur_str, sizeof(char) * str_len, 1, f_out);
            }
        }
    }

    fclose(f);
    fclose(f_out);
    fclose(f_data);
}