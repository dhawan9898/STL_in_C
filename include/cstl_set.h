#ifndef CSTL_SET_H
#define CSTL_SET_H

#include "cstl_common.h"

#define CSTL_SET(type) \
typedef struct set_node_##type { \
    type value; \
    struct set_node_##type* left; \
    struct set_node_##type* right; \
    int height; \
} set_node_##type; \
\
typedef struct set_##type { \
    set_node_##type* root; \
    size_t size; \
    int (*compare)(const void*, const void*); \
} set_##type; \
\
static inline int set_##type##_height(set_node_##type* node) { \
    return node ? node->height : 0; \
} \
\
static inline int set_##type##_max(int a, int b) { \
    return (a > b) ? a : b; \
} \
\
static inline set_node_##type* set_##type##_new_node(type value) { \
    set_node_##type* new_node = (set_node_##type*)CSTL_MALLOC(sizeof(set_node_##type)); \
    if (!new_node) return NULL; \
    new_node->value = value; \
    new_node->left = NULL; \
    new_node->right = NULL; \
    new_node->height = 1; \
    return new_node; \
} \
\
static inline set_node_##type* set_##type##_right_rotate(set_node_##type* y) { \
    set_node_##type* x = y->left; \
    set_node_##type* T2 = x->right; \
    x->right = y; \
    y->left = T2; \
    y->height = set_##type##_max(set_##type##_height(y->left), set_##type##_height(y->right)) + 1; \
    x->height = set_##type##_max(set_##type##_height(x->left), set_##type##_height(x->right)) + 1; \
    return x; \
} \
\
static inline set_node_##type* set_##type##_left_rotate(set_node_##type* x) { \
    set_node_##type* y = x->right; \
    set_node_##type* T2 = y->left; \
    y->left = x; \
    x->right = T2; \
    x->height = set_##type##_max(set_##type##_height(x->left), set_##type##_height(x->right)) + 1; \
    y->height = set_##type##_max(set_##type##_height(y->left), set_##type##_height(y->right)) + 1; \
    return y; \
} \
\
static inline int set_##type##_get_balance(set_node_##type* node) { \
    return node ? set_##type##_height(node->left) - set_##type##_height(node->right) : 0; \
} \
\
static inline set_node_##type* set_##type##_insert_node(set_node_##type* node, type value, int (*compare)(const void*, const void*), size_t* size) { \
    if (!node) { \
        set_node_##type* new_node = set_##type##_new_node(value); \
        if (new_node) (*size)++; \
        return new_node; \
    } \
    int cmp = compare(&value, &node->value); \
    if (cmp < 0) { \
        node->left = set_##type##_insert_node(node->left, value, compare, size); \
    } else if (cmp > 0) { \
        node->right = set_##type##_insert_node(node->right, value, compare, size); \
    } else { \
        return node; \
    } \
    node->height = 1 + set_##type##_max(set_##type##_height(node->left), set_##type##_height(node->right)); \
    int balance = set_##type##_get_balance(node); \
    if (balance > 1 && compare(&value, &node->left->value) < 0) { \
        return set_##type##_right_rotate(node); \
    } \
    if (balance < -1 && compare(&value, &node->right->value) > 0) { \
        return set_##type##_left_rotate(node); \
    } \
    if (balance > 1 && compare(&value, &node->left->value) > 0) { \
        node->left = set_##type##_left_rotate(node->left); \
        return set_##type##_right_rotate(node); \
    } \
    if (balance < -1 && compare(&value, &node->right->value) < 0) { \
        node->right = set_##type##_right_rotate(node->right); \
        return set_##type##_left_rotate(node); \
    } \
    return node; \
} \
\
static inline void set_##type##_init(set_##type* set, int (*compare)(const void*, const void*)) { \
    CSTL_CHECK_VOID(!set, "init: NULL"); \
    set->root = NULL; \
    set->size = 0; \
    set->compare = compare; \
} \
\
static inline int set_##type##_insert(set_##type* set, type value) { \
    CSTL_CHECK(!set || !set->compare, "insert: NULL or no compare function", CSTL_ERROR_INVALID_ARGUMENT); \
    size_t initial_size = set->size; \
    set->root = set_##type##_insert_node(set->root, value, set->compare, &set->size); \
    if (set->size > initial_size) { \
        return CSTL_SUCCESS; \
    } else if (!set->root && initial_size == 0) { \
        return CSTL_ERROR_ALLOCATION; \
    } else if (set->root && initial_size == set->size) { \
        return CSTL_SUCCESS; \
    } \
    return CSTL_SUCCESS; \
} \
\
static inline int set_##type##_contains(const set_##type* set, type value) { \
    CSTL_CHECK(!set || !set->compare, "contains: NULL or no compare function", 0); \
    set_node_##type* current = set->root; \
    while (current) { \
        int cmp = set->compare(&value, &current->value); \
        if (cmp < 0) { \
            current = current->left; \
        } else if (cmp > 0) { \
            current = current->right; \
        } else { \
            return 1; \
        } \
    } \
    return 0; \
} \
\
static inline void set_##type##_destroy_nodes(set_node_##type* node) { \
    if (node) { \
        set_##type##_destroy_nodes(node->left); \
        set_##type##_destroy_nodes(node->right); \
        CSTL_FREE(node); \
    } \
} \
\
static inline void set_##type##_destroy(set_##type* set) { \
    CSTL_CHECK_VOID(!set, "destroy: NULL"); \
    set_##type##_destroy_nodes(set->root); \
    set->root = NULL; \
    set->size = 0; \
} \
\
static inline size_t set_##type##_size(const set_##type* set) { \
    return set ? set->size : 0; \
} \
\
static inline int set_##type##_is_empty(const set_##type* set) { \
    return set ? (set->size == 0) : 1; \
}

#endif /* CSTL_SET_H */
