/*
Позитивные тесты:

Ввод:   10
        2
        15

Вывод:  375


Ввод:   15
        30
        25

Вывод:  9750
*/

#include <stdio.h>
#include <math.h>


int main(void)
{
    float v, a, t;
    float s;

    printf("Введите начальную скорость: ");
    scanf("%f", &v);

    printf("Введите ускорение: ");
    scanf("%f", &a);

    printf("Введите время движения: ");
    scanf("%f", &t);   

    s = v * t + (a * t * t / 2);

    printf("Перемещение объекта: %f\n", s);

    return 0;
}
