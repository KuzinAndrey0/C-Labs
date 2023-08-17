 #include <stdio.h>
 #include <math.h>

 #define ARRAY_MAX 20


int reverse_num(int num)
{
    int new_num = 0;

    while (num > 0)
    {
        new_num *= 10;
        new_num += num % 10;
        num /= 10;
    }

    return new_num;
}

int main(void)
{
    int num, n;
    int arr[ARRAY_MAX];

    num = scanf("%d", &n);

    //Длинна массива подходит условию
    if (!(num == 1 && n > 0 && n < 11))
    {
        return 100;
    }

    num = 0;
    for (int i = 0; i < n; i += 1)
    {
        num += scanf("%d", &arr[i]);
    }

    //Содержимое массива подходит условию
    if (num != n)
    {
        return 100;
    }

    for (int i = 0; i < n; i ++)
    {
        if (arr[i] > 0)
        {
            for (int j = n; j > i; j --)
            {
                arr[j] = arr[j - 1];
            }
            n ++;
            arr[i + 1] = reverse_num(arr[i]);
            i ++;           
        }
    }
    for (int i = 0; i < n; i ++)
    {
        printf("%d ", arr[i]);
    }    
}