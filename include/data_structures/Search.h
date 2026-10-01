#ifndef DATA_STRUCTURES_SEARCH_H
#define DATA_STRUCTURES_SEARCH_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


int linear_search(const int array[], size_t size, int target);


int binary_search(const int array[], size_t size, int target);

#ifdef __cplusplus
}
#endif

#endif
