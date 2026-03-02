#ifndef CSTL_STACK_H
#define CSTL_STACK_H

#include "cstl_common.h"

#define CSTL_STACK_INITIAL_CAPACITY 4

/**
 * CSTL_STACK(type)
 * ================ 
 *
 * DESCRIPTION
 *   Generic type-safe LIFO stack (Last-In-First-Out) macro for C. Implements
 *   a complete stack data structure with dynamic memory management.
 *   Instantiates a `stack_<type>` struct and inline functions for operations.
 *   This is a standalone implementation with NO dependencies on vector.
 *
 * GENERATED FUNCTIONS (where <type> is the instantiated type)
 *
 *   Initialization & Destruction:
 *   - stack_<type>_init(s)           Initialize stack with default capacity
 *   - stack_<type>_destroy(s)        Free internal storage and reset state
 *   - stack_<type>_reserve(s, n)     Reserve capacity for at least n elements
 *
 *   Stack Operations:
 *   - stack_<type>_push(s, val)      Push value onto stack (returns int)
 *   - stack_<type>_pop(s)            Pop top value from stack (returns int)
 *   - stack_<type>_pop_value(s, out) Pop value into an out-parameter
 *   - stack_<type>_top(s)            Get pointer to top element without removing
 *   - stack_<type>_size(s)           Get current number of elements
 *   - stack_<type>_capacity(s)       Get allocated capacity
 *   - stack_<type>_is_empty(s)       Check if stack is empty
 *   
 *   USAGE NOTES - Stack is implemented as a standalone data structure
 *   - No dependency on vector or other containers
 *   - All functions validate input arguments and return appropriate errors
 *   - top() returns pointer to top element (dereference to get value)
 *   - pop() removes and clears the top element but does NOT return its value
 *   - Capacity grows exponentially (2x) to amortize insertion costs
 *   - Caller is responsible for cleanup of pointer elements before destroy()
 * 
 *   EXAMPLE
 *   CSTL_STACK(int);
 *   stack_int s;
 *   stack_int_init(&s);
 *   if (stack_int_push(&s, 42) != CSTL_SUCCESS)
 *   int* top = stack_int_top(&s);
 *   stack_int_pop(&s);
 *   stack_int_destroy(&s) */

#define CSTL_STACK(type) \
typedef struct stack_##type stack_##type; \
\
struct stack_##type { \
    type* data; \
    size_t size; \
    size_t capacity; \
}; \
\
static inline void stack_##type##_init(stack_##type* stack) { \
    if (!stack) return; \
    stack->data = (type*)CSTL_MALLOC(CSTL_STACK_INITIAL_CAPACITY * sizeof(type)); \
    if (stack->data) { \
        memset(stack->data, 0, CSTL_STACK_INITIAL_CAPACITY * sizeof(type)); \
        stack->size = 0; \
        stack->capacity = CSTL_STACK_INITIAL_CAPACITY; \
    } else { \
        stack->size = 0; \
        stack->capacity = 0; \
        CSTL_LOG("init: Allocation failed"); \
    } \
} \
\
static inline void stack_##type##_destroy(stack_##type* stack) { \
    if (stack) { \
        if (stack->data) { \
            CSTL_FREE(stack->data); \
            stack->data = NULL; \
        } \
        stack->size = 0; \
        stack->capacity = 0; \
    } \
} \
\
static inline int stack_##type##_reserve(stack_##type* stack, size_t n) { \
    CSTL_CHECK(!stack, "reserve: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    \
    size_t target_capacity = n; \
    if (stack->capacity == 0 && target_capacity == 0) { \
        target_capacity = CSTL_STACK_INITIAL_CAPACITY; \
    } \
    \
    if (target_capacity < stack->size) { \
        target_capacity = stack->size; \
    } \
    \
    if (target_capacity > stack->capacity) { \
        void* ptr = CSTL_REALLOC(stack->data, target_capacity * sizeof(type)); \
        CSTL_CHECK(!ptr, "reserve: Realloc failed", CSTL_ERROR_ALLOCATION); \
        stack->data = (type*)ptr; \
        stack->capacity = target_capacity; \
    } \
    return CSTL_SUCCESS; \
} \
\
static inline int stack_##type##_push(stack_##type* stack, type val) { \
    CSTL_CHECK(!stack, "push: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    \
    if (stack->size >= stack->capacity) { \
        if (stack_##type##_reserve(stack, stack->capacity * 2) != CSTL_SUCCESS) { \
            return CSTL_ERROR_ALLOCATION; \
        } \
    } \
    \
    stack->data[stack->size++] = val; \
    return CSTL_SUCCESS; \
} \
\
static inline int stack_##type##_pop(stack_##type* stack) { \
    CSTL_CHECK(!stack, "pop: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    CSTL_CHECK(stack->size == 0, "pop: Empty", CSTL_ERROR_EMPTY); \
    \
    stack->data[stack->size - 1] = (type){0}; \
    stack->size--; \
    return CSTL_SUCCESS; \
} \
\
static inline int stack_##type##_pop_value(stack_##type* stack, type* value_out) { \
    CSTL_CHECK(!stack || !value_out, "pop_value: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    CSTL_CHECK(stack->size == 0, "pop_value: Empty", CSTL_ERROR_EMPTY); \
    \
    *value_out = stack->data[stack->size - 1]; \
    stack->data[stack->size - 1] = (type){0}; \
    stack->size--; \
    return CSTL_SUCCESS; \
} \
\
static inline type* stack_##type##_top(const stack_##type* stack) { \
    CSTL_CHECK_PTR_RET(!stack, "top: NULL"); \
    CSTL_CHECK_PTR_RET(stack->size == 0, "top: Empty"); \
    return &stack->data[stack->size - 1]; \
} \
\
static inline size_t stack_##type##_size(const stack_##type* stack) { \
    return stack ? stack->size : 0; \
} \
\
static inline size_t stack_##type##_capacity(const stack_##type* stack) { \
    return stack ? stack->capacity : 0; \
} \
\
static inline int stack_##type##_is_empty(const stack_##type* stack) { \
    return stack ? (stack->size == 0) : 1; \
} \

#endif /* CSTL_STACK_H */
