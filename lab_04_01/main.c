#include <stdio.h>
#include <string.h>
#define STRING_LENGTH 257

char *my_strchr(char str1[], int c)
{
    int i;
    char chr = c;
    for (i = 0; str1[i] != '\0'; i ++)
    {
        if (str1[i] == chr)
            return &str1[i];
    }
    return chr == '\0' ? &str1[i] : NULL;
}

char *my_strrchr(char str1[], int c)
{
    int i;
    char chr = c;
    char *p = NULL;
    for (i = 0; str1[i] != '\0'; i ++)
    {
        if (str1[i] == chr)
            p = &str1[i];
    }
    if (p != NULL)
    {
        return p;
    }
    return chr == '\0' ? &str1[i] : NULL;
}

char *my_strpbrk(char str1[], char str2[])
{
    int i;
    for (i = 0; str1[i] != '\0'; i ++)
    {
        for (int j = 0; str2[j] != '\0'; j ++)
        {
            if (str1[i] == str2[j])
            {
                return &str1[i];
            }
        }
    }
    return NULL;
}

size_t my_strspn(char str1[], char str2[])
{
    int count = 0;
    int success = 0;
    for (int i = 0; str1[i] != '\0'; i ++)
    {
        for (int j = 0; str2[j] != '\0'; j ++)
        {
            if (str1[i] == str2[j])
            {
                success += 1;
            }
        }
        if (success == 0)
        {
            return count;
        }
        else
        {
            success = 0;
            count ++;
        }
    }
    return count;
}

size_t my_strcspn(char str1[], char str2[])
{
    int count = 0;
    int success = 0;
    for (int i = 0; str1[i] != '\0'; i ++)
    {
        for (int j = 0; str2[j] != '\0'; j ++)
        {
            if (str1[i] == str2[j])
            {
                success += 1;
            }
        }
        if (success != 0)
        {
            return count;
        }
        else
        {
            success = 0;
            count ++;
        }
    }

    return count;
}

int main(void)
{
    int errors = 0;
    char str1[STRING_LENGTH];
    char str2[STRING_LENGTH];
    char chr;

    //Символ в исходной и искаемой строке посередине

    strcpy(str1, "string1");
    strcpy(str2, "helio");
    if (strpbrk(str1, str2) != my_strpbrk(str1, str2))
        errors ++;

    //Символа в исходной строке нет
    strcpy(str1, "string1");
    strcpy(str2, "hello");
    if (strpbrk(str1, str2) != my_strpbrk(str1, str2))
        errors ++;

    //Строка 2 - ноль
    strcpy(str1, "string1");
    strcpy(str2, "\0");
    if (strpbrk(str1, str2) != my_strpbrk(str1, str2))
        errors ++;

    //Исходная строка пустая
    strcpy(str1, "");
    strcpy(str2, "q");
    if (strpbrk(str1, str2) != my_strpbrk(str1, str2))
        errors ++;

    //Искаемая строка пустая
    strcpy(str1, "string");
    strcpy(str2, "");
    if (strpbrk(str1, str2) != my_strpbrk(str1, str2))
        errors ++;


    printf("strpbrk: %d\n", errors);
    errors = 0;

    //Несколько символов
    strcpy(str1, "0123456789");
    strcpy(str2, "52310");
    if (strspn(str1, str2) != my_strspn(str1, str2))
        errors ++;

    //Символы в искаемой строке повторяются
    strcpy(str1, "0123456789");
    strcpy(str2, "353001122");
    if (strspn(str1, str2) != my_strspn(str1, str2))
        errors ++;    

   //Один символ
    strcpy(str1, "0123456789");
    strcpy(str2, "3530022");
    if (strspn(str1, str2) != my_strspn(str1, str2))
        errors ++;              

   //Искаемая строка - ноль
    strcpy(str1, "0123456789");
    strcpy(str2, "\0");
    if (strspn(str1, str2) != my_strspn(str1, str2))
        errors ++;              

    printf("strspn: %d\n", errors);
    errors = 0;


    //Несколько символов
    strcpy(str1, "0123456789");
    strcpy(str2, "52310");
    if (strcspn(str1, str2) != my_strcspn(str1, str2))
        errors ++;

    //Символы в искаемой строке повторяются
    strcpy(str1, "0123456789");
    strcpy(str2, "353001122");
    if (strcspn(str1, str2) != my_strcspn(str1, str2))
        errors ++;    

   //Один символ
    strcpy(str1, "0123456789");
    strcpy(str2, "3530022");
    if (strcspn(str1, str2) != my_strcspn(str1, str2))
        errors ++;              

   //Искаемая строка - ноль
    strcpy(str1, "0123456789");
    strcpy(str2, "\0");
    if (strcspn(str1, str2) != my_strcspn(str1, str2))
        errors ++;              

    printf("strcspn: %d\n", errors);
    errors = 0;


   //Искомый символ в начале
    strcpy(str1, "0123456789");
    chr = '0';
    if (strchr(str1, chr) != my_strchr(str1, chr))
        errors ++;


    //Искомый символ в конце
    strcpy(str1, "0123456789");
    chr = '9';
    if (strchr(str1, chr) != my_strchr(str1, chr))
        errors ++;   

    //Искомых символов несколько
    strcpy(str1, "01253456789");
    chr = '5';
    if (strchr(str1, chr) != my_strchr(str1, chr))
        errors ++;   
                   
    //Искомых символ - ноль
    strcpy(str1, "01253456789");
    chr = '\0';
    if (strchr(str1, chr) != my_strchr(str1, chr))
        errors ++;   

    printf("strchr: %d\n", errors);
    errors = 0;  



    //Искомый символ в начале
    strcpy(str1, "0123456789");
    chr = '0';
    if (strrchr(str1, chr) != my_strrchr(str1, chr))
        errors ++;


    //Искомый символ в конце
    strcpy(str1, "0123456789");
    chr = '9';
    if (strrchr(str1, chr) != my_strrchr(str1, chr))
        errors ++;   

    //Искомых символов несколько
    strcpy(str1, "01253456789");
    chr = '5';
    if (strrchr(str1, chr) != my_strrchr(str1, chr))
        errors ++;   
                   
    //Искомых символ - ноль
    strcpy(str1, "01253456789");
    chr = '\0';
    if (strrchr(str1, chr) != my_strrchr(str1, chr))
        errors ++;   

    printf("strrchr: %d\n", errors);
    errors = 0;  


    return 0;
}
