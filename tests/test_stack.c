#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "data_structures/Stack.h"

#define CHECK(condition)                                                        \
    do {                                                                        \
        if (!(condition)) {                                                     \
            fprintf(stderr, "Check failed at %s:%d: %s\\n", __FILE__, __LINE__, \
                    #condition);                                               \
            return false;                                                       \
        }                                                                       \
    } while (0)

static bool test_empty_stack_operations(void) {
    TestResultStack stack;
    int result_id = -1;

    CHECK(stack_init(&stack));
    CHECK(stack_is_empty(&stack));
    CHECK(!stack_is_full(&stack));
    CHECK(!stack_pop(&stack, &result_id));
    CHECK(result_id == -1);
    CHECK(!stack_peek(&stack, &result_id));
    CHECK(result_id == -1);
    return true;
}

static bool test_lifo_order_and_peek(void) {
    TestResultStack stack;
    int result_id = 0;

    CHECK(stack_init(&stack));
    CHECK(stack_push(&stack, 101));
    CHECK(stack_push(&stack, 202));
    CHECK(stack_push(&stack, 303));
    CHECK(stack_peek(&stack, &result_id));
    CHECK(result_id == 303);
    CHECK(!stack_is_empty(&stack));
    CHECK(stack_pop(&stack, &result_id));
    CHECK(result_id == 303);
    CHECK(stack_pop(&stack, &result_id));
    CHECK(result_id == 202);
    CHECK(stack_push(&stack, 404));
    CHECK(stack_pop(&stack, &result_id));
    CHECK(result_id == 404);
    CHECK(stack_pop(&stack, &result_id));
    CHECK(result_id == 101);
    CHECK(stack_is_empty(&stack));
    return true;
}

static bool test_full_stack(void) {
    TestResultStack stack;
    int result_id = 0;
    size_t index;

    CHECK(stack_init(&stack));
    for (index = 0U; index < TEST_RESULT_STACK_CAPACITY; ++index) {
        CHECK(stack_push(&stack, (int)(index + 1U)));
    }
    CHECK(stack_is_full(&stack));
    CHECK(!stack_push(&stack, 999));

    for (index = TEST_RESULT_STACK_CAPACITY; index > 0U; --index) {
        CHECK(stack_pop(&stack, &result_id));
        CHECK(result_id == (int)index);
    }
    CHECK(stack_is_empty(&stack));
    return true;
}

static bool test_invalid_pointers(void) {
    TestResultStack stack;
    int result_id = 0;

    CHECK(!stack_init(NULL));
    CHECK(!stack_push(NULL, 1));
    CHECK(!stack_pop(NULL, &result_id));
    CHECK(!stack_peek(NULL, &result_id));
    CHECK(stack_init(&stack));
    CHECK(!stack_pop(&stack, NULL));
    CHECK(!stack_peek(&stack, NULL));
    CHECK(stack_is_empty(NULL));
    CHECK(!stack_is_full(NULL));
    return true;
}

int main(void) {
    if (!test_empty_stack_operations() || !test_lifo_order_and_peek() ||
        !test_full_stack() || !test_invalid_pointers()) {
        return 1;
    }

    puts("All stack tests passed.");
    return 0;
}
