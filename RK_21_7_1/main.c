#include <stdio.h>
#include <stdlib.h>

#define RETURN_SUCCESS 0
#define RETURN_ERROR 100


int reverse_number(int num) // Отражает число
{
    int new_num = 0; //Новое число
    int sign = num == 0 ? 0 : num / abs(num); // Знак числа

    if (sign == 0) // Если число - 0, вернуть его без изменений
    {
        return 0;
    }

    num = abs(num);

    while (num > 0) // Получать цифры, пока не закончатся
    {
        new_num *= 10;
        new_num += num % 10;

        num /= 10;
    }    

    return sign * new_num;
}

int replace_even(int num) // Заменяет четные цифры числа на 1
{
    int sign = num == 0 ? 0 : num / abs(num); // Знак числа
    int new_num = 0; // Новое число
    int digit; // Цифра числа

    if (sign == 0) // Если число - 0, вернуть его без изменений
    {
        return 0;
    }

    num = abs(num);

    while (num > 0)
    {
        digit = ((num % 10) % 2) == 0 ? 1 : num % 10; // Получить цифру числа, заменить на 1 если оно четное
        num /= 10;
        new_num *= 10;
        new_num += digit;
    }

    return (sign * reverse_number(new_num));

}

int main(void)
{
    int count, num;

    printf("Введите число: ");

    count = scanf("%d", &num);

    if (count != 1 || num < 1) // Проверка на корректный ввод
    {
        printf("Неверные данные\n");
        return RETURN_ERROR;
    }

    printf("Полученное число: %d\n", replace_even(num)); // Вывод полученного числа

    return RETURN_SUCCESS; // Успешное завершение

}