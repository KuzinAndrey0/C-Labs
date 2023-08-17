#include <stdio.h>
#include <string.h>
#include "my_defines.h"
#include "struct_funcs.h"
#include <stdint.h>

size_t file_size(FILE *f, size_t *size)
{
    long new_size;

    if (fseek(f, 0L, SEEK_END))
        return 1;

    new_size = ftell(f);
    if (new_size <= 0)
        return 1;

    *size = new_size;

    return fseek(f, 0L, SEEK_SET);
}

int main(int argc, char **argv)
{
    FILE *f, *f_out;
    int str_check, correct;
    size_t total, size, fs;
    total = 0;
    students_type students[ARRAY_SIZE];    

    if (argc < 3)
        return RETURN_WRONG_KEYS;   

    str_check = strcmp(argv[1], "st");
    if (str_check == 0)
    {
        f = fopen(argv[2], "r");

        if (f == NULL)
            return RETURN_NO_FILE;   
    
        fs = file_size(f, &size);

        if (fs == 1 || size <= 0)
            return RETURN_NO_FILE; 
        
        while (feof(f) == 0)
        {
            correct = read_struct(f, &students[total]);
            total ++;
        }

        fclose(f);

        total -= 1;

        if (total > 1)
            sort_struct(students, total);

        for (size_t i = 0; i < total; i ++)
        {
            printf("%s\n%s\n%u %u %u %u\n", students[i].last_name, students[i].first_name, students[i].mark[0], students[i].mark[1], students[i].mark[2], students[i].mark[3]);
        }
        return RETURN_SUCCESS;
    }

    str_check = strcmp(argv[1], "ft");
    if (str_check == 0)
    {
        if (argc < 5)
            return RETURN_WRONG_KEYS;   
        
        size_t len = strlen(argv[4]);

        f = fopen(argv[2], "r");

        if (f == NULL)
            return RETURN_NO_FILE;
  
        fs = file_size(f, &size);

        if (fs == 1 || size <= 0)
            return RETURN_NO_FILE; 


        f_out = fopen(argv[3], "w");
        if (f_out == NULL)
        {
            fclose(f);
            return RETURN_NO_FILE;
        }  

        while (feof(f) == 0)
        {
            correct = read_struct(f, &students[total]);

            if (!correct && feof(f) == 0)
            {
                fclose(f);
                fclose(f_out);
                return RETURN_NO_FILE;
            }
            total ++;
        }

        total -= 1;

        if (len <= 0 || len > 25)
        {
            fclose(f);
            fclose(f_out);
            return RETURN_WRONG_KEYS;
        }

        int cont = 0;      
        for (size_t i = 0; i < total; i ++)
        {
            if (strncmp(students[i].last_name, argv[4], len) == 0)
            {
                write_struct(f_out, students[i]);
                printf("%s\n%s\n%u %u %u %u\n", students[i].last_name, students[i].first_name, students[i].mark[0], students[i].mark[1], students[i].mark[2], students[i].mark[3]);                
                cont ++;
            }
        }

        fclose(f);
        fclose(f_out);

        if (cont == 0)
            return RETURN_NO_FILE;

        return RETURN_SUCCESS;
    }

    return RETURN_WRONG_KEYS;
}