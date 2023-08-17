/*
Позитивные тесты:

Ввод:   31 15

Вывод:  2
        1


Ввод:   45 15

Вывод:  3
        0

Ввод:   1 15

Вывод:  0
        1

Негативные тесты:

Ввод:   15 0

Ввод:   a 15

Ввод:   -1 2

*/


#include <stdio.h>
#include <math.h>

int get_whole(int num1, int num2)
{
    int i = 0;
    while (num1 >= 0)
    {
        num1 -= num2;
        i ++;
    }
    i --;
    return i;
}

int get_frac(int num1, int num2)
{
    int whole = get_whole(num1, num2);
    int frac = num1 - whole * num2;

    return frac;
}

int main(void)
{
    int a, d, num, frac, q;

    printf("Введите a и d: ");
    num = scanf("%d%d", &a, &d);

    if (num == 2 && a > 0 && d > 0)
    {
        q = get_whole(a, d);
        frac = get_frac(a, d);

        printf("Значение частного: %d\n", q);
        printf("Остаток частного: %d\n", frac);
    }
    else
    {
        printf("Неверные данные\n");
        return 100;
    }



    return 0;
}
