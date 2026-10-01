#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TEST_RESULT_STACK_CAPACITY 10U

typedef struct {
    int result_ids[TEST_RESULT_STACK_CAPACITY];
    size_t top;
} TestResultStack;

bool stack_init(TestResultStack *stack);

bool stack_push(TestResultStack *stack, int result_id);

bool stack_pop(TestResultStack *stack, int *result_id);

bool stack_peek(const TestResultStack *stack, int *result_id);

bool stack_is_empty(const TestResultStack *stack);

bool stack_is_full(const TestResultStack *stack);

#ifdef __cplusplus
}
#endif

#endif  /* DATA_STRUCTURES_STACK_H */
