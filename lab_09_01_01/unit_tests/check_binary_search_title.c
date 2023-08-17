#include <stdlib.h>
// Подключаем заголовочный файл библиотеки.
#include "../inc/find_struct.h"
#include "../inc/my_defines.h"
#include <check.h>
#include <stdio.h>

// Функция тестирования какой-либо задачи.
START_TEST(middle)
{
    film_t **film_p = malloc(3 * sizeof(film_t *));

    film_t film[3];

    film[0].title = "TEST1";

    film[1].title = "TEST2";

    film[2].title = "TEST3";

    for (int i = 0; i < 3; i++)
        film_p[i] = &film[i];

    int found = binary_search_title(film_p, "TEST1", 3);

    ck_assert_int_eq(found, 0);

    free(film_p);
}
END_TEST

START_TEST(first)
{
    film_t **film_p = malloc(3 * sizeof(film_t *));

    film_t film[3];

    film[0].title = "TEST1";

    film[1].title = "TEST2";

    film[2].title = "TEST3";

    for (int i = 0; i < 3; i++)
        film_p[i] = &film[i];

    int found = binary_search_title(film_p, "TEST2", 3);

    ck_assert_int_eq(found, 1);

    free(film_p);
}
END_TEST

START_TEST(last)
{
    film_t **film_p = malloc(3 * sizeof(film_t *));

    film_t film[3];

    film[0].title = "TEST1";

    film[1].title = "TEST2";

    film[2].title = "TEST3";

    for (int i = 0; i < 3; i++)
        film_p[i] = &film[i];

    int found = binary_search_title(film_p, "TEST3", 3);

    ck_assert_int_eq(found, 2);

    free(film_p);
}
END_TEST

// Функция создания набора тестов.
Suite *suite_create_binary_search_title(void)
{
    Suite *suite = suite_create("binary_search_title");
    // Набор разбивается на группы тестов, разделённых по каким-либо критериям.
    TCase *tcase_core = tcase_create("Positives");

    // Добавление теста в группу тестов.
    tcase_add_test(tcase_core, middle);
    tcase_add_test(tcase_core, first);
    tcase_add_test(tcase_core, last);

    // Добавление теста в тестовый набор.
    suite_add_tcase(suite, tcase_core);

    return suite;
}

int check_binary_search_title(void)
{
    int failed_count;
    Suite *suite = suite_create_binary_search_title();
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