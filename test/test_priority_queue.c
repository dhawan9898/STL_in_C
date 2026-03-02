#include <stdio.h>
#include "cstl_priority_queue.h"

// Instantiate priority_queue for int
CSTL_PRIORITY_QUEUE(int)

// Comparison function for integers (max-heap)
int compare_ints_max(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

// Comparison function for integers (min-heap)
int compare_ints_min(const void* a, const void* b) {
    return -compare_ints_max(a, b);
}

void test_max_heap() {
    printf("=== MAX-HEAP TESTS ===\n");
    priority_queue_int pq;
    priority_queue_int_init(&pq, compare_ints_max);

    printf("Pushing 10, 20, 5, 15, 30\n");
    priority_queue_int_push(&pq, 10);
    priority_queue_int_push(&pq, 20);
    priority_queue_int_push(&pq, 5);
    priority_queue_int_push(&pq, 15);
    priority_queue_int_push(&pq, 30);

    printf("Size: %zu\n", priority_queue_int_size(&pq));
    printf("Top: %d (should be 30)\n", *priority_queue_int_top(&pq));

    printf("Popping elements: ");
    while (!priority_queue_int_is_empty(&pq)) {
        printf("%d ", *priority_queue_int_top(&pq));
        priority_queue_int_pop(&pq);
    }
    printf("\n");
    printf("Size after popping all: %zu\n\n", priority_queue_int_size(&pq));

    priority_queue_int_destroy(&pq);
}

void test_min_heap() {
    printf("=== MIN-HEAP TESTS ===\n");
    priority_queue_int pq;
    priority_queue_int_init(&pq, compare_ints_min);

    printf("Pushing 10, 20, 5, 15, 30\n");
    priority_queue_int_push(&pq, 10);
    priority_queue_int_push(&pq, 20);
    priority_queue_int_push(&pq, 5);
    priority_queue_int_push(&pq, 15);
    priority_queue_int_push(&pq, 30);

    printf("Size: %zu\n", priority_queue_int_size(&pq));
    printf("Top: %d (should be 5)\n", *priority_queue_int_top(&pq));

    printf("Popping elements: ");
    while (!priority_queue_int_is_empty(&pq)) {
        printf("%d ", *priority_queue_int_top(&pq));
        priority_queue_int_pop(&pq);
    }
    printf("\n");
    printf("Size after popping all: %zu\n\n", priority_queue_int_size(&pq));

    priority_queue_int_destroy(&pq);
}

int main() {
    test_max_heap();
    test_min_heap();

    printf("=== PRIORITY QUEUE TESTS COMPLETED SUCCESSFULLY ===\n");

    return 0;
}
