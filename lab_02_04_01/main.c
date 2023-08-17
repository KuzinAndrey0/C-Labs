 #include <stdio.h>
 #include <math.h>

 #define ARRAY_MAX 10



void insert_sort(int arr[ARRAY_MAX], int len)
{
    int temp;
    for (int i = 1; i < len; i ++)     
    {
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; j --)
        {
            temp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = temp;
        }
    }
}


int main(void)
{
    int arr[ARRAY_MAX];
    int exit_code = 0;
    int len = 0;
    int old_num = 0;
    int val;
    int stop_input = 0;


    int num = 0;

    while (exit_code == 0 && stop_input == 0)
    {
        old_num = num;
        num += scanf("%d", &val);

        if (len == 10 && num - old_num != 0)
        {
            exit_code = 100;
        }
        else if (num - old_num != 0)
        {
            arr[len] = val;
        }
        else
        {
            stop_input = 1;
        }
        len ++;
    }
    len --;
    if (len == 0)
    {
        return 100;
    }


    insert_sort(arr, len);
    for (int i = 0; i < len; i ++)
    {
        printf("%d ", arr[i]);
    }    

    return exit_code;
}