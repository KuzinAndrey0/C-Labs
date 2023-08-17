#ifndef __FILE_FUNCS_H__

#define __FILE_FUNCS_H__

int get_number_by_pos(FILE *f, size_t pos);
void put_number_by_pos(FILE *f, size_t pos, int num);
size_t file_size(FILE *f, size_t *size);
int print_file(FILE *f);
int fill_with_number(FILE *f, size_t count);
int sort_file(FILE *f);

#endif