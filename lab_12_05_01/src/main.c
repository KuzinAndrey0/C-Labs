//#include "../inc/arr_lib_dyn_1.h"
#include "../inc/arr_lib_dyn_2.h"
#include "../inc/arr_lib_stat.h"
#include "../inc/my_defines.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*fn_key_t)(const int *, const int *, int **, int **);

int main(int argc, char **argv)
{

    if (argc < 3)
    {
        return RETURN_NOT_ENOUGH_ARGUMENTS;
    }

    FILE *f_in, *f_out;
    size_t count = 0;
    int correct;
    int *arr, *arr2;
    int filter_enabled = argc == 4 && strcmp(argv[3], "f") == 0;

    if (!filter_enabled && argc >= 4)
        return RETURN_WRONG_ARGUMENTS;
    if (argc > 4)
        return RETURN_WRONG_ARGUMENTS;

    f_in = fopen(argv[1], "r");
    if (f_in == NULL)
    {
        return RETURN_NO_FILE;
    }

    int rc = get_num_count(f_in, &count, &arr);
    if (rc != RETURN_SUCCESS)
        return rc;

    fclose(f_in);

    if (filter_enabled)
    {

        void *hlib = dlopen("./libs/arr_lib_dyn_1.so", RTLD_NOW);

        if (!hlib)
        {
            printf("%s", dlerror());

            free(arr);
            return RETURN_MEMORY_ERROR;
        }

        fn_key_t key_func;
        key_func = (fn_key_t)dlsym(hlib, "key");

        int *arr1_end = arr + count;
        int *arr2_end;

        count = key_func(arr, arr1_end, NULL, NULL);

        arr2 = malloc(count * sizeof(int));

        correct = key_func(arr, arr1_end, &arr2, &arr2_end);

        dlclose(hlib);

        if (correct != 0)
        {
            free(arr);
            return RETURN_MEMORY_ERROR;
        }

        count = arr2_end - arr2;

        mysort(arr2, count, sizeof(int), cmpfunc);

        f_out = fopen(argv[2], "w");
        if (f_out == NULL)
        {
            free(arr);
            free(arr2);
            return RETURN_NO_FILE;
        }
        for (size_t i = 0; i < count; i++)
        {
            fprintf(f_out, "%d ", *(arr2 + i));
        }

        free(arr2);
    }
    else
    {
        mysort(arr, count, sizeof(int), cmpfunc);

        f_out = fopen(argv[2], "w");
        if (f_out == NULL)
        {
            free(arr2);
            return RETURN_NO_FILE;
        }

        print_to_file(f_out, arr, count);
    }

    fclose(f_out);
    free(arr);
    return RETURN_SUCCESS;
}