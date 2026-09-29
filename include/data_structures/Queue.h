#ifndef DATA_STRUCTURES_QUEUE_H
#define DATA_STRUCTURES_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The queue holds pending InjectionTest identifiers until C/C++ integration. */
#define INJECTION_TEST_QUEUE_CAPACITY 10U

typedef struct {
    int test_ids[INJECTION_TEST_QUEUE_CAPACITY];
    size_t front;
    size_t rear;
    size_t count;
} TestQueue;

/* Returns false only when queue is NULL. */
bool queue_init(TestQueue *queue);

/* Returns false when queue is NULL or already full. */
bool queue_enqueue(TestQueue *queue, int test_id);

/* Returns false when a pointer is NULL or the queue is empty. */
bool queue_dequeue(TestQueue *queue, int *test_id);

/* A NULL queue is treated as empty so callers can safely avoid dequeueing it. */
bool queue_is_empty(const TestQueue *queue);

/* A NULL queue is never considered full; mutation operations still reject it. */
bool queue_is_full(const TestQueue *queue);

#ifdef __cplusplus
}
#endif

#endif  /* DATA_STRUCTURES_QUEUE_H */
