# STL_in_C

A lightweight, type-safe C library providing generic data structures similar to C++ STL containers. Using macro-based templates, it delivers compile-time type checking without runtime overhead.

## Overview

**STL_in_C** implements standard container abstractions for C, enabling developers to write type-safe, reusable code without sacrificing control over memory layout or performance. The library currently provides dynamic array (`vector`), stack (`stack`), and queue (`queue`) with comprehensive operations.

## Features

- **Type-Safe Generics**: Compile-time template instantiation via macros
- **Dynamic Array (Vector)**: Grow-able array with O(1) amortized append and O(n) insert/erase
- **Stack (LIFO)**: Last-In-First-Out container with O(1) push/pop operations
- **Queue (FIFO)**: First-In-First-Out container with O(1) circular buffer enqueue/dequeue
- **Comprehensive Operations**: Push, pop, insert, erase, sort, search, copy, and more
- **Error Handling**: Explicit error codes for invalid operations
- **Custom Comparators**: Pluggable comparison functions for sorting and searching (vector)
- **Zero-Overhead Abstractions**: No runtime dispatch or garbage collection
- **Simple API**: Consistent, intuitive function naming and semantics

## Project Structure

```
.
├── cstl_common.h       # Common macros, error codes, and comparison functions
├── cstl_vector.h       # Generic dynamic array (vector) implementation
├── cstl_stack.h        # Generic LIFO stack implementation
├── cstl_queue.h        # Generic FIFO queue (circular buffer) implementation
├── test_vector.c       # Comprehensive test suite for vector
├── test_stack.c        # Comprehensive test suite for stack
├── test_queue.c        # Comprehensive test suite for queue
└── README.md           # This file
```

## Files

### cstl_common.h

Core utilities and infrastructure shared across all containers:

- **Memory Management**: Configurable allocation via `CSTL_MALLOC`, `CSTL_REALLOC`, `CSTL_FREE`
- **Error Codes**: 
  - `CSTL_SUCCESS` (0) — Operation succeeded
  - `CSTL_ERROR_ALLOCATION` — Memory allocation failed
  - `CSTL_ERROR_INVALID_ARGUMENT` — Invalid argument (NULL, missing comparator, etc.)
  - `CSTL_ERROR_OUT_OF_BOUNDS` — Index out of bounds
  - `CSTL_ERROR_EMPTY` — Operation on empty container
  - `CSTL_ERROR_NOT_FOUND` — Value not found in search
- **Comparison Functions**:
  - `compare_int(a, b)` — Compare two integers
  - `compare_double(a, b)` — Compare two doubles (safe three-way comparison)
  - `compare_str(a, b)` — Compare two C strings
- **Error Logging**: Compile-time configurable via `CSTL_NO_LOG` and `CSTL_NO_CHECKS`

### cstl_vector.h

Generic dynamic array with robust memory management:

- **Type-Safe Instantiation**: `CSTL_VECTOR(type)` creates a vector for any type
- **Automatic Capacity Growth**: Doubles capacity on overflow (amortized O(1) append)
- **Rich API**: 20+ operations covering access, modification, and algorithms
- **Initial Capacity**: 4 elements (configurable via `CSTL_VECTOR_INITIAL_CAPACITY`)

#### Vector Operations

| Category | Functions |
|----------|-----------|
| **Initialization** | `_init()`, `_destroy()`, `_clear()`, `_reserve()` |
| **Insertion** | `_push_back()`, `_insert()` |
| **Removal** | `_pop_back()`, `_erase()`, `_erase_range()` |
| **Access** | `_at()`, `_front()`, `_back()`, `_size()`, `_capacity()`, `_is_empty()` |
| **Algorithms** | `_copy()`, `_sort()`, `_find()`, `_binary_search()` |

### cstl_stack.h

Generic Last-In-First-Out (LIFO) stack with standalone implementation:

