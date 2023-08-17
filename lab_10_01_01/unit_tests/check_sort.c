#include "../inc/dynamic_data.h"
#include "../inc/list_funcs.h"
#include "../inc/my_defines.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1.0e-7
//    ck_assert_double_eq_tol(avg, 0.0, EPS);

int cmpfunc(const void *ptr1, const void *ptr2)
{
    int num1 = *((int *)ptr1);
    int num2 = *((int *)ptr2);
    return num1 - num2;
}

// Функция тестирования какой-либо задачи.
START_TEST(sorted)
{
    int *val_ptr[10];
    list_t list;
    list.head = NULL;
    list.total = 0;

    for (int i = 0; i < 10; i++)
    {
        val_ptr[i] = malloc(sizeof(int));
        *val_ptr[i] = i;
        list_add_last(&list, (void *)val_ptr[i]);
    }

    list.head = sort(list.head, cmpfunc);

    list_node *test_ptr = list.head;
    for (int i = 0; i < 10; i++)
    {
        int val = *((int *)test_ptr->data);
        test_ptr = test_ptr->next;

        ck_assert_int_eq(val, i);
    }

    list_node *ptr = list.head;

    while (ptr != NULL)
    {
        list_node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }

    for (int i = 0; i < 10; i++)
        free(val_ptr[i]);
}
END_TEST

START_TEST(revsorted)
{
    int *val_ptr[10];
    list_t list;
    list.head = NULL;
    list.total = 0;

    for (int i = 0; i < 10; i++)
    {
        val_ptr[i] = malloc(sizeof(int));
        *val_ptr[i] = 9 - i;
        list_add_last(&list, (void *)val_ptr[i]);
    }

    list.head = sort(list.head, cmpfunc);

    list_node *test_ptr = list.head;
    for (int i = 0; i < 10; i++)
    {
        int val = *((int *)test_ptr->data);
        test_ptr = test_ptr->next;

        ck_assert_int_eq(val, i);
    }

    list_node *ptr = list.head;

    while (ptr != NULL)
    {
        list_node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }

    for (int i = 0; i < 10; i++)
        free(val_ptr[i]);
}
END_TEST

START_TEST(unsorted)
{
    int vals[] = {7, 4, 9, 3, 6, 2, 0, 5, 1, 8};
    int *val_ptr[10];
    list_t list;
    list.head = NULL;
    list.total = 0;

    for (int i = 0; i < 10; i++)
    {
        val_ptr[i] = malloc(sizeof(int));
        *val_ptr[i] = vals[i];
        list_add_last(&list, (void *)val_ptr[i]);
    }

    list.head = sort(list.head, cmpfunc);

    list_node *test_ptr = list.head;
    for (int i = 0; i < 10; i++)
    {
        int val = *((int *)test_ptr->data);
        test_ptr = test_ptr->next;

        ck_assert_int_eq(val, i);
    }

    list_node *ptr = list.head;

    while (ptr != NULL)
    {
        list_node *tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }

    for (int i = 0; i < 10; i++)
        free(val_ptr[i]);
}
END_TEST

// Функция создания набора тестов.
Suite *suite_create_sort(void)
{
    Suite *suite = suite_create("sort");
    // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
    TCase *tcase_core = tcase_create("Positives");

    // Добавление теста в группу тестов.
    tcase_add_test(tcase_core, sorted);
    tcase_add_test(tcase_core, revsorted);
    tcase_add_test(tcase_core, unsorted);

    // Добавление теста в тестовый набор.
    suite_add_tcase(suite, tcase_core);

    return suite;
}

int check_sort(void)
{
    int failed_count;
    Suite *suite = suite_create_sort();
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