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

void sort_by_min_elem(int arr[][ARRAY_LENGTH], int width, int height)
{
    int mins[height];

    for (int i = 0; i < height; i ++)
    {
        mins[i] = arr[i][0];

        for (int j = 0; j < width; j ++)
        {
            mins[i] = mins[i] > arr[i][j] ? arr[i][j] : mins[i];
        }
    }


    int temp;
    int temp_arr[width];

    for (int i = 1; i < height; i ++)     
    {
        for (int j = i; j > 0 && mins[j - 1] < mins[j]; j --)
        {
            temp = mins[j - 1];          
            for (int k = 0; k < width; k ++)
            {
                temp_arr[k] = arr[j - 1][k];      
            }

            mins[j - 1] = mins[j];
            for (int k = 0; k < width; k ++)
            {
                arr[j - 1][k] = arr[j][k];
            }
            
            mins[j] = temp;
            for (int k = 0; k < width; k ++)
            {
                arr[j][k] = temp_arr[k];
            }
        }
    }
}

int main(void)
{
    int arr[ARRAY_LENGTH][ARRAY_LENGTH];
    int width, height;
    int num;

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

    sort_by_min_elem(arr, width, height);

    printf("Новая матрица:\n");
    print_matrix(arr, width, height);


    return 0;
}