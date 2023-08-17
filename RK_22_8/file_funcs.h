#ifndef __FILE_FUNCS_H__

#define __FILE_FUNCS_H__

size_t file_size(FILE *f, size_t *size);
void change_val(FILE *f, long pos, int val);
long get_pos(FILE *f, int sign);
int fill_with_number(FILE *f, size_t count);
int get_sum(FILE *f);
int print_file(FILE *f);

#endif