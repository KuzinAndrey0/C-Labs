#include "../inc/matrix_funcs.h"
#include "../inc/matrix_math.h"
#include <check.h>
#include <stdlib.h>

#define EPS 1.0e-7
//    ck_assert_double_eq_tol(avg, 0.0, EPS);

// Функция тестирования какой-либо задачи.
START_TEST(square_matrix)
{
    double **arr1 = allocate_matrix(5, 5);
    double **arr2 = allocate_matrix(5, 5);
    double **arr3 = allocate_matrix(5, 5);

    double arr4[] = {215, 230,  245,  260,  275,  490,  530,  570,  610,  650,  765,  830, 895,
                     960, 1025, 1040, 1130, 1220, 1310, 1400, 1315, 1430, 1545, 1660, 1775};
    int height[] = {5, 5};
    int width[] = {5, 5};
    for (int i = 0; i < 25; i++)
    {
        arr1[0][i] = i + 1;
        arr2[0][i] = i + 1;
    }

    matrix_multiplication(arr1, arr2, &arr3, height, width);

    for (int i = 0; i < 25; i++)
    {
        ck_assert_double_eq_tol(arr3[0][i], arr4[i], EPS);
    }

    free_matrix(arr1);
    free_matrix(arr2);
    free_matrix(arr3);
}
END_TEST

START_TEST(small_matrix)
{
    double **arr1 = allocate_matrix(1, 1);
    double **arr2 = allocate_matrix(1, 1);
    double **arr3 = allocate_matrix(1, 1);
    int height[] = {1, 1};
    int width[] = {1, 1};
    arr1[0][0] = 4;
    arr2[0][0] = 3.3;

    matrix_multiplication(arr1, arr2, &arr3, height, width);

    ck_assert_double_eq_tol(arr3[0][0], 4 * 3.3, EPS);

    free_matrix(arr1);
    free_matrix(arr2);
    free_matrix(arr3);
}
END_TEST

START_TEST(rect_matrix)
{
    double **arr1 = allocate_matrix(5, 2);
    double **arr2 = allocate_matrix(2, 5);
    double **arr3 = allocate_matrix(5, 5);
    double arr4[] = {13, 16, 19, 22, 25, 27,  34,  41, 48, 55,  41,  52, 63,
                     74, 85, 55, 70, 85, 100, 115, 69, 88, 107, 126, 145};

    int height[] = {5, 2};
    int width[] = {2, 5};
    for (int i = 0; i < 10; i++)
    {
        arr1[0][i] = i + 1;
        arr2[0][i] = i + 1;
    }

    matrix_multiplication(arr1, arr2, &arr3, height, width);

    for (int i = 0; i < 10; i++)
    {
        ck_assert_double_eq_tol(arr3[0][i], arr4[i], EPS);
    }

    free_matrix(arr1);
    free_matrix(arr2);
    free_matrix(arr3);
}
END_TEST

END_TEST

// Функция создания набора тестов.
Suite *suite_create_matrix_multiplication(void)
{
    Suite *suite = suite_create("matrix_multiplication");
    // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
    TCase *tcase_core = tcase_create("Positives");

    // Добавление теста в группу тестов.
    tcase_add_test(tcase_core, square_matrix);
    tcase_add_test(tcase_core, small_matrix);
    tcase_add_test(tcase_core, rect_matrix);

    // Добавление теста в тестовый набор.
    suite_add_tcase(suite, tcase_core);

    return suite;
}

int check_matrix_multiplication(void)
{
    int failed_count;
    Suite *suite = suite_create_matrix_multiplication();
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