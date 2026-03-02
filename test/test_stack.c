#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cstl_stack.h"

/* Instantiate stacks for `int`, `double` and a string alias `str` */
CSTL_STACK(int)
CSTL_STACK(double)
typedef const char* str;
CSTL_STACK(str)

int main(void) {
    printf("=== INT STACK TESTS ===\n\n");
    
    /* Test int stack */
    stack_int si;
    stack_int_init(&si);
    printf("Created empty stack, is_empty=%d, size=%zu\n", 
           stack_int_is_empty(&si), stack_int_size(&si));

    /* Test NULL push (should fail) */
    int ret = stack_int_push(NULL, 42);
    printf("Push to NULL stack returned: %d (expected %d)\n", ret, CSTL_ERROR_INVALID_ARGUMENT);

    /* Push elements and check return values */
    printf("\nPushing 10, 20, 30, 40, 50...\n");
    for (int i = 1; i <= 5; ++i) {
        int res = stack_int_push(&si, i * 10);
        if (res != CSTL_SUCCESS) {
            printf("ERROR: push failed with code %d\n", res);
        }
    }
    printf("After pushing 5 elements: size=%zu, capacity=%zu\n", 
           stack_int_size(&si), stack_int_capacity(&si));

    /* Top without pop */
    int* top = stack_int_top(&si);
    if (top) {
        printf("Top element: %d\n", *top);
    } else {
        printf("ERROR: top returned NULL\n");
    }

    /* Pop one and check top again */
    if (stack_int_pop(&si) == CSTL_SUCCESS) {
        printf("Popped successfully, new size=%zu\n", stack_int_size(&si));
        top = stack_int_top(&si);
        if (top) printf("New top element: %d\n", *top);
    }

    /* Continue popping all */
    printf("Popping remaining elements: ");
    while (!stack_int_is_empty(&si)) {
        int* t = stack_int_top(&si);
        if (t) printf("%d ", *t);
        if (stack_int_pop(&si) != CSTL_SUCCESS) {
            printf("\nERROR: pop failed\n");
            break;
        }
    }
    printf("\nAfter popping all: is_empty=%d, size=%zu\n", 
           stack_int_is_empty(&si), stack_int_size(&si));

    /* Try to pop from empty stack (should error) */
    ret = stack_int_pop(&si);
    printf("Pop from empty stack returned: %d (expected %d)\n", ret, CSTL_ERROR_EMPTY);

    /* Push again */
    stack_int_push(&si, 100);
    stack_int_push(&si, 200);
    stack_int_push(&si, 300);
    printf("\nPushed 100, 200, 300: size=%zu\n", stack_int_size(&si));

    /* Test reserve */
    if (stack_int_reserve(&si, 50) == CSTL_SUCCESS) {
        printf("Reserved capacity 50: new capacity=%zu\n", stack_int_capacity(&si));
    }

    /* Test pop_value */
    printf("\nTesting pop_value...\n");
    int val_out;
    if (stack_int_pop_value(&si, &val_out) == CSTL_SUCCESS) {
        printf("Popped value: %d (expected 300), new size: %zu\n", val_out, stack_int_size(&si));
    }
    stack_int_pop_value(&si, &val_out);
    stack_int_pop_value(&si, &val_out);
    ret = stack_int_pop_value(&si, &val_out);
    printf("Pop_value on empty stack returned: %d (expected %d)\n", ret, CSTL_ERROR_EMPTY);


    stack_int_destroy(&si);
    printf("Stack destroyed.\n\n");

    /* ================ DOUBLE STACK TESTS ================ */
    printf("=== DOUBLE STACK TESTS ===\n\n");
    
    stack_double sd;
    stack_double_init(&sd);
    printf("Created empty double stack\n");

    double vals[] = {3.14, 2.71, 1.41, 1.73};
    printf("Pushing 3.14, 2.71, 1.41, 1.73...\n");
    for (size_t i = 0; i < sizeof(vals)/sizeof(vals[0]); ++i) {
        if (stack_double_push(&sd, vals[i]) != CSTL_SUCCESS) {
            printf("ERROR: push failed at index %zu\n", i);
        }
    }
    printf("After pushing 4 elements: size=%zu, capacity=%zu\n", 
           stack_double_size(&sd), stack_double_capacity(&sd));

    double* d_top = stack_double_top(&sd);
    if (d_top) printf("Top element: %.2f\n", *d_top);

    /* Pop and check */
    if (stack_double_pop(&sd) == CSTL_SUCCESS) printf("Popped one element, size=%zu\n", stack_double_size(&sd));
    if (stack_double_pop(&sd) == CSTL_SUCCESS) printf("Popped another, size=%zu\n", stack_double_size(&sd));

    d_top = stack_double_top(&sd);
    if (d_top) printf("New top element: %.2f\n", *d_top);

    /* Empty the stack */
    printf("Emptying stack: ");
    while (!stack_double_is_empty(&sd)) {
        double* val = stack_double_top(&sd);
        if (val) printf("%.2f ", *val);
        if (stack_double_pop(&sd) != CSTL_SUCCESS) break;
    }
    printf("\nFinal size=%zu, is_empty=%d\n", stack_double_size(&sd), stack_double_is_empty(&sd));

    /* Try top on empty */
    d_top = stack_double_top(&sd);
    printf("Top on empty stack returned: %s\n", d_top ? "pointer" : "NULL (expected)");

    stack_double_destroy(&sd);
    printf("Stack destroyed.\n\n");

    /* ================ STRING STACK TESTS ================ */
    printf("=== STRING STACK TESTS ===\n\n");
    
    stack_str ss;
    stack_str_init(&ss);
    printf("Created empty string stack, is_empty=%d, size=%zu\n", 
           stack_str_is_empty(&ss), stack_str_size(&ss));

    /* Push strings */
    const char* strings[] = {"world", "hello", "from", "C"};
    printf("Pushing %zu strings...\n", sizeof(strings)/sizeof(strings[0]));
    for (size_t i = 0; i < sizeof(strings)/sizeof(strings[0]); ++i) {
        if (stack_str_push(&ss, strings[i]) != CSTL_SUCCESS) {
            printf("ERROR: push failed for string %zu\n", i);
        }
    }
    printf("After pushing: size=%zu, capacity=%zu\n", 
           stack_str_size(&ss), stack_str_capacity(&ss));

    /* Top without pop */
    const char** s_top = stack_str_top(&ss);
    if (s_top) printf("Top string: %s\n", *s_top);

    /* Pop one and check */
    if (stack_str_pop(&ss) == CSTL_SUCCESS) {
        printf("Popped, new size=%zu\n", stack_str_size(&ss));
        s_top = stack_str_top(&ss);
        if (s_top) printf("New top string: %s\n", *s_top);
    }

    /* Pop all and demonstrate LIFO */
    printf("Popping all (LIFO order): ");
    while (!stack_str_is_empty(&ss)) {
        const char** item = stack_str_top(&ss);
        if (item) printf("%s ", *item);
        if (stack_str_pop(&ss) != CSTL_SUCCESS) {
            printf("\nERROR: pop failed\n");
            break;
        }
    }
    printf("\nFinal size=%zu\n", stack_str_size(&ss));

    /* Push again for more tests */
    stack_str_push(&ss, "apple");
    stack_str_push(&ss, "banana");
    stack_str_push(&ss, "cherry");
    printf("\nPushed 'apple', 'banana', 'cherry': size=%zu\n", stack_str_size(&ss));

    /* Try pushing to NULL stack */
    ret = stack_str_push(NULL, "test");
    printf("Push to NULL stack returned: %d (expected %d)\n", ret, CSTL_ERROR_INVALID_ARGUMENT);

    stack_str_destroy(&ss);
    printf("Stack destroyed.\n\n");

    printf("=== ALL TESTS COMPLETED SUCCESSFULLY ===\n");
    return 0;
}
