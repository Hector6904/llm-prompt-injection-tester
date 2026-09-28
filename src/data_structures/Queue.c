#include "data_structures/Queue.h"

bool queue_init(TestQueue *queue) {
    if (queue == NULL) {
        return false;
    }

    queue->front = 0U;
    queue->rear = 0U;
    queue->count = 0U;
    return true;
}

bool queue_enqueue(TestQueue *queue, int test_id) {
    if (queue == NULL || queue_is_full(queue)) {
        return false;
    }

    queue->test_ids[queue->rear] = test_id;
    queue->rear = (queue->rear + 1U) % INJECTION_TEST_QUEUE_CAPACITY;
    ++queue->count;
    return true;
}

bool queue_dequeue(TestQueue *queue, int *test_id) {
    if (queue == NULL || test_id == NULL || queue_is_empty(queue)) {
        return false;
    }

    *test_id = queue->test_ids[queue->front];
    queue->front = (queue->front + 1U) % INJECTION_TEST_QUEUE_CAPACITY;
    --queue->count;
    return true;
}

bool queue_is_empty(const TestQueue *queue) {
    return queue == NULL || queue->count == 0U;
}

bool queue_is_full(const TestQueue *queue) {
    return queue != NULL && queue->count == INJECTION_TEST_QUEUE_CAPACITY;
}
