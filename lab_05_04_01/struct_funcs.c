#include <stdio.h>
#include <string.h>
#include "my_defines.h"
#include "struct_funcs.h"
#include <stdint.h>


void swap_structs(students_type *struct1, students_type *struct2)
{
    students_type struct3;

    struct3 = *(struct2);
    *(struct2) = *(struct1);
    *(struct1) = struct3;
}

void sort_struct(students_type students[], size_t total)
{
    int diff;
    for (size_t i = 0; i < (total - 1); i++)
    {
        for (size_t j = 0; j < (total - i - 1); j++)
        {
            diff = strcmp(students[j + 1].last_name, students[j].last_name);
            if (diff < 0)
            {
                swap_structs(&students[j + 1], &students[j]);
            }
            else if (diff == 0 && strcmp(students[j + 1].first_name, students[j].first_name) < 0)
            {
                swap_structs(&students[j + 1], &students[j]);
            }
        }
    }
}

int read_struct(FILE *f, students_type *students)
{
    int correct;

    correct = fscanf(f, "%s", students->last_name);
    if (correct != 1)
        return 0;
    correct = fscanf(f, "%s", students->first_name);
    if (correct != 1)
        return 0;
    correct = fscanf(f, "%u %u %u %u", &(students->mark[0]), &(students->mark[1]), &(students->mark[2]), &(students->mark[3]));
    if (correct != 4)
        return 0;
    return 1;
}

void write_struct(FILE *f, students_type students)
{
    fprintf(f, "%s\n", students.last_name);
    fprintf(f, "%s\n", students.first_name);
    fprintf(f, "%u %u %u %u\n", students.mark[0], students.mark[1], students.mark[2], students.mark[3]);
}