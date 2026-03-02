#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cstl_queue.h"

/* Instantiate queues for `int`, `double` and a string alias `str` */
CSTL_QUEUE(int)
CSTL_QUEUE(double)
typedef const char* str;
CSTL_QUEUE(str)

#define INITIAL_CAP 4
#define TEST_ENQUEUE_COUNT 20

// Helper to print queue state for reserve tests
static void print_reserve_test_queue(const queue_int* q, const char* msg) {
    printf("%s - Size: %zu, Capacity: %zu, Is Empty: %d\n",
           msg, queue_int_size(q), queue_int_capacity(q), queue_int_is_empty(q));
    if (!queue_int_is_empty(q)) {
        printf("  Elements: front is %d, back is %d\n", *queue_int_front(q), *queue_int_back(q));
    }
}

// Function to verify queue contents after operations for reserve tests
static int verify_queue_contents(queue_int* q, int start_val, int expected_count, const char* test_name) {
    printf("  Verifying %s: Expecting %d elements starting from %d\n", test_name, expected_count, start_val);
    if ((size_t)expected_count != queue_int_size(q)) {
        printf("    FAIL: %s - Expected size %d, got %zu\n", test_name, expected_count, queue_int_size(q));
        return 0;
    }
    for (int i = 0; i < expected_count; ++i) {
        int* val_ptr = queue_int_front(q);
        if (val_ptr == NULL || *val_ptr != (start_val + i)) {
            printf("    FAIL: %s - At position %d, expected %d, got %d\n", test_name, i, start_val + i, val_ptr ? *val_ptr : -1);
            return 0;
        }
        queue_int_dequeue(q);
    }
    printf("    PASS: %s - All elements verified.\n", test_name);
    return 1;
}

