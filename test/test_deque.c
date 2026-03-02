#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cstl_deque.h"

// Instantiate deque for int
CSTL_DEQUE(int)

static void print_deque(const deque_int* d, const char* msg) {
    printf("%s (size=%zu, cap=%zu): ", msg, deque_int_size(d), deque_int_capacity(d));
    if (deque_int_is_empty(d)) {
        printf("[empty]\n");
        return;
    }
    for (size_t i = 0; i < deque_int_size(d); ++i) {
        printf("%d ", *deque_int_at(d, i));
    }
    printf("\n");
}

int main(void) {
    printf("=== DEQUE TESTS ===\n\n");

    deque_int d;
    deque_int_init(&d);
    print_deque(&d, "Initialized");

    // Test push_back and push_front
    printf("\n--- Pushing elements ---\n");
    deque_int_push_back(&d, 10);
    deque_int_push_back(&d, 20);
    deque_int_push_front(&d, 0);
    deque_int_push_front(&d, -10);
    print_deque(&d, "After push_back/front"); // Expected: -10 0 10 20

    // Test front, back, and at
    printf("\n--- Accessing elements ---\n");
    printf("Front: %d (expected -10)\n", *deque_int_front(&d));
    printf("Back: %d (expected 20)\n", *deque_int_back(&d));
    printf("At index 2: %d (expected 10)\n", *deque_int_at(&d, 2));

    // Test pop_front and pop_back
    printf("\n--- Popping elements ---\n");
    deque_int_pop_front(&d);
    print_deque(&d, "After pop_front"); // Expected: 0 10 20
    deque_int_pop_back(&d);
    print_deque(&d, "After pop_back"); // Expected: 0 10

    // Test capacity growth
    printf("\n--- Testing capacity growth ---\n");
    // size is 2, capacity is 8
    for(int i = 0; i < 10; ++i) {
        deque_int_push_back(&d, 100 + i*10);
    }
    print_deque(&d, "After pushing 10 more elements");
    if (deque_int_capacity(&d) >= 12) {
        printf("Capacity grew as expected.\n");
    } else {
        printf("FAIL: Capacity did not grow correctly.\n");
    }

    // Test wrapping behavior
    printf("\n--- Testing wrapping behavior ---\n");
    deque_int_destroy(&d);
    deque_int_init(&d);
    for(int i=0; i<6; ++i) deque_int_push_back(&d, i); // 0 1 2 3 4 5
    print_deque(&d, "Filled with 6 elements");
    for(int i=0; i<3; ++i) deque_int_pop_front(&d); // 3 4 5
    print_deque(&d, "Popped 3 from front");
    for(int i=0; i<5; ++i) deque_int_push_back(&d, 10+i); // 3 4 5 10 11 12 13 14 (should reallocate)
    print_deque(&d, "Pushed 5 to back");
    deque_int_push_front(&d, 99);
    print_deque(&d, "Pushed 99 to front");

    printf("\nFinal state check:\n");
    printf("Front: %d, Back: %d, Size: %zu\n", *deque_int_front(&d), *deque_int_back(&d), deque_int_size(&d));
    printf("Element at index 3: %d\n", *deque_int_at(&d, 3));


    deque_int_destroy(&d);
    printf("\nDeque destroyed.\n");

    printf("\n=== DEQUE TESTS COMPLETED SUCCESSFULLY ===\n");
    return 0;
}
