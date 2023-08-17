#include "../inc/dynamic_data.h"
#include "../inc/list_funcs.h"
#include "../inc/my_defines.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1.0e-7
//    ck_assert_double_eq_tol(avg, 0.0, EPS);

// Функция тестирования какой-либо задачи.
START_TEST(middle)
{
    int *val_ptr[11];
    list_t list;
    list_node *to_add = calloc(1, sizeof(list_node));
    list.head = NULL;
    list.total = 0;

    for (int i = 0; i < 10; i++)
    {
        val_ptr[i] = malloc(sizeof(int));
        *val_ptr[i] = i;
        list_add_last(&list, (void *)val_ptr[i]);
    }
    val_ptr[10] = malloc(sizeof(int));
    *val_ptr[10] = 50;

    list_node *before = list.head;

    for (int i = 0; i < 5; i++)
    {
        before = before->next;
    }

    to_add->data = val_ptr[10];
    to_add->next = NULL;

    insert(&(list.head), to_add, before);

    list_node *test_ptr = list.head;
    for (int i = 0; i < 11; i++)
    {
        int ii;
        if (i < 5)
            ii = i;
        if (i == 5)
            ii = 50;
        if (i > 5)
            ii = i - 1;

        int val = *((int *)test_ptr->data);
        test_ptr = test_ptr->next;

        ck_assert_int_eq(val, ii);
    }

    list_node *ptr = list.head;

    while (ptr != NULL)
    {
        list_node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }

    for (int i = 0; i < 11; i++)
        free(val_ptr[i]);
}
END_TEST

START_TEST(start)
{
    int *val_ptr[11];
    list_t list;
    list_node *to_add = calloc(1, sizeof(list_node));
    list.head = NULL;
    list.total = 0;

    for (int i = 0; i < 10; i++)
    {
        val_ptr[i] = malloc(sizeof(int));
        *val_ptr[i] = i;
        list_add_last(&list, (void *)val_ptr[i]);
    }
    val_ptr[10] = malloc(sizeof(int));
    *val_ptr[10] = 50;

    list_node *before = NULL;

    to_add->data = val_ptr[10];
    to_add->next = NULL;

    insert(&(list.head), to_add, before);

    list_node *test_ptr = list.head;
    for (int i = 0; i < 11; i++)
    {
        int ii;
        if (i < 10)
            ii = i;
        if (i == 10)
            ii = 50;
        if (i > 10)
            ii = i - 1;

        int val = *((int *)test_ptr->data);
        test_ptr = test_ptr->next;

        ck_assert_int_eq(val, ii);
    }

    list_node *ptr = list.head;

    while (ptr != NULL)
    {
        list_node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }

    for (int i = 0; i < 11; i++)
        free(val_ptr[i]);
}
END_TEST

START_TEST(end)
{
    int *val_ptr[11];
    list_t list;
    list_node *to_add = calloc(1, sizeof(list_node));
    list.head = NULL;
    list.total = 0;

    for (int i = 0; i < 10; i++)
    {
        val_ptr[i] = malloc(sizeof(int));
        *val_ptr[i] = i;
        list_add_last(&list, (void *)val_ptr[i]);
    }
    val_ptr[10] = malloc(sizeof(int));
    *val_ptr[10] = 50;

    list_node *before = list.head;

    to_add->data = val_ptr[10];
    to_add->next = NULL;

    insert(&(list.head), to_add, before);

    list_node *test_ptr = list.head;
    for (int i = 0; i < 11; i++)
    {
        int ii;
        if (i < 0)
            ii = i;
        if (i == 0)
            ii = 50;
        if (i > 0)
            ii = i - 1;

        int val = *((int *)test_ptr->data);
        test_ptr = test_ptr->next;

        ck_assert_int_eq(val, ii);
    }

    list_node *ptr = list.head;

    while (ptr != NULL)
    {
        list_node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }

    for (int i = 0; i < 11; i++)
        free(val_ptr[i]);
}
END_TEST

// Функция создания набора тестов.
Suite *suite_create_insert(void)
{
    Suite *suite = suite_create("insert");
    // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
    TCase *tcase_core = tcase_create("Positives");

    // Добавление теста в группу тестов.
    tcase_add_test(tcase_core, middle);
    tcase_add_test(tcase_core, start);
    tcase_add_test(tcase_core, end);

    // Добавление теста в тестовый набор.
    suite_add_tcase(suite, tcase_core);

    return suite;
}

int check_insert(void)
{
    int failed_count;
    Suite *suite = suite_create_insert();
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