- **Type-Safe Instantiation**: `CSTL_STACK(type)` creates a stack for any type
- **Standalone Implementation**: No dependency on vector or other containers
- **Automatic Capacity Growth**: Doubles capacity on overflow (amortized O(1) push)
- **Proper Error Handling**: All operations validate arguments and return error codes
- **Initial Capacity**: 4 elements (configurable via `CSTL_STACK_INITIAL_CAPACITY`)

#### Stack Operations

| Category | Functions |
|----------|-----------|
| **Initialization** | `_init()`, `_destroy()`, `_reserve()` |
| **Stack Ops** | `_push()`, `_pop()`, `_top()` |
| **Properties** | `_size()`, `_capacity()`, `_is_empty()` |

Stack Characteristics:
- **LIFO Semantics**: Last item pushed is first item popped
- **Return Values**: All modifying operations return `CSTL_SUCCESS` or error codes
- **top()**: Returns pointer to top element without removing (returns NULL on empty)
- **pop()**: Removes top element and returns error code (not the value)

### cstl_queue.h

Generic First-In-First-Out (FIFO) queue with circular buffer implementation:

- **Type-Safe Instantiation**: `CSTL_QUEUE(type)` creates a queue for any type
- **Circular Buffer**: Efficient O(1) enqueue and dequeue with automatic wraparound
- **Standalone Implementation**: No dependency on vector or other containers
- **Automatic Capacity Growth**: Doubles capacity on overflow (amortized O(1) enqueue)
- **Proper Error Handling**: All operations validate arguments and return error codes
- **Initial Capacity**: 4 elements (configurable via `CSTL_QUEUE_INITIAL_CAPACITY`)

#### Queue Operations

| Category | Functions |
|----------|-----------|
| **Initialization** | `_init()`, `_destroy()`, `_reserve()` |
| **Queue Ops** | `_enqueue()`, `_dequeue()`, `_front()`, `_back()` |
| **Properties** | `_size()`, `_capacity()`, `_is_empty()` |

Queue Characteristics:
- **FIFO Semantics**: First item enqueued is first item dequeued
- **Return Values**: All modifying operations return `CSTL_SUCCESS` or error codes
- **front()/back()**: Return pointers to elements without removing (return NULL on empty)
- **dequeue()**: Removes front element and returns error code (not the value)
- **Circular Buffer**: Uses modulo arithmetic internally for efficient O(1) operations

## Quick Start

### Build & Test

```bash
cd /workspaces/STL_in_C
gcc test_vector.c -o test && ./test
```

### Basic Usage Example

```c
#include "cstl_vector.h"

// Instantiate a vector for integers
CSTL_VECTOR(int);

int main(void) {
    // Initialize
    vector_int v;
    vector_int_init(&v);

    // Add elements
    for (int i = 1; i <= 5; ++i) {
        vector_int_push_back(&v, i * 10);
    }

    // Access elements
    printf("First: %d, Last: %d, Size: %zu\n",
           *vector_int_at(&v, 0),
           *vector_int_back(&v),
           vector_int_size(&v));

    // Modify: insert and erase
    vector_int_insert(&v, 2, 99);
    vector_int_erase(&v, 0);

    // Print
    for (size_t i = 0; i < vector_int_size(&v); ++i) {
        printf("%d ", *vector_int_at(&v, i));
    }
    printf("\n");

    // Cleanup
    vector_int_destroy(&v);
    return 0;
}
```

### Working with Strings

```c
#include "cstl_vector.h"

// Create a string alias for vectors of string pointers
typedef const char* str;
CSTL_VECTOR(str);

int main(void) {
    vector_str words;
    vector_str_init(&words);

    // Add strings
    vector_str_push_back(&words, "apple");
    vector_str_push_back(&words, "cherry");
    vector_str_push_back(&words, "banana");

    // Sort alphabetically
    vector_str_sort(&words);

    // Search
    size_t idx;
    if (vector_str_binary_search(&words, "banana", &idx) == CSTL_SUCCESS) {
        printf("Found at index: %zu\n", idx);
    }

    vector_str_destroy(&words);
    return 0;
}
```

### Working with Stacks

