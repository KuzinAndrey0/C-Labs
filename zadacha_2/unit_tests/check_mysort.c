#include <stdlib.h>
// Подключаем заголовочный файл библиотеки.
#include "../inc/arr_lib_dyn_2.h"

#include <check.h>

int cmpfunc_float(const void *a, const void *b)
{
    return (*(double *)a - *(double *)b);
}

int cmpfunc_char(const void *a, const void *b)
{
    return (*(char *)a - *(char *)b);
}

// Функция тестирования какой-либо задачи.
START_TEST(unsorted_array)
{
    int input[5] = {1, 3, 2, 5, 4};
    int output[5] = {1, 2, 3, 4, 5};

    // void mysort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))

    mysort(input, 5, sizeof(int), cmpfunc);
    for (size_t i = 0; i < 5; i++)
        ck_assert_int_eq(input[i], output[i]);
    // ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(reverse_array)
{
    int input[5] = {5, 4, 3, 2, 1};
    int output[5] = {1, 2, 3, 4, 5};

    // void mysort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))

    mysort(input, 5, sizeof(int), cmpfunc);
    for (size_t i = 0; i < 5; i++)
        ck_assert_int_eq(input[i], output[i]);
    // ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(sorted_array)
{
    int input[5] = {1, 2, 3, 4, 5};
    int output[5] = {1, 2, 3, 4, 5};

    // void mysort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))

    mysort(input, 5, sizeof(int), cmpfunc);
    for (size_t i = 0; i < 5; i++)
        ck_assert_int_eq(input[i], output[i]);
    // ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(double_sort)
{
    double input[5] = {1, 20, 3, 4, 5};
    double output[5] = {1, 3, 4, 5, 20};

    mysort(input, 5, sizeof(double), cmpfunc_float);

    for (size_t i = 0; i < 5; i++)
        ck_assert_double_eq(input[i], output[i]);
}
END_TEST

START_TEST(char_sort)
{
    char input[5] = {'B', 'D', 'A', 'E', 'C'};
    char output[5] = {'A', 'B', 'C', 'D', 'E'};

    mysort(input, 5, sizeof(char), cmpfunc_char);

    for (size_t i = 0; i < 5; i++)
        ck_assert_double_eq(input[i], output[i]);
}
END_TEST

// Функция создания набора тестов.
Suite *suite_create_mysort(void)
{
    Suite *suite = suite_create("mysort");
    // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
    TCase *tcase_pos = tcase_create("Positives");

    // Добавление теста в группу тестов.
    tcase_add_test(tcase_pos, unsorted_array);
    tcase_add_test(tcase_pos, reverse_array);
    tcase_add_test(tcase_pos, sorted_array);
    tcase_add_test(tcase_pos, double_sort);
    tcase_add_test(tcase_pos, char_sort);
    // Добавление теста в тестовый набор.
    suite_add_tcase(suite, tcase_pos);

    // TCase *tcase_neg = tcase_create("Negatives");

    // // Добавление теста в группу тестов.
    // tcase_add_test(tcase_neg, incorrect_values);

    // // Добавление теста в тестовый набор.
    // suite_add_tcase(suite, tcase_neg);

    return suite;
}

int check_mysort(void)
{
    int failed_count;
    Suite *suite = suite_create_mysort();
    SRunner *suite_runner = srunner_create(suite);

    srunner_run_all(suite_runner, CK_NORMAL);
    // Получаем количество проваленных тестов.
    failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);

    if (failed_count != 0)
    {
        // Сигнализируем о том, что тестирование прошло неудачно.
        return 1;
    }

    return 0;
}