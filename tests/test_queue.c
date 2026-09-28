#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "data_structures/Queue.h"

#define CHECK(condition)                                                        \
    do {                                                                        \
        if (!(condition)) {                                                     \
            fprintf(stderr, "Check failed at %s:%d: %s\\n", __FILE__, __LINE__, \
                    #condition);                                               \
            return false;                                                       \
        }                                                                       \
    } while (0)

static bool test_empty_queue_operations(void) {
    TestQueue queue;
    int test_id = -1;

    CHECK(queue_init(&queue));
    CHECK(queue_is_empty(&queue));
    CHECK(!queue_is_full(&queue));
    CHECK(!queue_dequeue(&queue, &test_id));
    CHECK(test_id == -1);
    return true;
}

static bool test_fifo_order(void) {
    TestQueue queue;
    int test_id = 0;

    CHECK(queue_init(&queue));
    CHECK(queue_enqueue(&queue, 101));
    CHECK(queue_enqueue(&queue, 202));
    CHECK(queue_enqueue(&queue, 303));
    CHECK(queue_dequeue(&queue, &test_id));
    CHECK(test_id == 101);
    CHECK(queue_dequeue(&queue, &test_id));
    CHECK(test_id == 202);
    CHECK(queue_enqueue(&queue, 404));
    CHECK(queue_enqueue(&queue, 505));
    CHECK(queue_dequeue(&queue, &test_id));
    CHECK(test_id == 303);
    CHECK(queue_dequeue(&queue, &test_id));
    CHECK(test_id == 404);
    CHECK(queue_dequeue(&queue, &test_id));
    CHECK(test_id == 505);
    CHECK(queue_is_empty(&queue));
    return true;
}

static bool test_full_queue_and_wraparound(void) {
    TestQueue queue;
    int test_id = 0;
    size_t index;

    CHECK(queue_init(&queue));
    for (index = 0U; index < INJECTION_TEST_QUEUE_CAPACITY; ++index) {
        CHECK(queue_enqueue(&queue, (int)(index + 1U)));
    }
    CHECK(queue_is_full(&queue));
    CHECK(!queue_enqueue(&queue, 999));

    CHECK(queue_dequeue(&queue, &test_id));
    CHECK(test_id == 1);
    CHECK(queue_dequeue(&queue, &test_id));
    CHECK(test_id == 2);
    CHECK(queue_enqueue(&queue, 11));
    CHECK(queue_enqueue(&queue, 12));

    for (index = 3U; index <= INJECTION_TEST_QUEUE_CAPACITY + 2U; ++index) {
        CHECK(queue_dequeue(&queue, &test_id));
        CHECK(test_id == (int)index);
    }
    CHECK(queue_is_empty(&queue));
    return true;
}

static bool test_invalid_pointers(void) {
    TestQueue queue;
    int test_id = 0;

    CHECK(!queue_init(NULL));
    CHECK(!queue_enqueue(NULL, 1));
    CHECK(!queue_dequeue(NULL, &test_id));
    CHECK(queue_init(&queue));
    CHECK(!queue_dequeue(&queue, NULL));
    CHECK(queue_is_empty(NULL));
    CHECK(!queue_is_full(NULL));
    return true;
}

int main(void) {
    if (!test_empty_queue_operations() || !test_fifo_order() ||
        !test_full_queue_and_wraparound() || !test_invalid_pointers()) {
        return 1;
    }

    puts("All queue tests passed.");
    return 0;
}
