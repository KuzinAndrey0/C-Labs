#include <stdio.h>

#define ARRAY_LENGTH 10

// -1 невозрастающая, 1 неубывающая, -2 - неизменная, 0 - не мотонная 
int get_sequence_type(const int arr[], const int len)
{
    int type = -2;

    if (len > 1)
    {
        for (int i = 0; i < len - 1; i ++)
        {
            if (arr[i + 1] < arr[i])
            {
                if (type == -2)
                {
                    type = -1;
                }
                if (type == 1)
                {
                    type = 0;
                }                                
            }
            if (arr[i + 1] > arr[i])
            {
                if (type == -2)
                {
                    type = 1;
                }
                if (type == -1)
                {
                    type = 0;
                }                                
            }
        }
    }
    else
    {
        type = 0;
    }
    return type;
}

int main(void)
{
    int arr[ARRAY_LENGTH][ARRAY_LENGTH];
    int arr_out[ARRAY_LENGTH];
    int width, height;
    int num;
    int add_num;

    printf("Введите ширину и высоту матрицы: ");
    num = scanf("%d %d", &height, &width);

    //Проверка на корректные размерности матрицы
    if (num != 2 || width > 10 || width < 1 || height > 10 || height < 1)
    {
        return 100;
    }

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
        add_num = get_sequence_type(arr[i], width) != 0 ? 1 : 0;
        arr_out[i] = add_num;
    }

    printf("Полученный массив: ");
    for (int i = 0; i < height; i ++)
    {
        printf("%d ", arr_out[i]);
    }
    return 0;
}