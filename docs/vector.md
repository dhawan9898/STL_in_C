# Vector (cstl_vector.h)

A generic, type-safe dynamic array that provides O(1) amortized appends and O(n) insertions and removals.

## Features

- **Type-Safe Instantiation**: `CSTL_VECTOR(type)` creates a vector for any given type.
- **Automatic Capacity Growth**: The vector automatically doubles its storage capacity when it runs out of space, leading to amortized O(1) time for `push_back` operations.
- **Rich API**: Provides over 20 functions covering element access, modification, and algorithms like sorting and searching.
- **Initial Capacity**: Defaults to 4 elements but can be configured by defining `CSTL_VECTOR_INITIAL_CAPACITY`.

## API Reference

### Initialization
- `void vector_<type>_init(vector_<type>* v)`: Initializes a vector with default capacity.
- `void vector_<type>_destroy(vector_<type>* v)`: Frees the vector's internal storage. *Note: This does not free the elements themselves if they are pointers.*
- `int vector_<type>_reserve(vector_<type>* v, size_t n)`: Ensures the vector has enough capacity for at least `n` elements.
- `int vector_<type>_clear(vector_<type>* v)`: Removes all elements from the vector without deallocating memory.

### Insertion
- `int vector_<type>_push_back(vector_<type>* v, type d)`: Appends an element to the end of the vector.
- `int vector_<type>_insert(vector_<type>* v, size_t i, type d)`: Inserts an element at a specific index `i`, shifting subsequent elements.

### Removal
- `int vector_<type>_pop_back(vector_<type>* v)`: Removes the last element from the vector.
- `int vector_<type>_erase(vector_<type>* v, size_t i)`: Removes the element at a specific index `i`.
- `int vector_<type>_erase_range(vector_<type>* v, size_t s, size_t e)`: Removes a range of elements from index `s` to `e-1`.

### Access
- `type* vector_<type>_at(const vector_<type>* v, size_t i)`: Returns a pointer to the element at a specific index `i`.
- `type* vector_<type>_front(const vector_<type>* v)`: Returns a pointer to the first element.
- `type* vector_<type>_back(const vector_<type>* v)`: Returns a pointer to the last element.

### Properties
- `size_t vector_<type>_size(const vector_<type>* v)`: Returns the number of elements in the vector.
- `size_t vector_<type>_capacity(const vector_<type>* v)`: Returns the current storage capacity of the vector.
- `int vector_<type>_is_empty(const vector_<type>* v)`: Returns non-zero if the vector is empty.

### Algorithms
- `int vector_<type>_copy(vector_<type>* dst, vector_<type>* src)`: Creates a deep copy of a source vector.
- `void vector_<type>_sort(vector_<type>* v)`: Sorts the vector using the `compare_<type>` function.
- `int vector_<type>_find(const vector_<type>* v, type val, size_t* idx)`: Performs a linear search to find an element.
- `int vector_<type>_binary_search(const vector_<type>* v, type val, size_t* idx)`: Performs a binary search on a sorted vector.
