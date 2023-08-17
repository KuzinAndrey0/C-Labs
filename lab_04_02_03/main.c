#include <stdio.h>
#include <string.h>

#define STRING_LENGTH 257
#define WORD_LENGTH 16
#define TOTAL_WORDS 128

#define RETURN_SUCCESS 0
#define RETURN_ERROR 1

#define SENTENCE_SIGNS ",;:-.!? "

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


int split_sentence(char str[STRING_LENGTH], char words[TOTAL_WORDS][WORD_LENGTH])
{
    int current_word = 0;
    int current_symbol = 0;
    int in_word = 0;
    char cur_char;

    for (int i = 0; str[i] != '\0'; i ++)
    {
        cur_char = *my_strchr(SENTENCE_SIGNS, str[i]);
        if (cur_char == '\0')
        {
            words[current_word][current_symbol] = str[i];
            current_symbol ++;  
            if (current_symbol == 17)
            {
                return -1;
            }

            in_word = 1;     
        }
        else
        {
            if (in_word)
            { 
                words[current_word][current_symbol] = '\0';
                current_word ++;
                current_symbol = 0;

                in_word = 0;
            }
        }
    }
    
    words[current_word][current_symbol] = '\0';
    return (current_word + in_word);
}

int count_word(char total_words[][WORD_LENGTH], int total_words_count[], char words[][WORD_LENGTH], int total_len, int new_len)
{
    int in_array;
    int comparison;

    for (int i = 0; i < new_len; i ++)
    {
        in_array = 0;
        for (int j = 0; j < total_len; j ++)
        {
            comparison = strcmp(total_words[j], words[i]);           
            if (comparison == 0)
            {
                in_array = 1;
                total_words_count[j] ++;
            }
        }

        if (in_array == 0)
        {
            strcpy(total_words[total_len], words[i]);
            total_words_count[total_len] = 1;
            total_len ++;
        }       
    }
    return total_len;
}

int main(void)
{
    char words[TOTAL_WORDS][WORD_LENGTH];
    char total_words[TOTAL_WORDS][WORD_LENGTH];
    int total_words_count[TOTAL_WORDS];
    char str[STRING_LENGTH];
    int num;
    int word_count = 0;
    int have_needed_words = 0;
    int line_num;

    for (int k = 0; k < 2; k ++)
    {
        printf("Введите строку: ");
        line_num = read_line(str, STRING_LENGTH);

        if (line_num == -1 || strlen(str) == 0)
        {
            printf("ERROR\n");
            return RETURN_ERROR;           
        }

        num = split_sentence(str, words);
        if (num == -1)
        {
            return RETURN_ERROR;
        }
        //printf("NUM: %d", num);

        word_count = count_word(total_words, total_words_count, words, word_count, num);
    }

    // for (int i = 0; i < word_count; i ++)
    // {
    //     printf("WORD: %s, COUNT: %d\n", total_words[i], total_words_count[i]);
    // }

    if (word_count == 0)
    {
        printf("ERROR\n");
        return RETURN_ERROR;
    }

    for (int i = 0; i < word_count; i ++)
    {
        if (total_words_count[i] == 1)
        {
            have_needed_words = 1;
        }
    }

    if (!have_needed_words)
    {
        printf("ERROR\n");
        return RETURN_ERROR;
    }

    printf("Result: ");
    for (int i = 0; i < word_count; i ++)
    {
        if (total_words_count[i] == 1)
        {
            printf("%s", total_words[i]);
            if (i != (word_count - 1))
            {
                printf(" ");
            }
            else
            {
                printf("\n");
            }
        }
    }


    return RETURN_SUCCESS;
}