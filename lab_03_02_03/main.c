#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LENGTH 10

void print_matrix(int arr[][ARRAY_LENGTH], int width, int height)
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}


void remove_row(int arr[][ARRAY_LENGTH], int width, int height, int row)
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = row; j < (width - 1); j ++)
        {
            arr[i][j] = arr[i][j + 1];
        }
    }
}

int has_digit(int num, int digit)
{
    num = abs(num);
    if (num == abs(digit))
    {
        return 1;
    }
    while (num > 0)
    {
        if (num % 10 == digit)
        {
            return 1;
        }
        num = num / 10;
    }
    return 0;
}
int main(void)
{
    int arr[ARRAY_LENGTH][ARRAY_LENGTH];
    int width, height;
    int num;
    int digit_to_delete;    

    //Ввод размерностей
    printf("Введите ширину и высоту матрицы: ");
    num = scanf("%d %d", &height, &width);

    //Проверка на корректные размерности матрицы
    if (num != 2 || width > 10 || width < 1 || height > 10 || height < 1)
    {
        return 100;
    }
    
    //Ввод матрицы
    for (int i = 0; i < height; i ++)
    {
        printf("Введите строку массива:\n");
        for (int j = 0; j < width; j ++)
        {
            num = scanf("%d", &arr[i][j]);
            if (num != 1)
            {
                return 100;
            }
        }
    }

    //Ввод цифры
    printf("Введите цифру для удаления: ");
    num = scanf("%d", &digit_to_delete);

    //Проверка на корректную цифру
    if (num != 1 || digit_to_delete > 9 || digit_to_delete < 0)
    {
        return 100;
    }

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            if (has_digit(arr[i][j], digit_to_delete))
            {
                remove_row(arr, width, height, j);               
                width --;
                j --;              
            }
        }
    }

    if (width == 0)
    {
        return 100;
    }
    printf("Новая матрица:\n");
    print_matrix(arr, width, height);


    return 0;
}