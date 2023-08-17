#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_prime(int n)
{
    if (n == 1 || n == 0)
        return 0;

    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

void fill_array(int size, int *arr)
{
    int pos = 0;
    int last_num = 0;
    while (pos < size)
    {
        last_num++;
        while (!is_prime(last_num))
            last_num++;
        arr[pos] = last_num;
        pos++;
    }
}

int extend_array(int size, int *arr, int *arr2, int num)
{
    int new_size = 0;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0)
        {
            new_size++;
        }
    }
    new_size += size;
    if (arr2 == NULL)
    {
        return new_size;
    }

    int pos = 0;
    for (int i = 0; i < size; i++)
    {
        arr2[pos] = arr[i];
        pos++;
        if (arr[i] % 2 == 0)
        {
            arr2[pos] = num;
            pos++;
        }
    }

    return new_size;
}

// int extend_array2(int size, int *arr, int *arr2, int num)
// {
//     // int new_size = size * 2;

//     int pos = 0;
//     for (int i = 0; i < size; i++)
//     {
//         arr2[pos] = arr[i];
//         pos++;
//         if (arr[i] % 2 == 0)
//         {
//             arr2[pos] = num;
//             pos++;
//         }
//     }

//     for (int i = 0; i < pos; i++)
//     {
//         printf("%d ", arr2[i]);
//     }

//     return pos;
// }

/*
int main(void)
{
    int *arr = malloc(sizeof(int) * 20);
    int *arr2 = malloc(sizeof(int) * 50);

    for (int i = 0; i < 20; i++)
    {
        arr[i] = i + 1;
    }

    int len = extend_array(20, arr, arr2, 555);
    fill_array(20, arr);

    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr2[i]);
    }

    printf("\n");

    return 0;
}*/