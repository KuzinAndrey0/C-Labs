#include "../inc/dynamic_data.h"
#include "../inc/my_defines.h"
#include "../inc/my_sprintf.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

// Функция тестирования какой-либо задачи.
START_TEST(s_one)
{
    int num1;
    int num2;

    char str1[50];
    char str2[50];

    num1 = my_snprintf(str1, 10, "%s", "test");
    num2 = snprintf(str2, 10, "%s", "test");

    ck_assert_int_eq(num1, num2);

    for (int i = 0; i < num1; i++)
    {
        ck_assert_int_eq(str1[i], str2[i]);
    }
}
END_TEST

// Функция тестирования какой-либо задачи.
START_TEST(s_row)
{
    int num1;
    int num2;

    char str1[50];
    char str2[50];

    num1 = my_snprintf(str1, 50, "%s%s%s", "test", "hello", "world");
    num2 = snprintf(str2, 50, "%s%s%s", "test", "hello", "world");

    ck_assert_int_eq(num1, num2);

    for (int i = 0; i < num1; i++)
    {
        ck_assert_int_eq(str1[i], str2[i]);
    }
}
END_TEST

// Функция тестирования какой-либо задачи.
START_TEST(s_middle)
{
    int num1;
    int num2;

    char str1[50];
    char str2[50];

    num1 = my_snprintf(str1, 50, "NOR%sMA%sL%sSTRING", "test", "hello", "world");
    num2 = snprintf(str2, 50, "NOR%sMA%sL%sSTRING", "test", "hello", "world");

    ck_assert_int_eq(num1, num2);

    for (int i = 0; i < num1; i++)
    {
        ck_assert_int_eq(str1[i], str2[i]);
    }
}
END_TEST

// Функция тестирования какой-либо задачи.
START_TEST(s_edges)
{
    int num1;
    int num2;

    char str1[50];
    char str2[50];

    num1 = my_snprintf(str1, 50, "%sNORMAL STRING%s", "hello", "world");
    num2 = snprintf(str2, 50, "%sNORMAL STRING%s", "hello", "world");

    ck_assert_int_eq(num1, num2);

    for (int i = 0; i < num1; i++)
    {
        ck_assert_int_eq(str1[i], str2[i]);
    }
}
END_TEST

// Функция тестирования какой-либо задачи.
START_TEST(li_one)
{
    int num1;
    int num2;

    char str1[50];
    char str2[50];

    num1 = my_snprintf(str1, 10, "%li", (long)123456789);
    num2 = snprintf(str2, 10, "%li", (long)123456789);

    ck_assert_int_eq(num1, num2);

    for (int i = 0; i < num1; i++)
    {
        ck_assert_int_eq(str1[i], str2[i]);
    }
}
END_TEST

// Функция тестирования какой-либо задачи.
START_TEST(li_row)
{
    int num1;
    int num2;

    char str1[50];
    char str2[50];

    num1 = my_snprintf(str1, 50, "%li%li%li", (long)123456789, (long)-67584, (long)-347324839);
    num2 = snprintf(str2, 50, "%li%li%li", (long)123456789, (long)-67584, (long)-347324839);

    ck_assert_int_eq(num1, num2);

    for (int i = 0; i < num1; i++)
    {
        ck_assert_int_eq(str1[i], str2[i]);
    }
}
END_TEST

// Функция тестирования какой-либо задачи.
START_TEST(li_middle)
{
    int num1;
    int num2;

    char str1[50];
    char str2[50];

    num1 = my_snprintf(str1, 50, "NOR%liMA%liL%liSTRING", (long)123456789, (long)-67584, (long)-347324839);
    num2 = snprintf(str2, 50, "NOR%liMA%liL%liSTRING", (long)123456789, (long)-67584, (long)-347324839);

    ck_assert_int_eq(num1, num2);

    for (int i = 0; i < num1; i++)
    {
        ck_assert_int_eq(str1[i], str2[i]);
    }
}
END_TEST

// Функция тестирования какой-либо задачи.
START_TEST(li_edges)
{
    int num1;
    int num2;

    char str1[50];
    char str2[50];

    num1 = my_snprintf(str1, 50, "%liNORMAL STRING%li", (long)123456789, (long)-347324839);
    num2 = snprintf(str2, 50, "%liNORMAL STRING%li", (long)123456789, (long)-347324839);

    ck_assert_int_eq(num1, num2);

    for (int i = 0; i < num1; i++)
    {
        ck_assert_int_eq(str1[i], str2[i]);
    }
}
END_TEST

// // Функция тестирования какой-либо задачи.
// START_TEST(all_one_char1)
// {
//     int num1;
//     int num2;

//     char str1[50];
//     char str2[50];

//     num1 = my_snprintf(str1, 1, "%li", (long)-347324839);
//     num2 = snprintf(str2, 1, "%li", (long)-347324839);

//     ck_assert_int_eq(num1, num2);

//     for (int i = 0; i < num1; i++)
//     {
//         ck_assert_int_eq(str1[i], str2[i]);
//     }
// }
// END_TEST

// Функция тестирования какой-либо задачи.
START_TEST(all_one_char2)
{
    int num1;
    int num2;

    char str1[50];
    char str2[50];

    num1 = my_snprintf(str1, 2, "_");
    num2 = snprintf(str2, 2, "_");

    ck_assert_int_eq(num1, num2);

    for (int i = 0; i < num1; i++)
    {
        ck_assert_int_eq(str1[i], str2[i]);
    }
}
END_TEST

// Функция тестирования какой-либо задачи.
START_TEST(all_no_args)
{
    int num1;
    int num2;

    char str1[50];
    char str2[50];

    num1 = my_snprintf(str1, 10, "test");
    num2 = snprintf(str2, 10, "test");

    ck_assert_int_eq(num1, num2);

    for (int i = 0; i < num1; i++)
    {
        ck_assert_int_eq(str1[i], str2[i]);
    }
}
END_TEST

// Функция создания набора тестов.
Suite *suite_create_my_snprintf(void)
{
    Suite *suite = suite_create("my_snprintf");
    // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
    TCase *tcase_core = tcase_create("Positives");

    // Добавление теста в группу тестов.
    tcase_add_test(tcase_core, s_one);
    tcase_add_test(tcase_core, s_row);
    tcase_add_test(tcase_core, s_middle);
    tcase_add_test(tcase_core, s_edges);

    tcase_add_test(tcase_core, li_one);
    tcase_add_test(tcase_core, li_row);
    tcase_add_test(tcase_core, li_middle);
    tcase_add_test(tcase_core, li_edges);

    tcase_add_test(tcase_core, all_no_args);
    // tcase_add_test(tcase_core, all_one_char1);
    tcase_add_test(tcase_core, all_one_char2);

    // Добавление теста в тестовый набор.
    suite_add_tcase(suite, tcase_core);

    return suite;
}

int check_my_snprintf(void)
{
    int failed_count;
    Suite *suite = suite_create_my_snprintf();
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