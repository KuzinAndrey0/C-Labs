#include <stdlib.h>
// Подключаем заголовочный файл библиотеки.
#include "../inc/array_funcs.h"
#include <check.h>

// Функция тестирования какой-либо задачи.
START_TEST(first_bigger)
{
    int a = 10;
    int b = 5;
    void *aa = &a;
    void *bb = &b;
    int rc;

    rc = cmpfunc(aa, bb);
    ck_assert_int_eq(rc, 5);
}
END_TEST

START_TEST(first_smaller)
{
    int a = 5;
    int b = 10;
    void *aa = &a;
    void *bb = &b;
    int rc;

    rc = cmpfunc(aa, bb);
    ck_assert_int_eq(rc, -5);
}
END_TEST

START_TEST(equal)
{
    int a = 5;
    int b = 5;
    void *aa = &a;
    void *bb = &b;
    int rc;

    rc = cmpfunc(aa, bb);
    ck_assert_int_eq(rc, 0);
}
END_TEST

// Функция создания набора тестов.
Suite *suite_create_cmpfunc(void)
{
    Suite *suite = suite_create("cmpfunc");
    // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
    TCase *tcase_core = tcase_create("Positives");

    // Добавление теста в группу тестов.
    tcase_add_test(tcase_core, first_bigger);
    tcase_add_test(tcase_core, first_smaller);
    tcase_add_test(tcase_core, equal);

    // Добавление теста в тестовый набор.
    suite_add_tcase(suite, tcase_core);

    return suite;
}

int check_cmpfunc(void)
{
    int failed_count;
    Suite *suite = suite_create_cmpfunc();
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