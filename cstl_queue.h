#ifndef CSTL_QUEUE_H
#define CSTL_QUEUE_H

#include "cstl_common.h"

#define CSTL_QUEUE_INITIAL_CAPACITY 4

/**
 * CSTL_QUEUE(type)
 * ================
 *
 * DESCRIPTION
 *   Generic type-safe FIFO queue (First-In-First-Out) macro for C. Implements
 *   a complete queue data structure using circular buffer for O(1) enqueue
 *   and dequeue operations. This is a standalone implementation with NO
 *   dependencies on vector or other containers.
 *
 * GENERATED FUNCTIONS (where <type> is the instantiated type)
 *
 *   Initialization & Destruction:
 *   - queue_<type>_init(q)           Initialize queue with default capacity
 *   - queue_<type>_destroy(q)        Free internal storage and reset state
 *   - queue_<type>_reserve(q, n)     Reserve capacity for at least n elements
 *
 *   Queue Operations:
 *   - queue_<type>_enqueue(q, val)   Add value to back of queue (returns int)
 *   - queue_<type>_dequeue(q)        Remove value from front (returns int)
 *   - queue_<type>_front(q)          Get pointer to front element without removing
 *   - queue_<type>_back(q)           Get pointer to back element without removing
 *   - queue_<type>_size(q)           Get current number of elements
 *   - queue_<type>_capacity(q)       Get allocated capacity
 *   - queue_<type>_is_empty(q)       Check if queue is empty
 *
 * RETURN VALUES
 *   Functions return CSTL_SUCCESS (0) on success or negative error codes:
 *   - CSTL_ERROR_ALLOCATION        Memory allocation failed
 *   - CSTL_ERROR_INVALID_ARGUMENT  Invalid argument (NULL ptr, etc.)
 *   - CSTL_ERROR_EMPTY             Dequeue/front attempted on empty queue
 *
 * USAGE NOTES
 *   - Queue is implemented as a circular buffer for O(1) operations
 *   - No dependency on vector or other containers
 *   - All functions validate input arguments and return appropriate errors
 *   - front()/back() return pointers to elements (dereference to get value)
 *   - dequeue() removes front element but does NOT return its value
 *   - Capacity grows exponentially (2x) to amortize insertion costs
 *   - Caller is responsible for cleanup of pointer elements before destroy()
 *
 * EXAMPLE
 *   CSTL_QUEUE(int);
 *   queue_int q;
 *   queue_int_init(&q);
 *   if (queue_int_enqueue(&q, 10) != CSTL_SUCCESS) { handle error }
 *   if (queue_int_enqueue(&q, 20) != CSTL_SUCCESS) { handle error }
 *   int* front = queue_int_front(&q);
 *   if (front) printf("%d\n", *front);
 *   queue_int_dequeue(&q);
 *   queue_int_destroy(&q);
 */

#define CSTL_QUEUE(type) \
typedef struct queue_##type queue_##type; \
\
struct queue_##type { \
    type* data; \
    size_t front_idx; \
    size_t size; \
    size_t capacity; \
}; \
\
static inline void queue_##type##_init(queue_##type* queue) { \
    if (!queue) return; \
    queue->data = (type*)CSTL_MALLOC(CSTL_QUEUE_INITIAL_CAPACITY * sizeof(type)); \
    if (queue->data) { \
        memset(queue->data, 0, CSTL_QUEUE_INITIAL_CAPACITY * sizeof(type)); \
        queue->front_idx = 0; \
        queue->size = 0; \
        queue->capacity = CSTL_QUEUE_INITIAL_CAPACITY; \
    } else { \
        queue->front_idx = 0; \
        queue->size = 0; \
        queue->capacity = 0; \
        CSTL_LOG("init: Allocation failed"); \
    } \
} \
\
static inline void queue_##type##_destroy(queue_##type* queue) { \
    if (queue) { \
        if (queue->data) { \
            CSTL_FREE(queue->data); \
            queue->data = NULL; \
        } \
        queue->front_idx = 0; \
        queue->size = 0; \
        queue->capacity = 0; \
    } \
} \
\
static inline int queue_##type##_reserve(queue_##type* queue, size_t n) { \
    CSTL_CHECK(!queue, "reserve: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    \
    size_t target_capacity = n; \
    if (queue->capacity == 0 && target_capacity == 0) { \
        target_capacity = CSTL_QUEUE_INITIAL_CAPACITY; \
    } \
    \
    if (target_capacity < queue->size) { \
        target_capacity = queue->size; \
    } \
    \
    if (target_capacity > queue->capacity) { \
        type* new_data = (type*)CSTL_MALLOC(target_capacity * sizeof(type)); \
        CSTL_CHECK(!new_data, "reserve: Malloc failed", CSTL_ERROR_ALLOCATION); \
        \
        if (queue->size > 0) { \
            if (queue->front_idx + queue->size <= queue->capacity) { \
                memcpy(new_data, queue->data + queue->front_idx, queue->size * sizeof(type)); \
            } else { \
                size_t first_part = queue->capacity - queue->front_idx; \
                memcpy(new_data, queue->data + queue->front_idx, first_part * sizeof(type)); \
                memcpy(new_data + first_part, queue->data, (queue->size - first_part) * sizeof(type)); \
            } \
        } \
        \
        CSTL_FREE(queue->data); \
        queue->data = new_data; \
        queue->front_idx = 0; \
        queue->capacity = target_capacity; \
    } \
    return CSTL_SUCCESS; \
} \
\
static inline int queue_##type##_enqueue(queue_##type* queue, type val) { \
    CSTL_CHECK(!queue, "enqueue: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    \
    if (queue->size >= queue->capacity) { \
        if (queue_##type##_reserve(queue, queue->capacity * 2) != CSTL_SUCCESS) { \
            return CSTL_ERROR_ALLOCATION; \
        } \
    } \
    \
    size_t back_idx = (queue->front_idx + queue->size) % queue->capacity; \
    queue->data[back_idx] = val; \
    queue->size++; \
    return CSTL_SUCCESS; \
} \
\
static inline int queue_##type##_dequeue(queue_##type* queue) { \
    CSTL_CHECK(!queue, "dequeue: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    CSTL_CHECK(queue->size == 0, "dequeue: Empty", CSTL_ERROR_EMPTY); \
    \
    queue->data[queue->front_idx] = (type){0}; \
    queue->front_idx = (queue->front_idx + 1) % queue->capacity; \
    queue->size--; \
    return CSTL_SUCCESS; \
} \
\
static inline type* queue_##type##_front(const queue_##type* queue) { \
    CSTL_CHECK_PTR_RET(!queue, "front: NULL"); \
    CSTL_CHECK_PTR_RET(queue->size == 0, "front: Empty"); \
    return &queue->data[queue->front_idx]; \
} \
\
static inline type* queue_##type##_back(const queue_##type* queue) { \
    CSTL_CHECK_PTR_RET(!queue, "back: NULL"); \
    CSTL_CHECK_PTR_RET(queue->size == 0, "back: Empty"); \
    size_t back_idx = (queue->front_idx + queue->size - 1) % queue->capacity; \
    return &queue->data[back_idx]; \
} \
\
static inline size_t queue_##type##_size(const queue_##type* queue) { \
    return queue ? queue->size : 0; \
} \
\
static inline size_t queue_##type##_capacity(const queue_##type* queue) { \
    return queue ? queue->capacity : 0; \
} \
\
static inline int queue_##type##_is_empty(const queue_##type* queue) { \
    return queue ? (queue->size == 0) : 1; \
} \

#endif /* CSTL_QUEUE_H */
