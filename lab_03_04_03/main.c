#include <stdio.h>

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

void print_matrix_funny(int arr[][ARRAY_LENGTH], int length)
{
    for (int i = 0; i < length; i ++)
    {
        for (int j = 0; j < length; j ++)
        {
            if ((j >= i && j >= (length - 1 - i)) || ((length - 1 - j) >= i && (length - 1 - j) >= (length - 1 - i)))
                printf("x ");
            else
                printf("%d ", arr[i][j]);     
        }
        printf("\n");
    }
}

void swap_rows_funny(int arr[][ARRAY_LENGTH], int length)
{
    for (int i = 0; i < length; i ++)
    {
        for (int j = 0; j < (length / 2); j ++)
        {
            if ((j >= i && j >= (length - 1 - i)) || ((length - 1 - j) >= i && (length - 1 - j) >= (length - 1 - i)))
            {
                int temp = arr[i][j];
                arr[i][j] = arr[i][length - 1 - j];
                arr[i][length - 1 - j] = temp;
            }      
        }
    }
}

int main(void)
{
    int arr[ARRAY_LENGTH][ARRAY_LENGTH];
    int length;
    int num;
    int width, height;

    //Ввод размерностей
    printf("Введите стороны матрицы: ");
    num = scanf("%d %d", &width, &height);

    //Проверка на корректные размерности матрицы
    if (num != 2 || width > 10 || width < 1 || width != height)
    {
        return 100;
    }

    length = width;
    
    //Ввод матрицы
    for (int i = 0; i < length; i ++)
    {
        printf("Введите строку массива:\n");
        for (int j = 0; j < length; j ++)
        {
            num = scanf("%d", &arr[i][j]);
            if (num != 1)
            {
                return 100;
            }
        }
    }

    swap_rows_funny(arr, length);

    printf("Новая матрица:\n");
    
    print_matrix(arr, length, length);


    return 0;
}