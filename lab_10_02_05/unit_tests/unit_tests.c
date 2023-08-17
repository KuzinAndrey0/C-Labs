#include "../inc/unit_tests.h"
#include "../inc/dynamic_data.h"

struct allocated_data_s global_data;

int main(void)
{
    check_find_substring();
    check_remove_spaces();
    return 0;
}