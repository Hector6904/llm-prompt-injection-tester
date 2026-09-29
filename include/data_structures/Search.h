#ifndef DATA_STRUCTURES_SEARCH_H
#define DATA_STRUCTURES_SEARCH_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Returns the first matching index, or -1 when the target is absent or array is
 * NULL. The array size must permit every valid index to be represented as int.
 */
int linear_search(const int array[], size_t size, int target);

/*
 * Searches an array sorted in ascending order. Returns a matching index, or -1
 * when the target is absent or array is NULL. With duplicates, any matching index
 * may be returned. The array size must permit every valid index as an int.
 */
int binary_search(const int array[], size_t size, int target);

#ifdef __cplusplus
}
#endif

#endif  /* DATA_STRUCTURES_SEARCH_H */
