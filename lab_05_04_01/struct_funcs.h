#ifndef __STRUCT_FUNCS_H__

#define __STRUCT_FUNCS_H__

void swap_structs(students_type *struct1, students_type *struct2);
void sort_struct(students_type students[], size_t total);
int read_struct(FILE *f, students_type *students);
void write_struct(FILE *f, students_type students);

#endif