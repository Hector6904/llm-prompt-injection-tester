#include "data_structures/Search.h"

int linear_search(const int array[], size_t size, int target) {
    size_t index;

    if (array == NULL) {
        return -1;
    }

    for (index = 0U; index < size; ++index) {
        if (array[index] == target) {
            return (int)index;
        }
    }

    return -1;
}

int binary_search(const int array[], size_t size, int target) {
    size_t low = 0U;
    size_t high = size;

    if (array == NULL) {
        return -1;
    }

    while (low < high) {
        const size_t middle = low + (high - low) / 2U;

        if (array[middle] == target) {
            return (int)middle;
        }

        if (array[middle] < target) {
            low = middle + 1U;
        } else {
            high = middle;
        }
    }

    return -1;
}
