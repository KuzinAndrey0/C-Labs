#include "../inc/unit_tests.h"
#include "../inc/dynamic_data.h"

struct allocated_data_s global_data;

int main(void)
{
    check_pop_front();
    check_insert();
    check_sort();

    return 0;
}