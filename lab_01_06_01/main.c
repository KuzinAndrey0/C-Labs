/*
Позитивные тесты:

Ввод:   1 2
        5 5
        4 4

Вывод:  0.5


Ввод:   3 3
        7 5
        10 10

Вывод:  7

Негативные тесты:

Ввод:   a 0

*/


#include <stdio.h>
#include <math.h>

double get_square(double x1, double y1, double x2, double y2, double x3, double y3)
{
    double s = (double)0.5 * fabs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
    return s;
}


int main(void)
{
    int num;
    double x1, y1, x2, y2, x3, y3;
    double s;

    printf("Введите координаты вершин: ");
    num = scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);

    if (num == 6)
    {
        s = get_square(x1, y1, x2, y2, x3, y3);
    }    
    else
    {
        printf("Неверные данные\n");
        return 100;        
    }
    
    if (s > 0)
    {
        printf("Площадь треугольника: %f\n", s);
    }
    else
    {
        printf("Неверная фигура.\n");
        return 100;
    }

    return 0;
}
