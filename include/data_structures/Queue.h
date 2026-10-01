#ifndef DATA_STRUCTURES_QUEUE_H
#define DATA_STRUCTURES_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define INJECTION_TEST_QUEUE_CAPACITY 10U

typedef struct {
    int test_ids[INJECTION_TEST_QUEUE_CAPACITY];
    size_t front;
    size_t rear;
    size_t count;
} TestQueue;

bool queue_init(TestQueue *queue);

bool queue_enqueue(TestQueue *queue, int test_id);

bool queue_dequeue(TestQueue *queue, int *test_id);

bool queue_is_empty(const TestQueue *queue);

bool queue_is_full(const TestQueue *queue);

#ifdef __cplusplus
}
#endif

#endif
