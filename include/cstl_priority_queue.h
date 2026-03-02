#ifndef CSTL_PRIORITY_QUEUE_H
#define CSTL_PRIORITY_QUEUE_H

#include "cstl_vector.h"

#define CSTL_PRIORITY_QUEUE(type) \
\
CSTL_VECTOR(type) \
\
typedef struct priority_queue_##type { \
    vector_##type* vector; \
    int (*compare)(const void*, const void*); \
} priority_queue_##type; \
\
static inline void pq_##type##_heapify_up(priority_queue_##type* pq, size_t index); \
static inline void pq_##type##_heapify_down(priority_queue_##type* pq, size_t index); \
\
static inline void priority_queue_##type##_init(priority_queue_##type* pq, int (*compare)(const void*, const void*)) { \
    CSTL_CHECK_VOID(!pq, "init: NULL"); \
    pq->vector = (vector_##type*)CSTL_MALLOC(sizeof(vector_##type)); \
    CSTL_CHECK_VOID(!pq->vector, "init: Malloc failed"); \
    vector_##type##_init(pq->vector); \
    pq->compare = compare; \
} \
\
static inline void priority_queue_##type##_destroy(priority_queue_##type* pq) { \
    CSTL_CHECK_VOID(!pq, "destroy: NULL"); \
    if (pq->vector) { \
        vector_##type##_destroy(pq->vector); \
        CSTL_FREE(pq->vector); \
        pq->vector = NULL; \
    } \
} \
\
static inline int priority_queue_##type##_push(priority_queue_##type* pq, type value) { \
    CSTL_CHECK(!pq, "push: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    int res = vector_##type##_push_back(pq->vector, value); \
    if (res != CSTL_SUCCESS) return res; \
    pq_##type##_heapify_up(pq, vector_##type##_size(pq->vector) - 1); \
    return CSTL_SUCCESS; \
} \
\
static inline int priority_queue_##type##_pop(priority_queue_##type* pq) { \
    CSTL_CHECK(!pq, "pop: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    CSTL_CHECK(vector_##type##_is_empty(pq->vector), "pop: Empty", CSTL_ERROR_EMPTY); \
    size_t last_index = vector_##type##_size(pq->vector) - 1; \
    type* data = pq->vector->data; \
    type temp = data[0]; \
    data[0] = data[last_index]; \
    data[last_index] = temp; \
    vector_##type##_pop_back(pq->vector); \
    pq_##type##_heapify_down(pq, 0); \
    return CSTL_SUCCESS; \
} \
\
static inline type* priority_queue_##type##_top(const priority_queue_##type* pq) { \
    CSTL_CHECK_PTR_RET(!pq || vector_##type##_is_empty(pq->vector), "top: Empty or NULL"); \
    return vector_##type##_front(pq->vector); \
} \
\
static inline size_t priority_queue_##type##_size(const priority_queue_##type* pq) { \
    return pq ? vector_##type##_size(pq->vector) : 0; \
} \
\
static inline int priority_queue_##type##_is_empty(const priority_queue_##type* pq) { \
    return pq ? vector_##type##_is_empty(pq->vector) : 1; \
} \
\
static inline void pq_##type##_heapify_up(priority_queue_##type* pq, size_t index) { \
    if (index == 0) return; \
    size_t parent_index = (index - 1) / 2; \
    type* data = pq->vector->data; \
    if (pq->compare(&data[index], &data[parent_index]) > 0) { \
        type temp = data[index]; \
        data[index] = data[parent_index]; \
        data[parent_index] = temp; \
        pq_##type##_heapify_up(pq, parent_index); \
    } \
} \
\
static inline void pq_##type##_heapify_down(priority_queue_##type* pq, size_t index) { \
    size_t size = vector_##type##_size(pq->vector); \
    if (size <= 1) return; \
    size_t left_child = 2 * index + 1; \
    size_t right_child = 2 * index + 2; \
    size_t largest = index; \
    type* data = pq->vector->data; \
    if (left_child < size && pq->compare(&data[left_child], &data[largest]) > 0) { \
        largest = left_child; \
    } \
    if (right_child < size && pq->compare(&data[right_child], &data[largest]) > 0) { \
        largest = right_child; \
    } \
    if (largest != index) { \
        type temp = data[index]; \
        data[index] = data[largest]; \
        data[largest] = temp; \
        pq_##type##_heapify_down(pq, largest); \
    } \
}

#endif /* CSTL_PRIORITY_QUEUE_H */
