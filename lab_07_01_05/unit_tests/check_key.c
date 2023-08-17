#include <stdlib.h>
// Подключаем заголовочный файл библиотеки.
#include "../inc/array_funcs.h"

#include <check.h>

// Функция тестирования какой-либо задачи.
START_TEST(correct_values)
{
    int a[5] = {5, 4, 3, 2, 1};
    int b[5];
    int *b_p = b;

    int *aa = a + 5;
    int *bb = b + 5;

    int rc;

    rc = key(a, aa, &b_p, &bb);
    ck_assert_int_eq(rc, 0);
    free(b_p);
}
END_TEST

START_TEST(incorrect_values)
{
    int a[5] = {5, 4, 3, 2, 1};
    int b[5];
    int *b_p = b;

    int *aa = a - 1;
    int *bb = b + 5;

    int rc;

    rc = key(a, aa, &b_p, &bb);
    ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(memory_error)
{
    int a[5] = {5, 4, 3, 2, 1};
    int b[5];
    int *b_p = b;

    int *aa = a - 1;
    int *bb = a - 1;

    int rc;

    rc = key(a, aa, &b_p, &bb);
    ck_assert_int_eq(rc, 1);
}

// Функция создания набора тестов.
Suite *suite_create_key(void)
{
    Suite *suite = suite_create("key");
    // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
    TCase *tcase_pos = tcase_create("Positives");

    // Добавление теста в группу тестов.
    tcase_add_test(tcase_pos, correct_values);

    // Добавление теста в тестовый набор.
    suite_add_tcase(suite, tcase_pos);

    TCase *tcase_neg = tcase_create("Negatives");

    // Добавление теста в группу тестов.
    tcase_add_test(tcase_neg, incorrect_values);
    tcase_add_test(tcase_neg, memory_error);

    // Добавление теста в тестовый набор.
    suite_add_tcase(suite, tcase_neg);

    return suite;
}

int check_key(void)
{
    int failed_count;
    Suite *suite = suite_create_key();
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