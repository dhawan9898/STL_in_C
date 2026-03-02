#ifndef CSTL_DEQUE_H
#define CSTL_DEQUE_H

#include "cstl_common.h"

#define CSTL_DEQUE_INITIAL_CAPACITY 8

/**
 * CSTL_DEQUE(type)
 * ================ 
 *
 * DESCRIPTION
 *   Generic type-safe deque (Double-Ended Queue) macro for C. Implements
 *   a complete deque data structure using a circular buffer for O(1) amortized
 *   push and pop operations at both ends.
 *
 * GENERATED FUNCTIONS (where <type> is the instantiated type)
 *
 *   Initialization & Destruction:
 *   - deque_<type>_init(d)           Initialize deque with default capacity
 *   - deque_<type>_destroy(d)        Free internal storage
 *   - deque_<type>_reserve(d, n)     Reserve capacity for at least n elements
 *
 *   Insertion & Removal:
 *   - deque_<type>_push_front(d, val) Add value to the front
 *   - deque_<type>_push_back(d, val)  Add value to the back
 *   - deque_<type>_pop_front(d)       Remove value from the front
 *   - deque_<type>_pop_back(d)        Remove value from the back
 *
 *   Access:
 *   - deque_<type>_front(d)          Get pointer to the front element
 *   - deque_<type>_back(d)           Get pointer to the back element
 *   - deque_<type>_at(d, i)          Get pointer to the element at index i
 *
 *   Properties:
 *   - deque_<type>_size(d)           Get current number of elements
 *   - deque_<type>_capacity(d)       Get allocated capacity
 *   - deque_<type>_is_empty(d)       Check if deque is empty
 */

#define CSTL_DEQUE(type) \
typedef struct deque_##type deque_##type; \
\
struct deque_##type { \
    type* data; \
    size_t front_idx; \
    size_t size; \
    size_t capacity; \
}; \
\
static inline void deque_##type##_init(deque_##type* deque) { \
    if (!deque) return; \
    deque->data = (type*)CSTL_MALLOC(CSTL_DEQUE_INITIAL_CAPACITY * sizeof(type)); \
    if (deque->data) { \
        deque->front_idx = 0; \
        deque->size = 0; \
        deque->capacity = CSTL_DEQUE_INITIAL_CAPACITY; \
    } else { \
        deque->front_idx = 0; \
        deque->size = 0; \
        deque->capacity = 0; \
        CSTL_LOG("init: Allocation failed"); \
    } \
} \
\
static inline void deque_##type##_destroy(deque_##type* deque) { \
    if (deque) { \
        if (deque->data) { \
            CSTL_FREE(deque->data); \
            deque->data = NULL; \
        } \
        deque->front_idx = 0; \
        deque->size = 0; \
        deque->capacity = 0; \
    } \
} \
\
static inline int deque_##type##_reserve(deque_##type* deque, size_t n) { \
    CSTL_CHECK(!deque, "reserve: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    if (n <= deque->capacity) return CSTL_SUCCESS; \
     \
    type* new_data = (type*)CSTL_MALLOC(n * sizeof(type)); \
    CSTL_CHECK(!new_data, "reserve: Malloc failed", CSTL_ERROR_ALLOCATION); \
     \
    if (deque->size > 0) { \
        size_t back_idx = (deque->front_idx + deque->size); \
        if (back_idx <= deque->capacity) { \
            memcpy(new_data, deque->data + deque->front_idx, deque->size * sizeof(type)); \
        } else { \
            size_t first_part_count = deque->capacity - deque->front_idx; \
            memcpy(new_data, deque->data + deque->front_idx, first_part_count * sizeof(type)); \
            memcpy(new_data + first_part_count, deque->data, (back_idx % deque->capacity) * sizeof(type)); \
        } \
    } \
     \
    CSTL_FREE(deque->data); \
    deque->data = new_data; \
    deque->front_idx = 0; \
    deque->capacity = n; \
     \
    return CSTL_SUCCESS; \
} \
\
static inline int deque_##type##_push_back(deque_##type* deque, type val) { \
    CSTL_CHECK(!deque, "push_back: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    if (deque->size >= deque->capacity) { \
        if (deque_##type##_reserve(deque, deque->capacity * 2) != CSTL_SUCCESS) return CSTL_ERROR_ALLOCATION; \
    } \
    size_t back_idx = (deque->front_idx + deque->size) % deque->capacity; \
    deque->data[back_idx] = val; \
    deque->size++; \
    return CSTL_SUCCESS; \
} \
\
static inline int deque_##type##_push_front(deque_##type* deque, type val) { \
    CSTL_CHECK(!deque, "push_front: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    if (deque->size >= deque->capacity) { \
        if (deque_##type##_reserve(deque, deque->capacity * 2) != CSTL_SUCCESS) return CSTL_ERROR_ALLOCATION; \
    } \
    deque->front_idx = (deque->front_idx == 0) ? deque->capacity - 1 : deque->front_idx - 1; \
    deque->data[deque->front_idx] = val; \
    deque->size++; \
    return CSTL_SUCCESS; \
} \
\
static inline int deque_##type##_pop_front(deque_##type* deque) { \
    CSTL_CHECK(!deque, "pop_front: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    CSTL_CHECK(deque->size == 0, "pop_front: Empty", CSTL_ERROR_EMPTY); \
    deque->front_idx = (deque->front_idx + 1) % deque->capacity; \
    deque->size--; \
    return CSTL_SUCCESS; \
} \
\
static inline int deque_##type##_pop_back(deque_##type* deque) { \
    CSTL_CHECK(!deque, "pop_back: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    CSTL_CHECK(deque->size == 0, "pop_back: Empty", CSTL_ERROR_EMPTY); \
    deque->size--; \
    return CSTL_SUCCESS; \
} \
\
static inline type* deque_##type##_front(const deque_##type* deque) { \
    CSTL_CHECK_PTR_RET(!deque || deque->size == 0, "front: Empty or NULL"); \
    return &deque->data[deque->front_idx]; \
} \
\
static inline type* deque_##type##_back(const deque_##type* deque) { \
    CSTL_CHECK_PTR_RET(!deque || deque->size == 0, "back: Empty or NULL"); \
    size_t back_idx = (deque->front_idx + deque->size - 1) % deque->capacity; \
    return &deque->data[back_idx]; \
} \
\
static inline type* deque_##type##_at(const deque_##type* deque, size_t index) { \
    CSTL_CHECK_PTR_RET(!deque || index >= deque->size, "at: Out of bounds or NULL"); \
    size_t internal_idx = (deque->front_idx + index) % deque->capacity; \
    return &deque->data[internal_idx]; \
} \
\
static inline size_t deque_##type##_size(const deque_##type* deque) { \
    return deque ? deque->size : 0; \
} \
\
static inline size_t deque_##type##_capacity(const deque_##type* deque) { \
    return deque ? deque->capacity : 0; \
} \
\
static inline int deque_##type##_is_empty(const deque_##type* deque) { \
    return deque ? (deque->size == 0) : 1; \
} \

#endif /* CSTL_DEQUE_H */