```c
#include "cstl_stack.h"

// Instantiate a stack for integers
CSTL_STACK(int);

// Or for strings
typedef const char* str;
CSTL_STACK(str);

int main(void) {
    // Create and initialize stack
    stack_int s;
    stack_int_init(&s);

    // Push elements (check return value)
    if (stack_int_push(&s, 10) != CSTL_SUCCESS) {
        printf("Push failed\n");
        return 1;
    }
    stack_int_push(&s, 20);
    stack_int_push(&s, 30);

    // Access top without removing
    int* top = stack_int_top(&s);
    if (top) printf("Top: %d\n", *top);  // Prints: 30

    // Pop elements (LIFO)
    while (!stack_int_is_empty(&s)) {
        int* val = stack_int_top(&s);
        if (val) printf("%d ", *val);  // Prints: 30 20 10
        stack_int_pop(&s);
    }

    // Cleanup
    stack_int_destroy(&s);
    return 0;
}
```

### Working with Queues

```c
#include "cstl_queue.h"

// Instantiate a queue for integers
CSTL_QUEUE(int);

// Or for strings
typedef const char* str;
CSTL_QUEUE(str);

int main(void) {
    // Create and initialize queue
    queue_int q;
    queue_int_init(&q);

    // Enqueue elements (add to back)
    if (queue_int_enqueue(&q, 10) != CSTL_SUCCESS) {
        printf("Enqueue failed\n");
        return 1;
    }
    queue_int_enqueue(&q, 20);
    queue_int_enqueue(&q, 30);

    // Access front and back without removing
    int* front = queue_int_front(&q);
    int* back = queue_int_back(&q);
    if (front && back) printf("Front: %d, Back: %d\n", *front, *back);  // Prints: 10, 30

    // Dequeue elements (FIFO - first in, first out)
    while (!queue_int_is_empty(&q)) {
        int* val = queue_int_front(&q);
        if (val) printf("%d ", *val);  // Prints: 10 20 30
        queue_int_dequeue(&q);
    }

    // Cleanup
    queue_int_destroy(&q);
    return 0;
}
```

## API Reference

### Vector Initialization

```c
void vector_<type>_init(vector_<type>* v)
```
Initialize a vector with default capacity (4 elements). Sets size to 0.

```c
void vector_<type>_destroy(vector_<type>* v)
```
Free internal storage. *Does not free elements if they are pointers to dynamically allocated memory.*

### Insertion Operations

```c
int vector_<type>_push_back(vector_<type>* v, type d)
```
Append element to end. Returns `CSTL_SUCCESS` or error code.

```c
int vector_<type>_insert(vector_<type>* v, size_t i, type d)
```
Insert element at index `i`. Shifts following elements right.

### Removal Operations

```c
int vector_<type>_pop_back(vector_<type>* v)
```
Remove last element. Returns error if vector is empty.

```c
int vector_<type>_erase(vector_<type>* v, size_t i)
```
Remove element at index `i`. Shifts following elements left.

```c
int vector_<type>_erase_range(vector_<type>* v, size_t s, size_t e)
```
Remove range [s, e). Half-open interval — erases indices s through e-1.

### Access Operations

```c
type* vector_<type>_at(const vector_<type>* v, size_t i)
```
Get pointer to element at index `i`. Returns NULL on bounds error or NULL vector.

```c
type* vector_<type>_front(const vector_<type>* v)
type* vector_<type>_back(const vector_<type>* v)
```
Get pointer to first/last element. Returns NULL if vector is empty.

```c
size_t vector_<type>_size(const vector_<type>* v)
size_t vector_<type>_capacity(const vector_<type>* v)
```
Query current size and allocated capacity.

```c
int vector_<type>_is_empty(const vector_<type>* v)
```
Check if vector is empty. Returns non-zero if empty or NULL.

### Algorithms

```c
int vector_<type>_copy(vector_<type>* dst, vector_<type>* src)
```
Deep copy `src` into `dst`, resizing `dst` if necessary.

