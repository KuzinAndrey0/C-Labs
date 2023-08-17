#include <stdio.h>

#define ARRAY_LENGTH 10

void print_matrix(int arr[][ARRAY_LENGTH], int width, int height)
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            printf("%2d ", arr[i][j]);
        }
        printf("\n");
    }
}

void funny_fill(int arr[ARRAY_LENGTH][ARRAY_LENGTH], int length)
{
    int top = 0;
    int left = 1;
    int bottom = length - 1;
    int right = length - 1;

    int dir = 0; //0 - вниз, 1 - вправо, 2 - вверх, 3 - влево
    int num = 1;
    int x = 0, y = 0;

    while (num <= (length * length))
    {
        arr[y][x] = num;
        num ++;

        if (dir == 0)
        {
            y ++;
            if (y == bottom)
            {
                bottom --;
                dir = 1;
            }
        }
        else if (dir == 1)
        {
            x ++;
            if (x == right)
            {
                right --;
                dir = 2;
            }
        }
        else if (dir == 2)
        {
            y --;
            if (y == top)
            {
                top ++;
                dir = 3;
            }
        }
        else if (dir == 3)
        {
            x --;
            if (x == left)
            {
                left ++;
                dir = 0;
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

 
    funny_fill(arr, length);

    printf("Новая матрица:\n");
    
    print_matrix(arr, length, length);


    return 0;
}