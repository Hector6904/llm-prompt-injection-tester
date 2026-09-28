#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "data_structures/Search.h"

#define CHECK(condition)                                                        \
    do {                                                                        \
        if (!(condition)) {                                                     \
            fprintf(stderr, "Check failed at %s:%d: %s\\n", __FILE__, __LINE__, \
                    #condition);                                               \
            return false;                                                       \
        }                                                                       \
    } while (0)

static bool index_matches_target(int index, const int array[], size_t size,
                                 int target) {
    return index >= 0 && (size_t)index < size && array[index] == target;
}

static bool test_linear_search(void) {
    const int values[] = {4, 9, 2, 7, 5};
    const int single_value[] = {42};
    const int duplicate_values[] = {8, 3, 8, 1, 8};
    const size_t values_size = sizeof(values) / sizeof(values[0]);
    const size_t duplicate_values_size =
        sizeof(duplicate_values) / sizeof(duplicate_values[0]);
    int index;

    CHECK(linear_search(values, values_size, 2) == 2);
    CHECK(linear_search(values, values_size, 4) == 0);
    CHECK(linear_search(values, values_size, 5) == 4);
    CHECK(linear_search(values, values_size, 99) == -1);
    CHECK(linear_search(values, 0U, 4) == -1);
    CHECK(linear_search(single_value, 1U, 42) == 0);
    CHECK(linear_search(single_value, 1U, 99) == -1);

    index = linear_search(duplicate_values, duplicate_values_size, 8);
    CHECK(index_matches_target(index, duplicate_values, duplicate_values_size, 8));
    CHECK(linear_search(NULL, values_size, 4) == -1);
    CHECK(linear_search(NULL, 0U, 4) == -1);
    return true;
}

static bool test_binary_search(void) {
    const int values[] = {2, 4, 6, 8, 10};
    const int single_value[] = {42};
    const int duplicate_values[] = {1, 3, 3, 3, 7};
    const size_t values_size = sizeof(values) / sizeof(values[0]);
    const size_t duplicate_values_size =
        sizeof(duplicate_values) / sizeof(duplicate_values[0]);
    int index;

    CHECK(binary_search(values, values_size, 6) == 2);
    CHECK(binary_search(values, values_size, 2) == 0);
    CHECK(binary_search(values, values_size, 10) == 4);
    CHECK(binary_search(values, values_size, 5) == -1);
    CHECK(binary_search(values, 0U, 2) == -1);
    CHECK(binary_search(single_value, 1U, 42) == 0);
    CHECK(binary_search(single_value, 1U, 99) == -1);

    index = binary_search(duplicate_values, duplicate_values_size, 3);
    CHECK(index_matches_target(index, duplicate_values, duplicate_values_size, 3));
    CHECK(binary_search(NULL, values_size, 2) == -1);
    CHECK(binary_search(NULL, 0U, 2) == -1);
    return true;
}

int main(void) {
    if (!test_linear_search() || !test_binary_search()) {
        return 1;
    }

    puts("All search tests passed.");
    return 0;
}
