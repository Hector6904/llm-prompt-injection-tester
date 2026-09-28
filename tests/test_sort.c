#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "data_structures/Sort.h"

#define CHECK(condition)                                                        \
    do {                                                                        \
        if (!(condition)) {                                                     \
            fprintf(stderr, "Check failed at %s:%d: %s\\n", __FILE__, __LINE__, \
                    #condition);                                               \
            return false;                                                       \
        }                                                                       \
    } while (0)

typedef bool (*SortFunction)(int array[], size_t size);

static bool sort_and_check(SortFunction sort, int array[], const int expected[],
                           size_t size) {
    CHECK(sort(array, size));
    CHECK(memcmp(array, expected, size * sizeof(array[0])) == 0);
    return true;
}

static bool test_sort_algorithm(SortFunction sort) {
    int ordinary[] = {5, 1, 4, 2, 8};
    const int ordinary_expected[] = {1, 2, 4, 5, 8};
    int already_sorted[] = {1, 2, 3, 4, 5};
    const int already_sorted_expected[] = {1, 2, 3, 4, 5};
    int reverse_sorted[] = {5, 4, 3, 2, 1};
    const int reverse_sorted_expected[] = {1, 2, 3, 4, 5};
    int duplicates[] = {3, 1, 3, 2, 1};
    const int duplicates_expected[] = {1, 1, 2, 3, 3};
    int negative_values[] = {0, -3, 5, -1, 2};
    const int negative_values_expected[] = {-3, -1, 0, 2, 5};
    int single_value[] = {42};
    const int single_value_expected[] = {42};
    int identical_values[] = {7, 7, 7, 7};
    const int identical_values_expected[] = {7, 7, 7, 7};
    int empty_placeholder = 99;

    CHECK(sort_and_check(sort, ordinary, ordinary_expected,
                         sizeof(ordinary) / sizeof(ordinary[0])));
    CHECK(sort_and_check(sort, already_sorted, already_sorted_expected,
                         sizeof(already_sorted) / sizeof(already_sorted[0])));
    CHECK(sort_and_check(sort, reverse_sorted, reverse_sorted_expected,
                         sizeof(reverse_sorted) / sizeof(reverse_sorted[0])));
    CHECK(sort_and_check(sort, duplicates, duplicates_expected,
                         sizeof(duplicates) / sizeof(duplicates[0])));
    CHECK(sort_and_check(sort, negative_values, negative_values_expected,
                         sizeof(negative_values) / sizeof(negative_values[0])));
    CHECK(sort_and_check(sort, single_value, single_value_expected,
                         sizeof(single_value) / sizeof(single_value[0])));
    CHECK(sort_and_check(sort, identical_values, identical_values_expected,
                         sizeof(identical_values) / sizeof(identical_values[0])));
    CHECK(sort(&empty_placeholder, 0U));
    CHECK(empty_placeholder == 99);
    CHECK(!sort(NULL, 0U));
    return true;
}

static bool run_sort_test(const char *algorithm_name, SortFunction sort) {
    if (!test_sort_algorithm(sort)) {
        fprintf(stderr, "%s tests failed.\\n", algorithm_name);
        return false;
    }

    return true;
}

static bool test_merge_sort_size_guard(void) {
    int value = 99;

    CHECK(!merge_sort(&value, SIZE_MAX));
    CHECK(value == 99);
    return true;
}

int main(void) {
    if (!run_sort_test("bubble_sort", bubble_sort) ||
        !run_sort_test("selection_sort", selection_sort) ||
        !run_sort_test("insertion_sort", insertion_sort) ||
        !run_sort_test("merge_sort", merge_sort) ||
        !run_sort_test("quick_sort", quick_sort) || !test_merge_sort_size_guard()) {
        return 1;
    }

    puts("All sort tests passed.");
    return 0;
}
