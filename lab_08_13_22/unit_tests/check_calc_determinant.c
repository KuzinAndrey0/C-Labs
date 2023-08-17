#include "../inc/matrix_funcs.h"
#include "../inc/matrix_math.h"
#include <check.h>
#include <stdlib.h>

#define EPS 1.0e-7
//    ck_assert_double_eq_tol(avg, 0.0, EPS);

// Функция тестирования какой-либо задачи.
START_TEST(one)
{
    double **arr1 = allocate_matrix(1, 1);
    double det;

    arr1[0][0] = 5;

    calc_determinant(arr1, 1, &det);

    ck_assert_double_eq_tol(det, 5, EPS);

    free_matrix(arr1);
}
END_TEST

START_TEST(two)
{
    double **arr1 = allocate_matrix(2, 2);
    double det;

    for (int i = 0; i < 4; i++)
    {
        arr1[0][i] = i + 1;
    }

    calc_determinant(arr1, 2, &det);

    ck_assert_double_eq_tol(det, -2, EPS);

    free_matrix(arr1);
}
END_TEST

START_TEST(three)
{
    double **arr1 = allocate_matrix(3, 3);
    double det;

    for (int i = 0; i < 9; i++)
    {
        arr1[0][i] = i + 1;
    }

    calc_determinant(arr1, 3, &det);

    ck_assert_double_eq_tol(det, 0, EPS);

    free_matrix(arr1);
}

START_TEST(four)
{
    double **arr1 = allocate_matrix(4, 4);
    double det;

    for (int i = 0; i < 16; i++)
    {
        arr1[0][i] = i + 1;
    }

    calc_determinant(arr1, 4, &det);

    ck_assert_double_eq_tol(det, 0, EPS);

    free_matrix(arr1);
}
END_TEST

// Функция создания набора тестов.
Suite *suite_create_calc_determinant(void)
{
    Suite *suite = suite_create("calc_determinant");
    // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
    TCase *tcase_core = tcase_create("Positives");

    // Добавление теста в группу тестов.
    tcase_add_test(tcase_core, one);
    tcase_add_test(tcase_core, two);
    tcase_add_test(tcase_core, three);
    tcase_add_test(tcase_core, four);

    // Добавление теста в тестовый набор.
    suite_add_tcase(suite, tcase_core);

    return suite;
}

int check_calc_determinant(void)
{
    int failed_count;
    Suite *suite = suite_create_calc_determinant();
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