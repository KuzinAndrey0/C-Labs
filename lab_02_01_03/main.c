 #include <stdio.h>
 #include <math.h>

 #define ARRAY_MAX 10

int has_positive(const int arr[ARRAY_MAX], size_t len)
{
    for (size_t i = 0; i < len; i ++)
    {
        if (arr[i] > 0)
        {
            return 1;
        }
    }
    return 0;
}

double geometric_mean(const int arr[ARRAY_MAX], size_t len)
{
    int nums = 1;
    double mean;
    int poses = 0;
   
    for (size_t i = 0; i < len; i ++)
    {
        if (arr[i] > 0)
        {
            nums *= arr[i];
            poses ++;
        }
    }

    double power = (double)1 / poses;
    mean = pow(nums, power);    
    return mean;
}

int main(void)
{
    int num, n;
    int arr[ARRAY_MAX];
    int has_pos;
    double mean;

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

    has_pos = has_positive(arr, n);

    //Содержимое массива подходит условию
    if (num != n || has_pos == 0)
    {
        return 100;
    }

    mean = geometric_mean(arr, n);
    printf("%f\n", mean);
    return 0;
}