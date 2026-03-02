#ifndef CSTL_LIST_H
#define CSTL_LIST_H

#include "cstl_common.h"

#define CSTL_LIST(type) \
typedef struct list_node_##type { \
    type value; \
    struct list_node_##type* next; \
    struct list_node_##type* prev; \
} list_node_##type; \
\
typedef struct list_##type { \
    list_node_##type* head; \
    list_node_##type* tail; \
    size_t size; \
} list_##type; \
\
static inline void list_##type##_init(list_##type* list) { \
    CSTL_CHECK_VOID(!list, "init: NULL"); \
    list->head = NULL; \
    list->tail = NULL; \
    list->size = 0; \
} \
\
static inline void list_##type##_destroy(list_##type* list) { \
    CSTL_CHECK_VOID(!list, "destroy: NULL"); \
    list_node_##type* current = list->head; \
    while (current) { \
        list_node_##type* next = current->next; \
        CSTL_FREE(current); \
        current = next; \
    } \
    list->head = NULL; \
    list->tail = NULL; \
    list->size = 0; \
} \
\
static inline int list_##type##_push_back(list_##type* list, type value) { \
    CSTL_CHECK(!list, "push_back: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    list_node_##type* new_node = (list_node_##type*)CSTL_MALLOC(sizeof(list_node_##type)); \
    CSTL_CHECK(!new_node, "push_back: Malloc failed", CSTL_ERROR_ALLOCATION); \
    new_node->value = value; \
    new_node->next = NULL; \
    new_node->prev = list->tail; \
    if (list->tail) { \
        list->tail->next = new_node; \
    } else { \
        list->head = new_node; \
    } \
    list->tail = new_node; \
    list->size++; \
    return CSTL_SUCCESS; \
} \
\
static inline int list_##type##_push_front(list_##type* list, type value) { \
    CSTL_CHECK(!list, "push_front: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    list_node_##type* new_node = (list_node_##type*)CSTL_MALLOC(sizeof(list_node_##type)); \
    CSTL_CHECK(!new_node, "push_front: Malloc failed", CSTL_ERROR_ALLOCATION); \
    new_node->value = value; \
    new_node->prev = NULL; \
    new_node->next = list->head; \
    if (list->head) { \
        list->head->prev = new_node; \
    } else { \
        list->tail = new_node; \
    } \
    list->head = new_node; \
    list->size++; \
    return CSTL_SUCCESS; \
} \
\
static inline int list_##type##_pop_back(list_##type* list) { \
    CSTL_CHECK(!list, "pop_back: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    CSTL_CHECK(list->size == 0, "pop_back: Empty", CSTL_ERROR_EMPTY); \
    list_node_##type* old_tail = list->tail; \
    list->tail = old_tail->prev; \
    if (list->tail) { \
        list->tail->next = NULL; \
    } else { \
        list->head = NULL; \
    } \
    CSTL_FREE(old_tail); \
    list->size--; \
    return CSTL_SUCCESS; \
} \
\
static inline int list_##type##_pop_front(list_##type* list) { \
    CSTL_CHECK(!list, "pop_front: NULL", CSTL_ERROR_INVALID_ARGUMENT); \
    CSTL_CHECK(list->size == 0, "pop_front: Empty", CSTL_ERROR_EMPTY); \
    list_node_##type* old_head = list->head; \
    list->head = old_head->next; \
    if (list->head) { \
        list->head->prev = NULL; \
    } else { \
        list->tail = NULL; \
    } \
    CSTL_FREE(old_head); \
    list->size--; \
    return CSTL_SUCCESS; \
} \
\
static inline type* list_##type##_front(const list_##type* list) { \
    CSTL_CHECK_PTR_RET(!list || list->size == 0, "front: Empty or NULL"); \
    return &list->head->value; \
} \
\
static inline type* list_##type##_back(const list_##type* list) { \
    CSTL_CHECK_PTR_RET(!list || list->size == 0, "back: Empty or NULL"); \
    return &list->tail->value; \
} \
\
static inline size_t list_##type##_size(const list_##type* list) { \
    return list ? list->size : 0; \
} \
\
static inline int list_##type##_is_empty(const list_##type* list) { \
    return list ? (list->size == 0) : 1; \
} \
\
typedef struct list_iterator_##type { \
    list_node_##type* node; \
} list_iterator_##type; \
\
static inline list_iterator_##type list_##type##_begin(const list_##type* list) { \
    return (list_iterator_##type){list ? list->head : NULL}; \
} \
\
static inline list_iterator_##type list_##type##_end(const list_##type* list) { \
    (void)list; \
    return (list_iterator_##type){NULL}; \
} \
\
static inline void list_##type##_next(list_iterator_##type* it) { \
    if (it && it->node) it->node = it->node->next; \
} \
\
static inline type* list_##type##_deref(const list_iterator_##type* it) { \
    return (it && it->node) ? &it->node->value : NULL; \
}

#endif /* CSTL_LIST_H */