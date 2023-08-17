#include "../inc/dynamic_data.h"
#include "../inc/list_strings.h"
#include "../inc/my_defines.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

// Функция тестирования какой-либо задачи.
START_TEST(begin)
{

    init_global_data();

    char test_in[] = "This is a test";
    char test_in2[] = "This";

    list_t string_list, string_list2;

    init_list(&string_list);
    init_list(&string_list2);

    convert_to_list(test_in, &string_list);
    convert_to_list(test_in2, &string_list2);

    int rc = find_substring(string_list, string_list2);
    ck_assert_int_eq(rc, 0);

    list_node *ptr = string_list.head;
    while (ptr != NULL)
    {
        list_node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
    ptr = string_list2.head;
    while (ptr != NULL)
    {
        list_node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
}
END_TEST

START_TEST(end)
{

    init_global_data();

    char test_in[] = "This is a test";
    char test_in2[] = "test";

    list_t string_list, string_list2;

    init_list(&string_list);
    init_list(&string_list2);

    convert_to_list(test_in, &string_list);
    convert_to_list(test_in2, &string_list2);

    int rc = find_substring(string_list, string_list2);
    ck_assert_int_eq(rc, 10);

    list_node *ptr = string_list.head;
    while (ptr != NULL)
    {
        list_node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
    ptr = string_list2.head;
    while (ptr != NULL)
    {
        list_node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
}
END_TEST

START_TEST(middle)
{

    init_global_data();

    char test_in[] = "This is a test";
    char test_in2[] = " a";

    list_t string_list, string_list2;

    init_list(&string_list);
    init_list(&string_list2);

    convert_to_list(test_in, &string_list);
    convert_to_list(test_in2, &string_list2);

    int rc = find_substring(string_list, string_list2);
    ck_assert_int_eq(rc, 7);

    list_node *ptr = string_list.head;
    while (ptr != NULL)
    {
        list_node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
    ptr = string_list2.head;
    while (ptr != NULL)
    {
        list_node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
}
END_TEST

START_TEST(none)
{

    init_global_data();

    char test_in[] = "This is a test";
    char test_in2[] = " m";

    list_t string_list, string_list2;

    init_list(&string_list);
    init_list(&string_list2);

    convert_to_list(test_in, &string_list);
    convert_to_list(test_in2, &string_list2);

    int rc = find_substring(string_list, string_list2);
    ck_assert_int_eq(rc, -1);

    list_node *ptr = string_list.head;
    while (ptr != NULL)
    {
        list_node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
    ptr = string_list2.head;
    while (ptr != NULL)
    {
        list_node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
}
END_TEST

// Функция создания набора тестов.
Suite *suite_create_find_substring(void)
{
    Suite *suite = suite_create("find_substring");
    // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
    TCase *tcase_core = tcase_create("Positives");

    // Добавление теста в группу тестов.
    tcase_add_test(tcase_core, begin);
    tcase_add_test(tcase_core, end);
    tcase_add_test(tcase_core, middle);
    tcase_add_test(tcase_core, none);
    // Добавление теста в тестовый набор.
    suite_add_tcase(suite, tcase_core);

    return suite;
}

int check_find_substring(void)
{
    int failed_count;
    Suite *suite = suite_create_find_substring();
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