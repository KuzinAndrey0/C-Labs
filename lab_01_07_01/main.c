/*
Позитивные тесты:

Ввод:   10 0.01

Вывод:  -0.544127
        -0.544021
        0.000105679
        0.000194255

Негативные тесты:

Ввод:   10 0

Ввод:   a 0.1

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double get_func_val(double x, double eps)
{
    double xx = x;
    double cur_val;
    double fac = 1;
    double s = 0;
    int cur_num = 1;
    int sgn = 1;   
    do
    {
        cur_val = xx / fac;
        fac *= cur_num + 1;
        fac *= cur_num + 2;

        cur_num += 2;
        xx *= x * x;

        s += cur_val * sgn;

        sgn *= -1;
    }
    while (fabs(cur_val) > eps);

    return s;
}


int main(void)
{
    double x, eps, f, d, g, s; 
    int num;


    printf("Введите x и точность eps: ");
    num = scanf("%lf %lf", &x, &eps);

    if (num != 2 || eps <= 0.0 || eps > 1.0)
    {
        printf("Неверные данные\n");
        return 100;
    }

    s = get_func_val(x, eps);

    f = sin(x);

    d = fabs(f - s);
    g = d / fabs(f);

    printf("s(x): %lf\nf(x): %lf\nАбсолютная погрешность: %lf\nОтносительная погрешность: %lf\n", s, f, d, g);


    return 0;
}
