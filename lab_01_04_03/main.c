/*
Позитивные тесты:

Ввод:   345

Вывод:  60


Ввод:   678

Вывод:  336
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int num;
    int d1, d2, d3;
    int output;

    printf("Введите трехначное число: ");
    scanf("%d", &num);

    d1 = num / 100;
    d2 = num % 100 / 10;
    d3 = num % 10;

    output = abs(d1 * d2 * d3);

    printf("Произведение его цифр: %d\n", output);

    return 0;
}
