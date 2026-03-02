# STL_in_C

A lightweight, type-safe C library providing generic data structures similar to C++ STL containers. Using macro-based templates, it delivers compile-time type checking without runtime overhead.

## Overview

**STL_in_C** implements standard container abstractions for C, enabling developers to write type-safe, reusable code without sacrificing control over memory layout or performance.

## Features

- **Type-Safe Generics**: Compile-time template instantiation via macros.
- **A-la-carte Headers**: Include only the data structures you need.
- **Comprehensive Operations**: Covers initialization, modification, access, and properties for all containers.
- **Error Handling**: Explicit error codes for invalid operations.
- **Customization**: Supports custom memory allocators and compile-time logging/check removal.
- **Zero-Overhead Abstractions**: No runtime dispatch or garbage collection.
- **Simple API**: Consistent, intuitive function naming and semantics.

## Data Structures

This library currently provides the following data structures:

- **[Vector](./docs/vector.md)**: A grow-able dynamic array.
- **[Stack](./docs/stack.md)**: A LIFO (Last-In-First-Out) container.
- **[Queue](./docs/queue.md)**: A FIFO (First-In-First-Out) circular buffer.
- **[Deque](./docs/deque.md)**: A double-ended queue implemented as a circular buffer.

## Project Structure

```
.
├── build/              # Compiled binaries
├── docs/               # Detailed documentation for each data structure
│   ├── deque.md
│   ├── queue.md
│   ├── stack.md
│   └── vector.md
├── include/            # Header files for all data structures
│   ├── cstl_common.h
│   ├── cstl_deque.h
│   ├── cstl_queue.h
│   ├── cstl_stack.h
│   └── cstl_vector.h
├── test/               # Test source files
│   ├── test_deque.c
│   ├── test_queue.c
│   ├── test_stack.c
│   └── test_vector.c
├── Makefile
└── README.md
```

## Build & Test

To build and run all tests, use the provided Makefile:

```bash
# Clean previous builds and run all tests
make clean && make test
```
The compiled test executables will be placed in the `build/` directory.

## Customization

### Memory Allocators

Override memory functions by defining these macros before including the library headers:

```c
#define CSTL_MALLOC custom_malloc
#define CSTL_REALLOC custom_realloc
#define CSTL_FREE custom_free
#include "cstl_vector.h" // or any other cstl header
```

### Error Logging

- Disable error logging: `#define CSTL_NO_LOG`
- Disable all runtime checks (use with caution): `#define CSTL_NO_CHECKS`

### Custom Types

To use custom types with algorithms like `sort` or `find`, you must provide a comparison function with the exact name `compare_<type>`.

```c
typedef struct { int id; char name[64]; } Person;

int compare_person(const void* a, const void* b) {
    const Person* pa = (const Person*)a;
    const Person* pb = (const Person*)b;
    return pa->id - pb->id;
}

// Now you can use sort with vector_Person
CSTL_VECTOR(Person);
```

## Performance Characteristics

All containers provide O(1) amortized insertion and removal at their ends. For more detailed performance information, please see the documentation for each data structure in the `docs/` folder.

## Limitations & Design Notes

- **No Iterators**: The library uses direct indexing or front/back accessors.
- **Manual Memory Management**: The caller is responsible for cleaning up any dynamically allocated elements (e.g., a vector of pointers).
- **Macro-Based Generics**: Code is generated for each instantiated type at compile time.
- **Single-Threaded**: No built-in synchronization; the caller must handle concurrency.

## License

This project is provided as-is for educational and practical use.

## Contributing

Report issues, suggest improvements, or submit pull requests via the repository.
