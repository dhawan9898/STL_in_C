#ifndef CSTL_VECTOR_H
#define CSTL_VECTOR_H

#include "cstl_common.h"

#define CSTL_VECTOR_INITIAL_CAPACITY 4

/**
 * CSTL_VECTOR(type)
 * =================
 *
 * DESCRIPTION
 *   Generic type-safe dynamic array (vector) macro for C. Instantiates a
 *   complete vector implementation for the given `type`, declaring a
 *   `vector_<type>` struct and inline functions operating on that type.
 *
 * GENERATED FUNCTIONS (where <type> is the instantiated type)
 *
 *   Initialization & Destruction:
 *   - vector_<type>_init(v)         Initialize with default capacity
 *   - vector_<type>_destroy(v)      Free internal storage
 *   - vector_<type>_reserve(v, n)   Ensure capacity >= n elements
 *
 *   Insertion & Removal:
 *   - vector_<type>_push_back(v, d)      Append element to end
 *   - vector_<type>_pop_back(v)          Remove last element
 *   - vector_<type>_insert(v, i, d)      Insert at index i
 *   - vector_<type>_erase(v, i)          Remove element at index i
 *   - vector_<type>_erase_range(v, s, e) Erase range [s, e)
 *   - vector_<type>_clear(v)             Remove all elements
 *
 *   Properties & Access:
 *   - vector_<type>_size(v)              Get current element count
 *   - vector_<type>_capacity(v)          Get allocated capacity
 *   - vector_<type>_at(v, i)             Pointer to element at index i
 *   - vector_<type>_front(v)             Pointer to first element
 *   - vector_<type>_back(v)              Pointer to last element
 *   - vector_<type>_is_empty(v)          Return non-zero if empty
 *
 *   Algorithms:
 *   - vector_<type>_copy(dst, src)       Deep copy src into dst
 *   - vector_<type>_sort(v)              Sort using compare_<type>
 *   - vector_<type>_find(v, val, idx)    Linear search
 *   - vector_<type>_binary_search(v, val, idx)  Binary search (requires sort)
 *
 * RETURN VALUES
 *   Functions return CSTL_SUCCESS (0) on success or negative error codes:
 *   - CSTL_ERROR_ALLOCATION        Memory allocation failed
 *   - CSTL_ERROR_INVALID_ARGUMENT  Invalid argument (NULL ptr, etc.)
 *   - CSTL_ERROR_OUT_OF_BOUNDS     Index out of bounds
 *   - CSTL_ERROR_EMPTY             Operation on empty vector
 *   - CSTL_ERROR_NOT_FOUND         Search value not found
 *
 * USAGE NOTES
 *   - Requires compare function: For int/double use compare_int/compare_double
 *     from cstl_common.h. For custom types, provide your own compare_<type>.
 *   - For strings: typedef const char* str; then CSTL_VECTOR(str)
 *     requires compare_str from cstl_common.h
 *   - Pointer-returning functions (at, front, back) return NULL on error
 *   - destroy() does NOT free elements that are pointers; caller must manage
 *   - Capacity grows exponentially (2x) to amortize insertion costs
 *
 * EXAMPLE
 *   CSTL_VECTOR(int);
 *   vector_int v;
 *   vector_int_init(&v);
 *   vector_int_push_back(&v, 42);
 *   printf("%d\n", *vector_int_back(&v));
 *   vector_int_destroy(&v);
 */

