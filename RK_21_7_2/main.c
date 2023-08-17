#include <stdio.h>
#include <stdlib.h>

#define RETURN_SUCCESS 0
#define RETURN_ERROR_COUNT 100
#define RETURN_ERROR_ARRAY 101

#define ARRAY_LENGTH 11


void insert_element(int array[], int length, int num, int pos) // Вставляет элемент в заданную позицию массива
{
    for(int i = length; i > pos; i --)
    {
        array[i] = array[i - 1];
    }

    array[pos] = num;
}

int get_array_max(int array[], int length) // Возвращает максимальный элемент массива
{
    int max = array[0];

    for (int i = 1; i < length; i ++)
    {
        max = max < array[i] ? array[i] : max;
    }

    return max;
}

int get_array_min(int array[], int length) // Возвращает минимальный элемент массива
{
    int min = array[0];

    for (int i = 1; i < length; i ++)
    {
        min = min > array[i] ? array[i] : min;
    }

    return min;
}

int main(void)
{
    int length, count; 
    int arr[ARRAY_LENGTH];
    int min_element, max_element, sum, insert_pos;

    printf("Введите размер массива: ");

    count = scanf("%d", &length);

    if (count != 1 || length < 1 || length > 10) // Проверка на корректный ввод
    {
        printf("Неверные данные\n");
        return RETURN_ERROR_COUNT;
    }

    for (int i = 0; i < length; i ++) // Заполнить массив
    {
        count = scanf("%d", &arr[i]); 
        if (count != 1) // Проверка на корректный ввод
        {
            printf("Неверные данные\n");
            return RETURN_ERROR_ARRAY;           
        }

    }

    min_element = get_array_min(arr, length); // Минимальный элемент массива
    max_element = get_array_max(arr, length); // Максимальный элемент массива

    sum = min_element + max_element; // Сумма макс. и мин. элементов 

    insert_pos = (sum % 2) == 0 ? 0 : length; // Определить позицию для вставки - начало если четная, конец если нечетная
    insert_element(arr, length, sum, insert_pos); // Вставить элемент в массив в нужную позицию
    length ++; //Увеличить размер массива

    // Вывод полученного массива
    printf("Новый массив: ");
    for (int i = 0; i < length; i ++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return RETURN_SUCCESS; // Успешное завершение программы

}