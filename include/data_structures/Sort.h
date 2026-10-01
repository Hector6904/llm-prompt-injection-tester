#ifndef DATA_STRUCTURES_SORT_H
#define DATA_STRUCTURES_SORT_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

bool bubble_sort(int array[], size_t size);
bool selection_sort(int array[], size_t size);
bool insertion_sort(int array[], size_t size);


bool merge_sort(int array[], size_t size);

bool quick_sort(int array[], size_t size);

#ifdef __cplusplus
}
#endif

#endif  /* DATA_STRUCTURES_SORT_H */
