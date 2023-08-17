/*
Позитивные тесты:

Ввод:   2
        3
        4
        5
        -1

Вывод:  0.002876

Негативные тесты:

Ввод:   a

*/

#include <stdio.h>
#include <math.h>

void print_func(double f)
{
    double g = exp(1 / f);

    printf("Значение функции: %lf\n", g);
}

int main(void)
{
    double n, x, f;
    int num;
    n = 0;
    f = 1;

    printf("Введите элемент: ");
    num = scanf("%lf", &x);

    while (num == 1 && x >= 0) 
    {
        n += 1;
        f *= x + n;
        printf("Введите элемент: ");
        num = scanf("%lf", &x);
    }
    if (num != 1 || n <= 0)
    {
        printf("Error: Неверные данные\n");        
        return 100;
    }
    else
    {
        print_func(f);
        return 0;
    }
}
