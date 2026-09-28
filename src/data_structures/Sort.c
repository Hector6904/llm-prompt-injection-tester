#include "data_structures/Sort.h"

#include <stdint.h>
#include <stdlib.h>

static void swap_integers(int *left, int *right) {
    const int temporary = *left;
    *left = *right;
    *right = temporary;
}

bool bubble_sort(int array[], size_t size) {
    size_t unsorted_end;

    if (array == NULL) {
        return false;
    }

    for (unsorted_end = size; unsorted_end > 1U; --unsorted_end) {
        bool swapped = false;
        size_t index;

        for (index = 1U; index < unsorted_end; ++index) {
            if (array[index - 1U] > array[index]) {
                swap_integers(&array[index - 1U], &array[index]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }

    return true;
}

bool selection_sort(int array[], size_t size) {
    size_t index;

    if (array == NULL) {
        return false;
    }

    if (size < 2U) {
        return true;
    }

    for (index = 0U; index < size - 1U; ++index) {
        size_t minimum_index = index;
        size_t candidate;

        for (candidate = index + 1U; candidate < size; ++candidate) {
            if (array[candidate] < array[minimum_index]) {
                minimum_index = candidate;
            }
        }

        if (minimum_index != index) {
            swap_integers(&array[index], &array[minimum_index]);
        }
    }

    return true;
}

bool insertion_sort(int array[], size_t size) {
    size_t index;

    if (array == NULL) {
        return false;
    }

    for (index = 1U; index < size; ++index) {
        const int value = array[index];
        size_t position = index;

        while (position > 0U && array[position - 1U] > value) {
            array[position] = array[position - 1U];
            --position;
        }
        array[position] = value;
    }

    return true;
}

static void merge_ranges(int array[], int temporary[], size_t begin, size_t middle,
                         size_t end) {
    size_t left = begin;
    size_t right = middle;
    size_t destination = begin;
    size_t index;

    while (left < middle && right < end) {
        if (array[left] <= array[right]) {
            temporary[destination++] = array[left++];
        } else {
            temporary[destination++] = array[right++];
        }
    }

    while (left < middle) {
        temporary[destination++] = array[left++];
    }

    while (right < end) {
        temporary[destination++] = array[right++];
    }

    for (index = begin; index < end; ++index) {
        array[index] = temporary[index];
    }
}

static void merge_sort_range(int array[], int temporary[], size_t begin, size_t end) {
    const size_t length = end - begin;
    const size_t middle = begin + length / 2U;

    if (length < 2U) {
        return;
    }

    merge_sort_range(array, temporary, begin, middle);
    merge_sort_range(array, temporary, middle, end);
    merge_ranges(array, temporary, begin, middle, end);
}

bool merge_sort(int array[], size_t size) {
    int *temporary;

    if (array == NULL) {
        return false;
    }

    if (size < 2U) {
        return true;
    }

    if (size > SIZE_MAX / sizeof(*temporary)) {
        return false;
    }

    temporary = malloc(size * sizeof(*temporary));
    if (temporary == NULL) {
        return false;
    }

    merge_sort_range(array, temporary, 0U, size);
    free(temporary);
    return true;
}

static int median_of_three(int first, int middle, int last) {
    if (first < middle) {
        if (middle < last) {
            return middle;
        }
        return first < last ? last : first;
    }

    if (first < last) {
        return first;
    }
    return middle < last ? last : middle;
}

static void partition_three_way(int array[], size_t low, size_t high,
                                size_t *equal_begin, size_t *equal_end) {
    const size_t middle_index = low + (high - low) / 2U;
    const int pivot = median_of_three(array[low], array[middle_index], array[high - 1U]);
    size_t less = low;
    size_t current = low;
    size_t greater = high;

    while (current < greater) {
        if (array[current] < pivot) {
            swap_integers(&array[less], &array[current]);
            ++less;
            ++current;
        } else if (array[current] > pivot) {
            --greater;
            swap_integers(&array[current], &array[greater]);
        } else {
            ++current;
        }
    }

    *equal_begin = less;
    *equal_end = greater;
}

static void quick_sort_range(int array[], size_t low, size_t high) {
    while (high - low > 1U) {
        size_t equal_begin;
        size_t equal_end;
        size_t left_size;
        size_t right_size;

        partition_three_way(array, low, high, &equal_begin, &equal_end);
        left_size = equal_begin - low;
        right_size = high - equal_end;

        if (left_size < right_size) {
            quick_sort_range(array, low, equal_begin);
            low = equal_end;
        } else {
            quick_sort_range(array, equal_end, high);
            high = equal_begin;
        }
    }
}

bool quick_sort(int array[], size_t size) {
    if (array == NULL) {
        return false;
    }

    quick_sort_range(array, 0U, size);
    return true;
}
