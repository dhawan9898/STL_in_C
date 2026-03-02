# Deque (cstl_deque.h)

A generic, type-safe deque (Double-Ended Queue) implemented with a circular buffer for O(1) amortized push and pop operations at both ends.

## Features

- **Type-Safe Instantiation**: `CSTL_DEQUE(type)` creates a deque for any given type.
- **Circular Buffer**: Allows for efficient, O(1) amortized operations at both the front and back.
- **Automatic Capacity Growth**: Automatically resizes to accommodate more elements.
- **Initial Capacity**: Defaults to 8 elements, configurable via `CSTL_DEQUE_INITIAL_CAPACITY`.

## API Reference

### Initialization
- `void deque_<type>_init(deque_<type>* d)`: Initializes a deque with a default capacity.
- `void deque_<type>_destroy(deque_<type>* d)`: Frees the deque's internal storage.
- `int deque_<type>_reserve(deque_<type>* d, size_t n)`: Ensures the deque has enough capacity for at least `n` elements.

### Insertion
- `int deque_<type>_push_front(deque_<type>* d, type val)`: Adds an element to the front of the deque.
- `int deque_<type>_push_back(deque_<type>* d, type val)`: Adds an element to the back of the deque.

### Removal
- `int deque_<type>_pop_front(deque_<type>* d)`: Removes the element from the front of the deque.
- `int deque_<type>_pop_back(deque_<type>* d)`: Removes the element from the back of the deque.

### Access
- `type* deque_<type>_front(const deque_<type>* d)`: Returns a pointer to the front element.
- `type* deque_<type>_back(const deque_<type>* d)`: Returns a pointer to the back element.
- `type* deque_<type>_at(const deque_<type>* d, size_t index)`: Returns a pointer to the element at a specific index.

### Properties
- `size_t deque_<type>_size(const deque_<type>* d)`: Returns the number of elements in the deque.
- `size_t deque_<type>_capacity(const deque_<type>* d)`: Returns the current storage capacity.
- `int deque_<type>_is_empty(const deque_<type>* d)`: Returns non-zero if the deque is empty.
