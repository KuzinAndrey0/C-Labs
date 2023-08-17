#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STRING_LENGTH 257
#define WORD_LENGTH 16
#define TOTAL_WORDS 128

#define RETURN_SUCCESS 0
#define RETURN_ERROR 1

//[+D](DDD)-DDD-DD-DD
// 15 - 17

void delete_pos(char word[], int pos)
{
    memmove(&word[pos], &word[pos + 1], strlen(word) - pos);
}

int is_num(char chr)
{
    return (chr >= 48 && chr <= 57);
}

size_t read_line(char *s, size_t n)
{
    int ch;
    size_t i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
        if (i < n - 1)
            s[i++] = ch;
        else
            return -1;
    s[i] = '\0';
    return i;
}

int is_telephone(char input[], int num)
{
    int offset = 0;    
    while (isspace(input[0]))
    {
        delete_pos(input, 0);
        num --;
    }

    if (num < 15)
        return 0;
    if (input[0] == '+')
    {
        offset = 1;
        while (is_num(input[offset]))
        {
            //printf("NUM: %c\n", input[offset]);            
            offset ++;
        }

        //printf("SKOBKA: %c\n", input[offset]);
        if (input[offset] != '(' || offset == 1)
            return 0;
        if (num < (15 + offset))
        {
            return 0;
        }
    }

    while (isspace(input[15 + offset]))
    {
        delete_pos(input, 15 + offset);
        num --;
    }

    if (num != (15 + offset))
    {
        return 0;
    }

    if (input[0 + offset] == '(' &&
        is_num(input[1 + offset]) &&
        is_num(input[2 + offset]) &&
        is_num(input[3 + offset]) &&  
        input[4 + offset] == ')' &&  
        input[5 + offset] == '-' &&
        is_num(input[6 + offset]) &&
        is_num(input[7 + offset]) &&
        is_num(input[8 + offset]) &&
        input[9 + offset] == '-' &&
        is_num(input[10 + offset]) &&
        is_num(input[11 + offset]) &&
        input[12 + offset] == '-' &&
        is_num(input[13 + offset]) &&
        is_num(input[14 + offset]))
    {
        return 1;       
    }
    else
    {
        return 0;
    }
}

int main(void)
{
    char input[STRING_LENGTH];
    int num;

    num = read_line(input, STRING_LENGTH);

    if (num == -1)
        return RETURN_ERROR;

    int is_num = is_telephone(input, num);

    if (is_num)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }


    return RETURN_SUCCESS;
}