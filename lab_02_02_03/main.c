 #include <stdio.h>
 #include <math.h>

 #define ARRAY_MAX 10

int is_armstrong(int num)
{
    int original = num;
    int digits = 0;
    int test_num = 0;

    while (num > 0)
    {
        digits ++;
        num /= 10;
    }
    num = original;

    for (int i = 0; i < digits; i ++)
    {
        test_num += (int)pow(num % 10, digits);
        num /= 10;
    }

    return (test_num == original && original != 0);
}

int main(void)
{
    int num, n;
    int arr[ARRAY_MAX], new_arr[ARRAY_MAX];
    int new_arr_pos = 0;
    int is_arm;

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

    for (int i = 0; i < n; i += 1)
    {
        is_arm = is_armstrong(arr[i]);
        if (is_arm)
        {
            new_arr[new_arr_pos] = arr[i];
            new_arr_pos ++;
        }
    }
    if (new_arr_pos == 0)
    {
        return 100;
    }
    else
    {
        for (int i = 0; i < new_arr_pos; i ++)
        {
            printf("%d ", new_arr[i]);
        }
        return 0;
    }
}