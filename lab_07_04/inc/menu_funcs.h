#ifndef __MENU_FUNCS__

// trc-ignore
#define __MENU_FUNCS__

// trc-ignore
void center_text(char *text, int width);
// trc-ignore
void print_menu(void);
// trc-ignore
int is_integer(char str[]);
// trc-ignore
int get_input(char str[], unsigned max_length);
// trc-ignore
int get_input_num(char str[], unsigned max_length, int *num);
// trc-ignore
void print_table_middle(int size, char *key, char *value);

#endif