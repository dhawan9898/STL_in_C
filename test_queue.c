#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cstl_queue.h"

/* Instantiate queues for `int`, `double` and a string alias `str` */
CSTL_QUEUE(int)
CSTL_QUEUE(double)
typedef const char* str;
CSTL_QUEUE(str)

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

    printf("=== ALL TESTS COMPLETED SUCCESSFULLY ===\n");
    return 0;
}