static int run_reserve_tests() {
    printf("\n=== QUEUE RESERVE TESTS ===\n\n");
    queue_int q;
    queue_int_init(&q);
    print_reserve_test_queue(&q, "Initial queue");

    // Test 1: Enqueue elements to trigger multiple reallocations and wrapping
    printf("\n--- Test 1: Enqueue to trigger reallocations ---\n");
    for (int i = 0; i < TEST_ENQUEUE_COUNT; ++i) {
        if (queue_int_enqueue(&q, i) != CSTL_SUCCESS) {
            printf("FAIL: Enqueue %d failed\n", i);
            return 1;
        }
    }
    print_reserve_test_queue(&q, "After initial enqueues");
    // All 20 elements (0-19) should be in the queue
    if (!verify_queue_contents(&q, 0, TEST_ENQUEUE_COUNT, "Initial enqueue contents")) return 1;
    printf("Queue empty after verification: Size: %zu, Capacity: %zu\n", queue_int_size(&q), queue_int_capacity(&q));
    
    // Re-fill the queue to test reserve with existing elements
    queue_int_init(&q); // Re-initialize as verify_queue_contents emptied it
    for (int i = 0; i < TEST_ENQUEUE_COUNT; ++i) {
        queue_int_enqueue(&q, i);
    }
    printf("\n--- Test 2: Reserve capacity larger than current ---\n");
    if (queue_int_reserve(&q, 100) != CSTL_SUCCESS) {
        printf("FAIL: Reserve to 100 failed\n");
        return 1;
    }
    print_reserve_test_queue(&q, "After reserving to 100");
    if (queue_int_capacity(&q) < 100) {
        printf("FAIL: Capacity after reserve is %zu, expected at least 100\n", queue_int_capacity(&q));
        return 1;
    }
    if (!verify_queue_contents(&q, 0, TEST_ENQUEUE_COUNT, "Contents after reserve larger")) return 1;

    // Test 3: Reserve when queue is wrapped
    printf("\n--- Test 3: Reserve when queue is wrapped ---\n");
    queue_int_init(&q);
    for (int i = 0; i < 3; ++i) queue_int_enqueue(&q, i); // 0, 1, 2
    queue_int_dequeue(&q); // remove 0 -> front is 1
    queue_int_enqueue(&q, 3); // 1, 2, 3
    queue_int_enqueue(&q, 4); // 1,2,3,4 (capacity grows to 8, buffer should unwrap)
    queue_int_enqueue(&q, 5); // 1,2,3,4,5
    print_reserve_test_queue(&q, "Queue with some elements, potentially wrapped");
    
    // Now reserve a much larger capacity. This should force unwrapping and reallocation.
    if (queue_int_reserve(&q, 50) != CSTL_SUCCESS) {
        printf("FAIL: Reserve to 50 failed for wrapped queue\n");
        return 1;
    }
    print_reserve_test_queue(&q, "After reserving wrapped queue to 50");
    if (queue_int_capacity(&q) < 50) {
        printf("FAIL: Capacity after reserve is %zu, expected at least 50\n", queue_int_capacity(&q));
        return 1;
    }
    // Expected elements: 1, 2, 3, 4, 5
    if (!verify_queue_contents(&q, 1, 5, "Contents after reserve wrapped")) return 1;

    // Test 4: Reserve capacity smaller than current
    printf("\n--- Test 4: Reserve capacity smaller than current ---\n");
    queue_int_init(&q);
    for (int i = 0; i < 10; ++i) queue_int_enqueue(&q, i); // size 10, cap 16
    print_reserve_test_queue(&q, "Before reserving to 5");
    size_t initial_cap = queue_int_capacity(&q);
    if (queue_int_reserve(&q, 5) != CSTL_SUCCESS) {
        printf("FAIL: Reserve to 5 failed\n");
        return 1;
    }
    print_reserve_test_queue(&q, "After reserving to 5");
    // Should not shrink below current size
    if (queue_int_capacity(&q) < queue_int_size(&q)) {
        printf("FAIL: Capacity %zu is less than size %zu after reserve\n", queue_int_capacity(&q), queue_int_size(&q));
        return 1;
    }
    if (queue_int_capacity(&q) != initial_cap) {
         printf("WARNING: Capacity changed from %zu to %zu when reserving smaller. This is OK.\n", initial_cap, queue_int_capacity(&q));
    }
    if (!verify_queue_contents(&q, 0, 10, "Contents after reserve smaller")) return 1;

    queue_int_destroy(&q);
    printf("\nAll queue reserve tests passed!\n");
    return 0; // Return 0 for success
}


