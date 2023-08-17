#include <stdlib.h>
// Подключаем заголовочный файл библиотеки.
#include "../inc/my_defines.h"
#include "../inc/sort_struct.h"
#include <check.h>
#include <stdio.h>

// Функция тестирования какой-либо задачи.
START_TEST(unsorted)
{
    film_t **film_p = malloc(3 * sizeof(film_t *));

    film_t film[3];

    film[0].title = "3";

    film[1].title = "1";

    film[2].title = "2";

    for (int i = 0; i < 3; i++)
        film_p[i] = &film[i];

    sort_struct_title(film_p, 3);

    for (int i = 0; i < 3; i++)
        ck_assert_int_eq(i + 1, atoi(film_p[i]->title));

    free(film_p);
}
END_TEST

START_TEST(sorted)
{
    film_t **film_p = malloc(3 * sizeof(film_t *));

    film_t film[3];

    film[0].title = "1";

    film[1].title = "2";

    film[2].title = "3";

    for (int i = 0; i < 3; i++)
        film_p[i] = &film[i];

    sort_struct_title(film_p, 3);

    for (int i = 0; i < 3; i++)
        ck_assert_int_eq(i + 1, atoi(film_p[i]->title));

    free(film_p);
}
END_TEST

START_TEST(sorted_rev)
{
    film_t **film_p = malloc(3 * sizeof(film_t *));

    film_t film[3];

    film[0].title = "3";

    film[1].title = "2";

    film[2].title = "1";

    for (int i = 0; i < 3; i++)
        film_p[i] = &film[i];

    sort_struct_title(film_p, 3);

    for (int i = 0; i < 3; i++)
        ck_assert_int_eq(i + 1, atoi(film_p[i]->title));

    free(film_p);
}
END_TEST

// Функция создания набора тестов.
Suite *suite_create_sort_struct_title(void)
{
    Suite *suite = suite_create("sort_struct_title");
    // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
    TCase *tcase_core = tcase_create("Positives");

    // Добавление теста в группу тестов.
    tcase_add_test(tcase_core, unsorted);
    tcase_add_test(tcase_core, sorted);
    tcase_add_test(tcase_core, sorted_rev);

    // Добавление теста в тестовый набор.
    suite_add_tcase(suite, tcase_core);

    return suite;
}

int check_sort_struct_title(void)
{
    int failed_count;
    Suite *suite = suite_create_sort_struct_title();
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