```c
int vector_<type>_reserve(vector_<type>* v, size_t n)
```
Ensure capacity is at least `n` elements. Does not change size.

```c
void vector_<type>_sort(vector_<type>* v)
```
Sort elements using `qsort` and `compare_<type>` function.

```c
int vector_<type>_find(const vector_<type>* v, type val, size_t* idx)
```
Linear search for `val`. If found, sets `*idx` and returns `CSTL_SUCCESS`.

```c
int vector_<type>_binary_search(const vector_<type>* v, type val, size_t* idx)
```
Binary search for `val`. Vector must be sorted. Returns success code.

```c
int vector_<type>_clear(vector_<type>* v)
```
Remove all elements without deallocating storage. Resets size to 0.

### Stack Operations

```c
void stack_<type>_init(stack_<type>* s)
```
Initialize stack with default capacity (4 elements). Sets size to 0.

```c
void stack_<type>_destroy(stack_<type>* s)
```
Free internal storage and reset state.

```c
int stack_<type>_push(stack_<type>* s, type val)
```
Push element onto stack. Returns `CSTL_SUCCESS` or error code (e.g., `CSTL_ERROR_ALLOCATION`).

```c
int stack_<type>_pop(stack_<type>* s)
```
Pop top element from stack. Returns `CSTL_SUCCESS`, or `CSTL_ERROR_EMPTY` if stack is empty.

```c
type* stack_<type>_top(const stack_<type>* s)
```
Get pointer to top element without removing. Returns NULL if stack is empty or argument is NULL.

```c
size_t stack_<type>_size(const stack_<type>* s)
size_t stack_<type>_capacity(const stack_<type>* s)
```
Query current size and allocated capacity.

```c
int stack_<type>_is_empty(const stack_<type>* s)
```
Check if stack is empty. Returns non-zero if empty or NULL.

```c
int stack_<type>_reserve(stack_<type>* s, size_t n)
```
Reserve capacity for at least `n` elements. Does not change size. Returns `CSTL_SUCCESS` or error code.

### Queue Operations

```c
void queue_<type>_init(queue_<type>* q)
```
Initialize queue with default capacity (4 elements). Sets size to 0. Uses circular buffer internally.

```c
void queue_<type>_destroy(queue_<type>* q)
```
Free internal storage and reset state.

```c
int queue_<type>_enqueue(queue_<type>* q, type val)
```
Add element to back of queue. Returns `CSTL_SUCCESS` or error code (e.g., `CSTL_ERROR_ALLOCATION`).

```c
int queue_<type>_dequeue(queue_<type>* q)
```
Remove element from front of queue. Returns `CSTL_SUCCESS`, or `CSTL_ERROR_EMPTY` if queue is empty.

```c
type* queue_<type>_front(const queue_<type>* q)
type* queue_<type>_back(const queue_<type>* q)
```
Get pointers to front/back elements without removing. Returns NULL if queue is empty or argument is NULL.

```c
size_t queue_<type>_size(const queue_<type>* q)
size_t queue_<type>_capacity(const queue_<type>* q)
```
Query current size and allocated capacity.

```c
int queue_<type>_is_empty(const queue_<type>* q)
```
Check if queue is empty. Returns non-zero if empty or NULL.

```c
int queue_<type>_reserve(queue_<type>* q, size_t n)
```
Reserve capacity for at least `n` elements. Compacts circular buffer if needed. Returns `CSTL_SUCCESS` or error code.

## Customization

### Memory Allocators

Override memory functions before including headers:

```c
#define CSTL_MALLOC custom_malloc
#define CSTL_REALLOC custom_realloc
#define CSTL_FREE custom_free
#include "cstl_vector.h"
#include "cstl_stack.h"
#include "cstl_queue.h"
```

### Error Logging

Disable error logging:

```c
#define CSTL_NO_LOG
#include "cstl_vector.h"
```

Disable all runtime checks (use with caution):

```c
#define CSTL_NO_CHECKS
#include "cstl_vector.h"
```

