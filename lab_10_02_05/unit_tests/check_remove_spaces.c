#include "../inc/dynamic_data.h"
#include "../inc/list_strings.h"
#include "../inc/my_defines.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

// Функция тестирования какой-либо задачи.
START_TEST(none)
{

    init_global_data();

    char test_in[] = "This is a test";
    char test_in2[] = "This is a test";

    list_t string_list, string_list2;

    init_list(&string_list);
    init_list(&string_list2);

    convert_to_list(test_in, &string_list);
    convert_to_list(test_in2, &string_list2);

    remove_spaces(&string_list);

    list_node *ptr1 = string_list.head;
    list_node *ptr2 = string_list2.head;

    int stop = 0;
    for (int i = 0; i < string_list.total && !stop; i++)
    {
        for (int j = 0; j < 4 && !stop; j++)
        {
            ck_assert_int_eq(((char *)ptr1->data)[j], ((char *)ptr2->data)[j]);
            if (((char *)ptr1->data)[j] == '\0')
                stop = 1;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

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

// Функция тестирования какой-либо задачи.
START_TEST(one_series)
{

    init_global_data();

    char test_in[] = "This is    a test";
    char test_in2[] = "This is a test";

    list_t string_list, string_list2;

    init_list(&string_list);
    init_list(&string_list2);

    convert_to_list(test_in, &string_list);
    convert_to_list(test_in2, &string_list2);

    remove_spaces(&string_list);

    list_node *ptr1 = string_list.head;
    list_node *ptr2 = string_list2.head;

    int stop = 0;
    for (int i = 0; i < string_list.total && !stop; i++)
    {
        for (int j = 0; j < 4 && !stop; j++)
        {
            ck_assert_int_eq(((char *)ptr1->data)[j], ((char *)ptr2->data)[j]);
            if (((char *)ptr1->data)[j] == '\0')
                stop = 1;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

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

// Функция тестирования какой-либо задачи.
START_TEST(multiple_series)
{

    init_global_data();

    char test_in[] = "Th      is        is    a     test";
    char test_in2[] = "Th is is a test";

    list_t string_list, string_list2;

    init_list(&string_list);
    init_list(&string_list2);

    convert_to_list(test_in, &string_list);
    convert_to_list(test_in2, &string_list2);

    remove_spaces(&string_list);

    list_node *ptr1 = string_list.head;
    list_node *ptr2 = string_list2.head;

    int stop = 0;
    for (int i = 0; i < string_list.total && !stop; i++)
    {
        for (int j = 0; j < 4 && !stop; j++)
        {
            ck_assert_int_eq(((char *)ptr1->data)[j], ((char *)ptr2->data)[j]);
            if (((char *)ptr1->data)[j] == '\0')
                stop = 1;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

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

// Функция тестирования какой-либо задачи.
START_TEST(edges)
{

    init_global_data();

    char test_in[] = "                         Th      is        is    a     test                    ";
    char test_in2[] = " Th is is a test ";

    list_t string_list, string_list2;

    init_list(&string_list);
    init_list(&string_list2);

    convert_to_list(test_in, &string_list);
    convert_to_list(test_in2, &string_list2);

    remove_spaces(&string_list);

    list_node *ptr1 = string_list.head;
    list_node *ptr2 = string_list2.head;

    int stop = 0;
    for (int i = 0; i < string_list.total && !stop; i++)
    {
        for (int j = 0; j < 4 && !stop; j++)
        {
            ck_assert_int_eq(((char *)ptr1->data)[j], ((char *)ptr2->data)[j]);
            if (((char *)ptr1->data)[j] == '\0')
                stop = 1;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

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
Suite *suite_create_remove_spaces(void)
{
    Suite *suite = suite_create("remove_spaces");
    // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
    TCase *tcase_core = tcase_create("Positives");

    // Добавление теста в группу тестов.
    tcase_add_test(tcase_core, none);
    tcase_add_test(tcase_core, one_series);
    tcase_add_test(tcase_core, multiple_series);
    tcase_add_test(tcase_core, edges);

    // Добавление теста в тестовый набор.
    suite_add_tcase(suite, tcase_core);

    return suite;
}

int check_remove_spaces(void)
{
    int failed_count;
    Suite *suite = suite_create_remove_spaces();
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