int main(void) {
    printf("=== INT QUEUE TESTS ===\n\n");
    
    /* Test int queue */
    queue_int qi;
    queue_int_init(&qi);
    printf("Created empty queue, is_empty=%d, size=%zu\n", 
           queue_int_is_empty(&qi), queue_int_size(&qi));

    /* Test NULL enqueue (should fail) */
    int ret = queue_int_enqueue(NULL, 42);
    printf("Enqueue to NULL queue returned: %d (expected %d)\n", ret, CSTL_ERROR_INVALID_ARGUMENT);

    /* Enqueue elements and check return values */
    printf("\nEnqueueing 10, 20, 30, 40, 50...\n");
    for (int i = 1; i <= 5; ++i) {
        int res = queue_int_enqueue(&qi, i * 10);
        if (res != CSTL_SUCCESS) {
            printf("ERROR: enqueue failed with code %d\n", res);
        }
    }
    printf("After enqueueing 5 elements: size=%zu, capacity=%zu\n", 
           queue_int_size(&qi), queue_int_capacity(&qi));

    /* Front and back without removing */
    int* front = queue_int_front(&qi);
    int* back = queue_int_back(&qi);
    if (front && back) {
        printf("Front element: %d, Back element: %d\n", *front, *back);
    }

    /* Dequeue one and check front again */
    if (queue_int_dequeue(&qi) == CSTL_SUCCESS) {
        printf("Dequeued successfully, new size=%zu\n", queue_int_size(&qi));
        front = queue_int_front(&qi);
        if (front) printf("New front element: %d\n", *front);
    }

    /* Test dequeue_value */
    printf("\nTesting dequeue_value...\n");
    int val_out;
    if (queue_int_dequeue_value(&qi, &val_out) == CSTL_SUCCESS) {
        printf("Dequeued value: %d (expected 20), new size: %zu\n", val_out, queue_int_size(&qi));
    }
    
    /* Continue dequeuing all - demonstrates FIFO */
    printf("Dequeuing remaining elements (FIFO order): ");
    while (!queue_int_is_empty(&qi)) {
        int* f = queue_int_front(&qi);
        if (f) printf("%d ", *f);
        if (queue_int_dequeue(&qi) != CSTL_SUCCESS) {
            printf("\nERROR: dequeue failed\n");
            break;
        }
    }
    printf("\nAfter dequeuing all: is_empty=%d, size=%zu\n", 
           queue_int_is_empty(&qi), queue_int_size(&qi));

    /* Try to dequeue from empty queue (should error) */
    ret = queue_int_dequeue(&qi);
    printf("Dequeue from empty queue returned: %d (expected %d)\n", ret, CSTL_ERROR_EMPTY);

    /* Test front on empty queue */
    front = queue_int_front(&qi);
    printf("Front on empty queue returned: %s\n", front ? "pointer" : "NULL (expected)");

    /* Enqueue again - test wraparound with circular buffer */
    printf("\nEnqueueing 100, 200, 300, 400, 500, 600...\n");
    for (int i = 1; i <= 6; ++i) {
        queue_int_enqueue(&qi, i * 100);
    }
    printf("After enqueueing 6: size=%zu, capacity=%zu\n", queue_int_size(&qi), queue_int_capacity(&qi));

    /* Dequeue 2 then enqueue 2 more (tests circular behavior) */
    if (queue_int_dequeue(&qi) == CSTL_SUCCESS) printf("Dequeued one (100)\n");
    if (queue_int_dequeue(&qi) == CSTL_SUCCESS) printf("Dequeued one (200)\n");
    
    queue_int_enqueue(&qi, 700);
    queue_int_enqueue(&qi, 800);
    printf("After dequeue 2 + enqueue 2: size=%zu\n", queue_int_size(&qi));

    /* Print remaining elements in FIFO order */
    printf("Remaining elements (FIFO): ");
    while (!queue_int_is_empty(&qi)) {
        int* val = queue_int_front(&qi);
        if (val) printf("%d ", *val);
        queue_int_dequeue(&qi);
    }
    printf("\n");

    /* Test reserve */
    queue_int_enqueue(&qi, 1000);
    if (queue_int_reserve(&qi, 50) == CSTL_SUCCESS) {
        printf("Reserved capacity 50: new capacity=%zu\n", queue_int_capacity(&qi));
    }

    queue_int_destroy(&qi);
    printf("Queue destroyed.\n\n");

    /* ================ DOUBLE QUEUE TESTS ================ */
    printf("=== DOUBLE QUEUE TESTS ===\n\n");
    
    queue_double qd;
    queue_double_init(&qd);
    printf("Created empty double queue\n");

    double vals[] = {3.14, 2.71, 1.41, 1.73};
    printf("Enqueueing 3.14, 2.71, 1.41, 1.73...\n");
    for (size_t i = 0; i < sizeof(vals)/sizeof(vals[0]); ++i) {
        if (queue_double_enqueue(&qd, vals[i]) != CSTL_SUCCESS) {
            printf("ERROR: enqueue failed at index %zu\n", i);
        }
    }
    printf("After enqueueing 4 elements: size=%zu, capacity=%zu\n", 
           queue_double_size(&qd), queue_double_capacity(&qd));

    double* d_front = queue_double_front(&qd);
    double* d_back = queue_double_back(&qd);
    if (d_front && d_back) printf("Front: %.2f, Back: %.2f\n", *d_front, *d_back);

    /* Dequeue and check */
    if (queue_double_dequeue(&qd) == CSTL_SUCCESS) printf("Dequeued one, size=%zu\n", queue_double_size(&qd));
    if (queue_double_dequeue(&qd) == CSTL_SUCCESS) printf("Dequeued one, size=%zu\n", queue_double_size(&qd));

    d_front = queue_double_front(&qd);
    if (d_front) printf("New front element: %.2f\n", *d_front);

    /* Empty the queue */
    printf("Dequeueing all (FIFO order): ");
    while (!queue_double_is_empty(&qd)) {
        double* val = queue_double_front(&qd);
        if (val) printf("%.2f ", *val);
        if (queue_double_dequeue(&qd) != CSTL_SUCCESS) break;
    }
    printf("\nFinal size=%zu, is_empty=%d\n", queue_double_size(&qd), queue_double_is_empty(&qd));

    queue_double_destroy(&qd);
    printf("Queue destroyed.\n\n");

    /* ================ STRING QUEUE TESTS ================ */
    printf("=== STRING QUEUE TESTS ===\n\n");
    
    queue_str qs;
    queue_str_init(&qs);
    printf("Created empty string queue, is_empty=%d, size=%zu\n", 
           queue_str_is_empty(&qs), queue_str_size(&qs));

    /* Enqueue strings */
    const char* strings[] = {"first", "second", "third", "fourth"};
    printf("Enqueueing %zu strings...\n", sizeof(strings)/sizeof(strings[0]));
    for (size_t i = 0; i < sizeof(strings)/sizeof(strings[0]); ++i) {
        if (queue_str_enqueue(&qs, strings[i]) != CSTL_SUCCESS) {
            printf("ERROR: enqueue failed for string %zu\n", i);
        }
    }
    printf("After enqueueing: size=%zu, capacity=%zu\n", 
           queue_str_size(&qs), queue_str_capacity(&qs));

    /* Front and back */
    const char** s_front = queue_str_front(&qs);
    const char** s_back = queue_str_back(&qs);
    if (s_front && s_back) printf("Front: %s, Back: %s\n", *s_front, *s_back);

    /* Dequeue one and check */
    if (queue_str_dequeue(&qs) == CSTL_SUCCESS) {
        printf("Dequeued, new size=%zu\n", queue_str_size(&qs));
        s_front = queue_str_front(&qs);
        if (s_front) printf("New front string: %s\n", *s_front);
    }

    /* Dequeue all - demonstrates FIFO (should be second, third, fourth) */
    printf("Dequeueing all (FIFO order): ");
    while (!queue_str_is_empty(&qs)) {
        const char** item = queue_str_front(&qs);
        if (item) printf("%s ", *item);
        if (queue_str_dequeue(&qs) != CSTL_SUCCESS) {
            printf("\nERROR: dequeue failed\n");
            break;
        }
    }
    printf("\nFinal size=%zu\n", queue_str_size(&qs));

    /* Enqueue again and test multiple enqueue/dequeue cycles */
    queue_str_enqueue(&qs, "apple");
    queue_str_enqueue(&qs, "banana");
    queue_str_enqueue(&qs, "cherry");
    queue_str_dequeue(&qs);  /* Remove apple, front is now banana */
    queue_str_enqueue(&qs, "date");
    queue_str_enqueue(&qs, "elderberry");
    
    printf("\nAfter mixed operations: size=%zu\n", queue_str_size(&qs));
    printf("Remaining (FIFO): ");
    while (!queue_str_is_empty(&qs)) {
        const char** val = queue_str_front(&qs);
        if (val) printf("%s ", *val);
        queue_str_dequeue(&qs);
    }
    printf("\n");

    /* Try enqueueing to NULL queue */
    ret = queue_str_enqueue(NULL, "test");
    printf("Enqueue to NULL queue returned: %d (expected %d)\n", ret, CSTL_ERROR_INVALID_ARGUMENT);

    queue_str_destroy(&qs);
    printf("Queue destroyed.\n\n");

    // Run the reserve tests
    if (run_reserve_tests() != 0) {
        printf("=== RESERVE TESTS FAILED ===\n");
        return 1;
    }

    printf("=== ALL TESTS COMPLETED SUCCESSFULLY ===\n");
    return 0;
}
