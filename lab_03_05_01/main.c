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

int big_digit_sum(int num)
{
    num = abs(num);
    int sum = 0;
    while (num > 0)
    {
        sum += num % 10;
        num /= 10;
    }

    return sum > 10 ? 1 : 0;
}

int main(void)
{
    int arr[ARRAY_LENGTH][ARRAY_LENGTH];
    int width, height;
    int num;
    int nums[ARRAY_LENGTH * ARRAY_LENGTH][3];
    int cur_pos = 0;

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

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            if (big_digit_sum(arr[i][j]))
            {
                nums[cur_pos][0] = arr[i][j];
                nums[cur_pos][1] = i;
                nums[cur_pos][2] = j;
                cur_pos ++;
            }
        }
    }
    
    if (cur_pos == 0)
    {
        return 100;
    }

    for (int i = 0; i < 3; i ++)
    {
        int temp = nums[0][0];
        for (int j = 0; j < (cur_pos - 1); j ++)
        {
            nums[j][0] = nums[j + 1][0];
        }
        nums[cur_pos - 1][0] = temp;
    }

    for (int i = 0; i < cur_pos; i ++)
    {
        arr[nums[i][1]][nums[i][2]] = nums[i][0];
    }

    printf("Новая матрица:\n");
    
    print_matrix(arr, width, height);


    return 0;
} 
