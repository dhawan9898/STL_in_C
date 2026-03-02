#include <stdio.h>
#include <string.h>
#include "cstl_list.h"

// Instantiate list for int and str
CSTL_LIST(int);
typedef const char* str;
CSTL_LIST(str);

int main() {
    printf("=== LIST TESTS ===\n\n");

    // Integer list tests
    list_int int_list;
    list_int_init(&int_list);

    printf("Initialized (size=%zu, is_empty=%d): [empty]\n", list_int_size(&int_list), list_int_is_empty(&int_list));

    list_int_push_back(&int_list, 10);
    list_int_push_back(&int_list, 20);
    list_int_push_front(&int_list, 0);
    list_int_push_front(&int_list, -10);

    printf("\n--- After pushing elements ---\n");
    printf("List (size=%zu): ", list_int_size(&int_list));
    list_iterator_int it;
    for (it = list_int_begin(&int_list); it.node != list_int_end(&int_list).node; list_int_next(&it)) {
        printf("%d ", *list_int_deref(&it));
    }
    printf("\n");

    printf("\n--- Accessing elements ---\n");
    printf("Front: %d (expected -10)\n", *list_int_front(&int_list));
    printf("Back: %d (expected 20)\n", *list_int_back(&int_list));

    list_int_pop_front(&int_list);
    list_int_pop_back(&int_list);

    printf("\n--- After popping elements ---\n");
    printf("List (size=%zu): ", list_int_size(&int_list));
    for (it = list_int_begin(&int_list); it.node != list_int_end(&int_list).node; list_int_next(&it)) {
        printf("%d ", *list_int_deref(&it));
    }
    printf("\n");

    list_int_destroy(&int_list);
    printf("\nInt list destroyed.\n");


    // String list tests
    list_str str_list;
    list_str_init(&str_list);

    printf("\n=== STRING LIST TESTS ===\n\n");
    list_str_push_back(&str_list, "world");
    list_str_push_front(&str_list, "hello");
    list_str_push_back(&str_list, "!");

    printf("String list (size=%zu): ", list_str_size(&str_list));
    list_iterator_str s_it;
    for (s_it = list_str_begin(&str_list); s_it.node != list_str_end(&str_list).node; list_str_next(&s_it)) {
        printf("%s ", *list_str_deref(&s_it));
    }
    printf("\n");

    printf("Front: %s, Back: %s\n", *list_str_front(&str_list), *list_str_back(&str_list));

    list_str_pop_front(&str_list);
    printf("After pop_front (size=%zu): ", list_str_size(&str_list));
    for (s_it = list_str_begin(&str_list); s_it.node != list_str_end(&str_list).node; list_str_next(&s_it)) {
        printf("%s ", *list_str_deref(&s_it));
    }
    printf("\n");

    list_str_destroy(&str_list);
    printf("\nString list destroyed.\n");

    printf("\n=== LIST TESTS COMPLETED SUCCESSFULLY ===\n");

    return 0;
}
