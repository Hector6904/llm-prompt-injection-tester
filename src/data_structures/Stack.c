#include "data_structures/Stack.h"

bool stack_init(TestResultStack *stack) {
    if (stack == NULL) {
        return false;
    }

    stack->top = 0U;
    return true;
}

bool stack_push(TestResultStack *stack, int result_id) {
    if (stack == NULL || stack_is_full(stack)) {
        return false;
    }

    stack->result_ids[stack->top] = result_id;
    ++stack->top;
    return true;
}

bool stack_pop(TestResultStack *stack, int *result_id) {
    if (stack == NULL || result_id == NULL || stack_is_empty(stack)) {
        return false;
    }

    --stack->top;
    *result_id = stack->result_ids[stack->top];
    return true;
}

bool stack_peek(const TestResultStack *stack, int *result_id) {
    if (stack == NULL || result_id == NULL || stack_is_empty(stack)) {
        return false;
    }

    *result_id = stack->result_ids[stack->top - 1U];
    return true;
}

bool stack_is_empty(const TestResultStack *stack) {
    return stack == NULL || stack->top == 0U;
}

bool stack_is_full(const TestResultStack *stack) {
    return stack != NULL && stack->top == TEST_RESULT_STACK_CAPACITY;
}