#define CSTL_VECTOR(type) \
typedef struct vector_##type vector_##type; \
\
struct vector_##type { \
    type* data; \
    size_t size; \
    size_t capacity; \
}; \
\
static inline void vector_##type##_init(vector_##type* vector) { \
    vector->data = (type*)CSTL_MALLOC(CSTL_VECTOR_INITIAL_CAPACITY * sizeof(type)); \
    vector->size = 0; \
    vector->capacity = CSTL_VECTOR_INITIAL_CAPACITY; \
} \
\
static inline void vector_##type##_destroy(vector_##type* vector) { \
    if (vector) { \
        if (vector->data) { \
            CSTL_FREE(vector->data); \
            /* NOTE: If the vector holds pointers to dynamically allocated memory, you should call the destructor for each element before freeing the data array. */ \
            vector->data = NULL; \
        } \
        vector->size = 0; \
        vector->capacity = 0; \
    } \
} \
static inline int vector_##type##_reserve(vector_##type* vector, size_t n) { \
    CSTL_CHECK(!vector, "reserve: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
\
    size_t target_capacity = n; \
    if (vector->capacity == 0 && target_capacity == 0) { \
        target_capacity = CSTL_VECTOR_INITIAL_CAPACITY; \
    } \
    \
    if (target_capacity < vector->size) { \
        target_capacity = vector->size; \
    } \
\
    if (target_capacity > vector->capacity) { \
        void* ptr = CSTL_REALLOC(vector->data, target_capacity * sizeof(type)); \
        CSTL_CHECK(!ptr, "reserve: Fail", CSTL_ERROR_ALLOCATION); \
        vector->data = (type*)ptr; \
        vector->capacity = target_capacity; \
    } \
    return CSTL_SUCCESS; \
} \
static inline int vector_##type##_push_back(vector_##type* vector, type d) { \
    CSTL_CHECK(!vector, "push_back: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    if(vector->size >= vector->capacity) { \
        if (vector_##type##_reserve(vector, vector->capacity * 2) != CSTL_SUCCESS) return CSTL_ERROR_ALLOCATION; \
    } \
    vector->data[vector->size++] = d; \
    return CSTL_SUCCESS; \
} \
static inline int vector_##type##_pop_back(vector_##type* vector) { \
    CSTL_CHECK(!vector, "pop_back: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    CSTL_CHECK(vector->size == 0, "pop_back: Empty", CSTL_ERROR_EMPTY); \
    vector->data[vector->size - 1] = (type){0}; /* Optional: Clear the last element */ \
    vector->size--; \
    return CSTL_SUCCESS; \
} \
static inline int vector_##type##_insert(vector_##type* vector, size_t i, type d) { \
    CSTL_CHECK(!vector, "insert: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    CSTL_CHECK(i > vector->size, "insert: Bounds", CSTL_ERROR_OUT_OF_BOUNDS); \
    if (vector->size >= vector->capacity) { \
        if (vector_##type##_reserve(vector, vector->capacity * 2) != CSTL_SUCCESS) return CSTL_ERROR_ALLOCATION; \
    } \
    memmove(vector->data + i + 1, vector->data + i, (vector->size - i) * sizeof(type)); \
    vector->data[i] = d; \
    vector->size++; \
    return CSTL_SUCCESS; \
} \
static inline int vector_##type##_erase(vector_##type* vector, size_t i) { \
    CSTL_CHECK(!vector, "erase: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    CSTL_CHECK(i >= vector->size, "erase: Bounds", CSTL_ERROR_OUT_OF_BOUNDS); \
    memmove(vector->data + i, vector->data + i + 1, (vector->size - i - 1) * sizeof(type)); \
    vector->size--; \
    return CSTL_SUCCESS; \
} \
static inline int vector_##type##_erase_range(vector_##type* vector, size_t s, size_t e) { \
    CSTL_CHECK(!vector, "erase_range: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    CSTL_CHECK(s > vector->size || e > vector->size || s > e, "erase_range: Invalid range", CSTL_ERROR_OUT_OF_BOUNDS); \
    if (s == e) return CSTL_SUCCESS; \
    memmove(vector->data + s, vector->data + e, (vector->size - e) * sizeof(type)); \
    vector->size -= (e - s); \
    return CSTL_SUCCESS; \
} \
static inline int vector_##type##_clear(vector_##type* vector) { \
    CSTL_CHECK(!vector, "clear: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    memset(vector->data, 0, vector->capacity * sizeof(type)); /* Optional: Clear all elements */ \
    vector->size = 0; \
    return CSTL_SUCCESS; \
} \
static inline int vector_##type##_copy(vector_##type* dst, vector_##type* src) { \
    CSTL_CHECK(!dst || !src, "copy: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    vector_##type##_clear(dst); \
    if (dst->capacity < src->size) { \
        if (vector_##type##_reserve(dst, src->size) != CSTL_SUCCESS) return CSTL_ERROR_ALLOCATION; \
    } \
    memcpy(dst->data, src->data, src->size * sizeof(type)); \
    dst->size = src->size; \
    return CSTL_SUCCESS; \
} \
static inline size_t vector_##type##_size(const vector_##type* vector) { \
    return vector ? vector->size : 0; \
} \
static inline size_t vector_##type##_capacity(const vector_##type* vector) { \
    return vector ? vector->capacity : 0; \
} \
static inline type* vector_##type##_at(const vector_##type* vector, size_t i) { \
    CSTL_CHECK_PTR_RET(!vector, "at: NULL"); \
    CSTL_CHECK_PTR_RET(i >= vector->size, "at: Bounds"); \
    return &vector->data[i]; \
} \
static inline type* vector_##type##_front(const vector_##type* vector) { \
    CSTL_CHECK_PTR_RET(!vector, "front: NULL"); \
    CSTL_CHECK_PTR_RET(vector->size == 0, "front: Empty"); \
    return &vector->data[0]; \
} \
static inline type* vector_##type##_back(const vector_##type* vector) { \
    CSTL_CHECK_PTR_RET(!vector, "back: NULL"); \
    CSTL_CHECK_PTR_RET(vector->size == 0, "back: Empty"); \
    return &vector->data[vector->size - 1]; \
} \
static inline void vector_##type##_sort(vector_##type* vector) { \
    if (vector) qsort(vector->data, vector->size, sizeof(type), compare_##type); \
    else { \
       if (!vector) CSTL_LOG("sort: NULL"); \
    } \
} \
static inline int vector_##type##_find(const vector_##type* vector, type val, size_t* idx) { \
    CSTL_CHECK(!vector, "find: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    for (size_t i = 0; i < vector->size; ++i) { \
        if (compare_##type(&vector->data[i], &val) == 0) { if(idx)*idx=i; return CSTL_SUCCESS; } \
    } \
    return CSTL_ERROR_NOT_FOUND; \
} \
static inline int vector_##type##_binary_search(const vector_##type* vector, type val, size_t* idx) { \
    CSTL_CHECK(!vector, "bin_search: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    void* r = bsearch(&val, vector->data, vector->size, sizeof(type), compare_##type); \
    if (r) { if(idx)*idx=(size_t)((type*)r - vector->data); return CSTL_SUCCESS; } \
    return CSTL_ERROR_NOT_FOUND; \
} \
static inline int vector_##type##_is_empty(const vector_##type* vector) { \
    return vector ? (vector->size == 0) : 1; \
} \

#endif /* CSTL_VECTOR_H */
