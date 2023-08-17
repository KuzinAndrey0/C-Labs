/*
Позитивные тесты:

Ввод:   3 4
        90

Вывод:  6


Ввод:   5 7
        80

Вывод:  17.2341
*/


#include <stdio.h>
#define M_PI           3.14159265358979323846
#include <math.h>


int main(void)
{
    float a, b, d, sq;
    float rad;

    printf("Введите стороны a и b треугольника: ");
    scanf("%f%f", &a, &b);

    printf("Введите угол между сторонами a и b треугольника: ");
    scanf("%f", &d);

    rad = d * M_PI / 180.0;
    
    sq = 1.0 / 2.0 * a * b * sin(rad);
    printf("Площать треугольника: %f\n", sq);

    return 0;
}
