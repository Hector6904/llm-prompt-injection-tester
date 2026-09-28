#ifndef DATA_STRUCTURES_SORT_H
#define DATA_STRUCTURES_SORT_H

#include <stdbool.h>
#include <stddef.h>

/* Each function sorts array in ascending order and returns false when array is NULL. */
bool bubble_sort(int array[], size_t size);
bool selection_sort(int array[], size_t size);
bool insertion_sort(int array[], size_t size);

/*
 * Merge sort returns false when array is NULL or temporary-buffer allocation fails.
 * On allocation failure, the array is left unchanged.
 */
bool merge_sort(int array[], size_t size);

bool quick_sort(int array[], size_t size);

#endif  /* DATA_STRUCTURES_SORT_H */
