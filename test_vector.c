#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cstl_vector.h"

/* Instantiate vectors for `int`, `double` and a string alias `str` */
CSTL_VECTOR(int)
CSTL_VECTOR(double)
typedef const char* str;
CSTL_VECTOR(str)

/* Helper print functions */
static void print_int_vector(const vector_int* v) {
    printf("ints(size=%zu, cap=%zu):", vector_int_size(v), vector_int_capacity(v));
    for (size_t i = 0; i < vector_int_size(v); ++i) {
        printf(" %d", *vector_int_at(v, i));
    }
    printf("\n");
}

static void print_double_vector(const vector_double* v) {
    printf("doubles(size=%zu, cap=%zu):", vector_double_size(v), vector_double_capacity(v));
    for (size_t i = 0; i < vector_double_size(v); ++i) {
        printf(" %.2f", *vector_double_at(v, i));
    }
    printf("\n");
}

static void print_str_vector(const vector_str* v) {
    printf("strs(size=%zu, cap=%zu):", vector_str_size(v), vector_str_capacity(v));
    for (size_t i = 0; i < vector_str_size(v); ++i) {
        printf(" %s", *vector_str_at(v, i));
    }
    printf("\n");
}

int main(void) {
    /* ---------------- INT tests ---------------- */
    vector_int vi;
    vector_int_init(&vi);
    for (int i = 0; i < 10; ++i) {
        vector_int_push_back(&vi, i);
    }
    print_int_vector(&vi);

    /* test front/back/at */
    printf("front=%d back=%d at(4)=%d\n", *vector_int_front(&vi), *vector_int_back(&vi), *vector_int_at(&vi,4));

    /* insert and erase */
    vector_int_insert(&vi, 5, 99);
    printf("after insert 99 at 5: "); print_int_vector(&vi);
    vector_int_erase(&vi, 2);
    printf("after erase index 2: "); print_int_vector(&vi);
    vector_int_erase_range(&vi, 3, 6);
    printf("after erase_range 3..6: "); print_int_vector(&vi);

    /* copy and clear */
    vector_int vcopy;
    vector_int_init(&vcopy);
    vector_int_copy(&vcopy, &vi);
    printf("copied vector: "); print_int_vector(&vcopy);
    vector_int_clear(&vcopy);
    printf("cleared copy, is_empty=%d\n", vector_int_is_empty(&vcopy));

    /* reserve */
    vector_int_reserve(&vi, 32);
    printf("after reserve to 32: cap=%zu\n", vector_int_capacity(&vi));

    /* sort, find and binary_search */
    vector_int_sort(&vi);
    printf("after sort: "); print_int_vector(&vi);
    size_t idx;
    if (vector_int_find(&vi, 99, &idx) == CSTL_SUCCESS) {
        printf("found 99 at %zu\n", idx);
    }
    if (vector_int_binary_search(&vi, 99, &idx) == CSTL_SUCCESS) {
        printf("binary found 99 at %zu\n", idx);
    }

    while (!vector_int_is_empty(&vi)) {
        vector_int_pop_back(&vi);
    }
    printf("after popping all, is_empty=%d\n", vector_int_is_empty(&vi));
    vector_int_destroy(&vi);
    vector_int_destroy(&vcopy);

    /* ---------------- DOUBLE tests ---------------- */
    vector_double vd;
    vector_double_init(&vd);
    double arr[] = {3.14, 2.71, -1.0, 42.0, 0.0};
    for (size_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i) {
        vector_double_push_back(&vd, arr[i]);
    }
    printf("before sort: "); print_double_vector(&vd);
    vector_double_sort(&vd);
    printf("after sort: "); print_double_vector(&vd);
    double key = 2.71;
    if (vector_double_find(&vd, key, &idx) == CSTL_SUCCESS) {
        printf("found %.2f at %zu\n", key, idx);
    }
    if (vector_double_binary_search(&vd, key, &idx) == CSTL_SUCCESS) {
        printf("binary found %.2f at %zu\n", key, idx);
    }
    vector_double_destroy(&vd);

    /* ---------------- STRING tests ---------------- */
    vector_str vs;
    vector_str_init(&vs);
    vector_str_push_back(&vs, "apple");
    vector_str_push_back(&vs, "orange");
    vector_str_push_back(&vs, "banana");
    vector_str_push_back(&vs, "grape");
    printf("strings before sort: "); print_str_vector(&vs);
    vector_str_sort(&vs);
    printf("strings after sort: "); print_str_vector(&vs);
    if (vector_str_find(&vs, "banana", &idx) == CSTL_SUCCESS) {
        printf("found 'banana' at %zu\n", idx);
    }
    if (vector_str_binary_search(&vs, "banana", &idx) == CSTL_SUCCESS) {
        printf("binary found 'banana' at %zu\n", idx);
    }
    vector_str_erase(&vs, 1);
    printf("after erase index 1: "); print_str_vector(&vs);
    vector_str_clear(&vs);
    printf("after clear, is_empty=%d\n", vector_str_is_empty(&vs));
    vector_str_destroy(&vs);

    return 0;
}