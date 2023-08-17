 #include <stdio.h>
 #include <math.h>

 #define ARRAY_MAX 10

int get_sum(int *first, int *last)
{
    int sum = 1;
    for (int *i = first; i < last; i ++)
    {
        sum *= *i;
    }
    return sum;
}

int main(void)
{
    int arr[ARRAY_MAX], add_num;
    int *p_start, *p_end, *p_cur;
    int num, n, old_num;
    int sum = 0;
    p_start = arr;
    p_end = arr;
    p_cur = arr;

    num = scanf("%d", &n);

    //Длинна массива подходит условию
    if (!(num == 1 && n > 0 && n < 11))
    {
        return 100;
    }    

    num = 0;
    for (int i = 0; i < n; i += 1)
    {
        old_num = num;
        num += scanf("%d", &add_num);
        if (num - old_num != 0)
        {
            *p_end = add_num;
            p_end += 1;
        }
    }
    if (p_start == p_end || n != num)
    {
        return 100;
    }

    do
    {
        p_cur ++;        
        sum += get_sum(p_start, p_cur);
    }
    while (*(p_cur - 1) > 0 && p_cur < p_end);

    printf("%d\n", sum);

    return 0;
}