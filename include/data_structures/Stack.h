#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The stack holds TestResult identifiers until C/C++ integration. */
#define TEST_RESULT_STACK_CAPACITY 10U

typedef struct {
    int result_ids[TEST_RESULT_STACK_CAPACITY];
    size_t top;
} TestResultStack;

/* Returns false only when stack is NULL. */
bool stack_init(TestResultStack *stack);

/* Returns false when stack is NULL or already full. */
bool stack_push(TestResultStack *stack, int result_id);

/* Returns false when a pointer is NULL or the stack is empty. */
bool stack_pop(TestResultStack *stack, int *result_id);

/* Returns false when a pointer is NULL or the stack is empty. */
bool stack_peek(const TestResultStack *stack, int *result_id);

/* A NULL stack is treated as empty so callers can safely avoid popping it. */
bool stack_is_empty(const TestResultStack *stack);

/* A NULL stack is never considered full; mutation operations still reject it. */
bool stack_is_full(const TestResultStack *stack);

#ifdef __cplusplus
}
#endif

#endif  /* DATA_STRUCTURES_STACK_H */