### Custom Types

Provide a comparison function for your type:

```c
typedef struct { int id; char name[64]; } Person;

int compare_person(const void* a, const void* b) {
    const Person* pa = (const Person*)a;
    const Person* pb = (const Person*)b;
    return pa->id - pb->id;
}

CSTL_VECTOR(Person);
```

## Testing

The test suite includes:

**Vector Tests** (`test_vector.c`):
- Integer vectors: push, pop, insert, erase, sort, search
- Double vectors: floating-point values and comparisons
- String vectors: string operations and lexicographic sorting
- Edge cases: empty vectors, boundary conditions, capacity growth
- All API functions exercised for each type

**Stack Tests** (`test_stack.c`):
- Integer stacks: push, pop, top, LIFO semantics
- Double stacks: floating-point stack operations
- String stacks: string stack operations
- Error handling: NULL argument checks, empty stack operations
- Return value validation for all operations
- Capacity growth and reserve operations

**Queue Tests** (`test_queue.c`):
- Integer queues: enqueue, dequeue, front, back, FIFO semantics
- Double queues: floating-point queue operations
- String queues: string queue operations
- Error handling: NULL argument checks, empty queue operations
- Return value validation for all operations
- Circular buffer behavior and wraparound operations
- Capacity growth and reserve operations with buffer compaction

Build and run all tests:

```bash
# Vector tests
gcc test_vector.c -o test_vector && ./test_vector

# Stack tests
gcc test_stack.c -o test_stack && ./test_stack

# Queue tests
gcc test_queue.c -o test_queue && ./test_queue
```

## Performance Characteristics

### Vector Operations

| Operation | Time Complexity | Space |
|-----------|-----------------|-------|
| `push_back` | O(1) amortized | O(n) |
| `pop_back` | O(1) | — |
| `insert` | O(n) | — |
| `erase` | O(n) | — |
| `access` (at, front, back) | O(1) | — |
| `sort` | O(n log n) | O(log n) |
| `find` | O(n) | — |
| `binary_search` | O(log n) | — |

### Stack Operations

| Operation | Time Complexity | Space |
|-----------|-----------------|-------|
| `push` | O(1) amortized | O(n) |
| `pop` | O(1) | — |
| `top` | O(1) | — |
| `is_empty` / `size` | O(1) | — |
| `reserve` | O(n) | — |

### Queue Operations

| Operation | Time Complexity | Space |
|-----------|-----------------|-------|
| `enqueue` | O(1) amortized | O(n) |
| `dequeue` | O(1) | — |
| `front` / `back` | O(1) | — |
| `is_empty` / `size` | O(1) | — |
| `reserve` | O(n) | — |

## Limitations & Design Notes

**Vector & Stack & Queue Shared:**
- **No Iterators**: Direct array indexing is the primary access pattern
- **Manual Memory Management**: Caller is responsible for cleanup (including elements that are pointers)
- **Macro-Based Generics**: Creates code for each instantiated type at compile time
- **Single-Threaded**: No built-in synchronization; caller must handle concurrency
- **Type Safety**: Enforced at compile time; no type erasure
- **Standalone**: Stack and Queue have no dependencies on other containers

**Stack Specific:**
- **LIFO Only**: Strictly Last-In-First-Out behavior; no random access
- **Return Values**: All operations explicitly return error codes for proper validation

**Queue Specific:**
- **FIFO Only**: Strictly First-In-First-Out behavior; no random access
- **Circular Buffer**: Uses efficient modulo arithmetic internally for O(1) operations
- **Return Values**: All operations explicitly return error codes for proper validation
- **Buffer Compaction**: Reserve operation compacts circular buffer if needed

**Vector Specific:**
- **Random Access**: Full indexing and search capabilities
- **Rich Algorithms**: Sorting, searching (linear and binary), copying
- **Flexible Modifications**: Insert at arbitrary positions, erase ranges

## License

This project is provided as-is for educational and practical use.

## Contributing

Report issues, suggest improvements, or submit pull requests via the repository.