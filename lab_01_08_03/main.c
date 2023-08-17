/*
Позитивные тесты:

Ввод:   10

Вывод:  00000000000000000000000000000101


Ввод:   2

Вывод:  00000000000000000000000000000001

Негативные тесты:

Ввод:   a

*/

#include <stdio.h>
#include <math.h>

void print_bin(unsigned long int num)
{
    unsigned long int i = (unsigned long int)pow(2, 31);
    
    while (i)
    {
        printf("%d", (num & i) > 0);
        i >>= 1;
    }
}


int main(void)
{
    unsigned long int x, x2;
    int num;
    unsigned long int mask = 2863311530; //0b10101010101010101010101010101010

    printf("Введите число: ");
    num = scanf("%lu", &x);

    if (num != 1)
    {
        printf("Error: Неверные данные\n");
        return 100;
    }

    x2 = ((x << 1) & mask) | ((x >> 1) & (mask >> 1));

    // printf("Binary: ");  
    // print_bin(x);
    // printf("\n");  

    printf("Result: ");    
    print_bin(x2);   
    printf("\n");

    return 0;
}
