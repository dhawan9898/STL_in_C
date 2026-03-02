#include <stdio.h>
#include "cstl_set.h"

// Instantiate set for int
CSTL_SET(int)

// Comparison function for integers
int compare_ints(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

void print_set_info(set_int* s, const char* name) {
    printf("%s (size=%zu, is_empty=%d)\n", name, set_int_size(s), set_int_is_empty(s));
}

int main() {
    printf("=== SET TESTS ===\n\n");

    set_int s;
    set_int_init(&s, compare_ints);

    print_set_info(&s, "Initialized Set");

    printf("\n--- Inserting elements ---\n");
    set_int_insert(&s, 10);
    set_int_insert(&s, 20);
    set_int_insert(&s, 30); // Triggers left rotation
    set_int_insert(&s, 40);
    set_int_insert(&s, 50); // Triggers left rotation
    set_int_insert(&s, 25); // Triggers right-left rotation

    print_set_info(&s, "After insertions");

    printf("\n--- Checking contents ---\n");
    printf("Contains 10: %s\n", set_int_contains(&s, 10) ? "yes" : "no");
    printf("Contains 30: %s\n", set_int_contains(&s, 30) ? "yes" : "no");
    printf("Contains 99: %s\n", set_int_contains(&s, 99) ? "yes" : "no");

    // Test inserting a duplicate
    printf("\n--- Inserting duplicate ---\n");
    size_t size_before = set_int_size(&s);
    set_int_insert(&s, 20);
    size_t size_after = set_int_size(&s);
    printf("Size before: %zu, Size after: %zu (should be the same)\n", size_before, size_after);

    set_int_destroy(&s);
    print_set_info(&s, "\nAfter destruction");


    printf("\n=== SET TESTS COMPLETED SUCCESSFULLY ===\n");

    return 0;
}