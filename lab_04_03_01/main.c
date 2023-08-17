#include <stdio.h>
#include <string.h>

#define STRING_LENGTH 257
#define WORD_LENGTH 16
#define TOTAL_WORDS 128

#define RETURN_SUCCESS 0
#define RETURN_ERROR 1

#define SENTENCE_SIGNS ",;:-.!? "

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
char *my_strchr(char str1[], char chr)
{
    int i;
    for (i = 0; str1[i] != '\0'; i ++)
    {
        if (str1[i] == chr)
            return &str1[i];
    }
    return &str1[i];
}

// Удалить первые вхождения каждой буквы

void delete_pos(char word[], int pos)
{
    memmove(&word[pos], &word[pos + 1], strlen(word) - pos);
}
void modify_word(char word[])
{
    int deleted_symbols_num = 0;
    char deleted_symbols[WORD_LENGTH + 1] = "";

   
    char comparison;
    for (int i = 0; word[i] != '\0'; i ++)
    {
        comparison = *my_strchr(deleted_symbols, word[i]);
        //printf("comp: %s %c\n", deleted_symbols, word[i]);

        if (comparison == '\0')
        {
            deleted_symbols[deleted_symbols_num] = word[i];        
            deleted_symbols_num ++;
        }
        else
        {
            delete_pos(word, i); 
            i --;                               
        }   
    }
    // for ( int i = 0; i < deleted_symbols_num; i ++)
    // {
    //     printf("char: %c \n", deleted_symbols[i]);
    // }    
}

int get_word_array(char str[], char words[TOTAL_WORDS][WORD_LENGTH + 1])
{
    char *cur_word;
    int total_words = 0;
    (void) words;

    cur_word = strtok(str, SENTENCE_SIGNS);

    while (cur_word)
    {
        if (strlen(cur_word) > 16)
        {
            return -1;
        }
        strcpy(words[total_words], cur_word);
        //printf("[%s]\n", cur_word);
        total_words ++;

        cur_word = strtok(NULL, SENTENCE_SIGNS);
    }
    
    return total_words;
}

int main(void)
{
    char str[STRING_LENGTH];
    char words[TOTAL_WORDS][WORD_LENGTH + 1];
    char output[STRING_LENGTH] = "";
    int word_num;
    int num;

    printf("Введите строку: ");
    num = read_line(str, STRING_LENGTH);
 
    if (num == -1)
        return RETURN_ERROR;   

    word_num = get_word_array(str, words);
    if (word_num == -1)
        return RETURN_ERROR;

    //printf("OLD: %s\n", words[word_num - 1]);
    modify_word(words[word_num - 1]);
    //printf("NEW: %s\n", words[word_num - 1]);
    for (int i = (word_num - 2); i >= 0; i --)
    {
    //printf("OLDi: %s\n", words[word_num - 1]);       
        modify_word(words[i]);
    //printf("NEWi: %s\n", words[word_num - 1]);
        //printf("COMPARE: %s %s\n", words[i], words[word_num - 1]);
        if (strcmp(words[i], words[word_num - 1]) != 0)
        {
            //printf("WORD: %s %d\n", words[i], i);
            
            //printf("NWORD: %s\n", words[i]);            
            if (strlen(words[i]) > 0)
            {
                strcat(output, words[i]);
                strcat(output, " ");
            }
        }
    }

    if (strlen(output) == 0)
    {
        return RETURN_ERROR;
    }

    output[strlen(output) - 1] = '\0';

    printf("Result: %s\n", output);


    return RETURN_SUCCESS;
}