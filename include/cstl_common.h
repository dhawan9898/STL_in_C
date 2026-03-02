#ifndef CSTL_COMMON_H
#define CSTL_COMMON_H

#include <stdlib.h> 
#include <stdio.h> 
#include <stddef.h> 
#include <string.h> 

// ----------------------------------------------------------------------------- 
// Memory Management Macros
// ----------------------------------------------------------------------------- 
#ifndef CSTL_MALLOC
#define CSTL_MALLOC malloc
#endif

#ifndef CSTL_REALLOC
#define CSTL_REALLOC realloc
#endif

#ifndef CSTL_FREE
#define CSTL_FREE free
#endif

// ----------------------------------------------------------------------------- 
// Error Handling & Optimization Flags 
// ----------------------------------------------------------------------------- 

typedef enum { 
    CSTL_SUCCESS = 0, 
    CSTL_ERROR_ALLOCATION = -1, 
    CSTL_ERROR_INVALID_ARGUMENT = -2, 
    CSTL_ERROR_OUT_OF_BOUNDS = -3, 
    CSTL_ERROR_EMPTY = -4, 
    CSTL_ERROR_NOT_FOUND = -5 
} CstlError;

#ifndef CSTL_NO_LOG
#define CSTL_LOG(msg) fprintf(stderr, "[CSTL ERROR] %s\n", msg)
#else
#define CSTL_LOG(msg) do {} while(0)
#endif

#ifndef CSTL_NO_CHECKS
#define CSTL_CHECK(cond, msg, err) do { if (cond) { CSTL_LOG(msg); return err; } } while(0)
#define CSTL_CHECK_PTR_RET(cond, msg) do { if (cond) { CSTL_LOG(msg); return NULL; } } while(0)
#define CSTL_CHECK_VOID(cond, msg) do { if (cond) { CSTL_LOG(msg); return; } } while(0)
#else
#define CSTL_CHECK(cond, msg, err) do {} while(0)
#define CSTL_CHECK_PTR_RET(cond, msg) do {} while(0)
#define CSTL_CHECK_VOID(cond, msg) do {} while(0)
#endif

/* ----------------------------------------------------------------------------- */
/* Comparison Functions                                                           */
/* ----------------------------------------------------------------------------- */

/**
 * compare_int(a, b)
 * ------------------
 * Comparison function for `int` values used by `qsort`, `bsearch`, and search
 * algorithms. Implements the standard qsort comparator signature.
 *
 * @param a Pointer to first `int` value
 * @param b Pointer to second `int` value
 * @return Negative if *a < *b, zero if equal, positive if *a > *b
 */
int compare_int(const void* a, const void* b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

/**
 * compare_char(a, b)
 * ------------------
 * Comparison function for `char` values used by `qsort`, `bsearch`, and search
 * algorithms.
 *
 * @param a Pointer to first `char` value
 * @param b Pointer to second `char` value
 * @return Negative if *a < *b, zero if equal, positive if *a > *b
 */
int compare_char(const void* a, const void* b) {
    char ca = *(const char*)a;
    char cb = *(const char*)b;
    if (ca < cb) return -1;
    if (ca > cb) return 1;
    return 0;
}

/**
 * compare_double(a, b)
 * --------------------
 * Comparison function for `double` values. Uses safe three-way comparison
 * to avoid floating-point subtraction issues.
 *
 * @param a Pointer to first `double` value
 * @param b Pointer to second `double` value
 * @return Negative if *a < *b, zero if equal, positive if *a > *b
 */
int compare_double(const void* a, const void* b) {
    double da = *(const double*)a;
    double db = *(const double*)b;
    double diff = da - db;
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}

/**
 * compare_str(a, b)
 * -----------------
 * Comparison function for C strings (const char*). For use with qsort/bsearch
 * on arrays of string pointers.
 *
 * @param a Pointer to first string pointer
 * @param b Pointer to second string pointer
 * @return Result of strcmp on the dereferenced strings
 */
int compare_str(const void* a, const void* b) {
    const char* sa = *(const char* const*)a;
    const char* sb = *(const char* const*)b;
    return strcmp(sa, sb);
}

#endif /* CSTL_COMMON_H */