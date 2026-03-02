# Deque (`cstl_deque.h`)

A generic, type-safe deque (Double-Ended Queue) implemented with a circular buffer for O(1) amortized push and pop operations at both ends. It is created using the `CSTL_DEQUE(type)` macro.

## Performance

- **`push_front` / `push_back`**: Amortized O(1). Reallocation occurs when the capacity is full, which is an O(n) operation.
- **`pop_front` / `pop_back`**: O(1).
- **`front` / `back`**: O(1).
- **`at`**: O(1).
- **`reserve`**: O(n) if reallocation is needed.

## API Details

### Initialization

#### `deque_<type>_init`
Initializes a deque with a default capacity.

- **Signature**: `void deque_<type>_init(deque_<type>* d)`
- **Usage**:
  ```c
  CSTL_DEQUE(int);
  deque_int d;
  deque_int_init(&d);
  ```

#### `deque_<type>_destroy`
Frees the deque's internal storage. Does not handle freeing of pointer elements.

- **Signature**: `void deque_<type>_destroy(deque_<type>* d)`
- **Usage**:
  ```c
  deque_int_destroy(&d);
  ```

#### `deque_<type>_reserve`
Ensures the deque has capacity for at least `n` elements.

- **Signature**: `int deque_<type>_reserve(deque_<type>* d, size_t n)`
- **Usage**:
  ```c
  // Reserve space for 40 integers
  deque_int_reserve(&d, 40);
  ```

### Insertion

#### `deque_<type>_push_front`
Adds an element to the front of the deque.

- **Signature**: `int deque_<type>_push_front(deque_<type>* d, type val)`
- **Usage**:
  ```c
  deque_int_push_front(&d, 10);
  deque_int_push_front(&d, 5); // Deque: [5, 10]
  ```

#### `deque_<type>_push_back`
Adds an element to the back of the deque.

- **Signature**: `int deque_<type>_push_back(deque_<type>* d, type val)`
- **Usage**:
  ```c
  deque_int_push_back(&d, 20); // Deque: [5, 10, 20]
  ```

### Removal

#### `deque_<type>_pop_front`
Removes the element from the front of the deque.

- **Signature**: `int deque_<type>_pop_front(deque_<type>* d)`
- **Usage**:
  ```c
  deque_int_pop_front(&d); // Deque: [10, 20]
  ```

#### `deque_<type>_pop_back`
Removes the element from the back of the deque.

- **Signature**: `int deque_<type>_pop_back(deque_<type>* d)`
- **Usage**:
  ```c
  deque_int_pop_back(&d); // Deque: [10]
  ```

### Access

#### `deque_<type>_front`
Returns a pointer to the front element. Returns `NULL` if the deque is empty.

- **Signature**: `type* deque_<type>_front(const deque_<type>* d)`
- **Usage**:
  ```c
  int* front_val = deque_int_front(&d);
  if (front_val) {
      printf("Front element: %d\n", *front_val);
  }
  ```

#### `deque_<type>_back`
Returns a pointer to the back element. Returns `NULL` if the deque is empty.

- **Signature**: `type* deque_<type>_back(const deque_<type>* d)`
- **Usage**:
  ```c
  int* back_val = deque_int_back(&d);
  ```

#### `deque_<type>_at`
Returns a pointer to the element at a specific index. Index 0 is the front of the deque.

- **Signature**: `type* deque_<type>_at(const deque_<type>* d, size_t index)`
- **Usage**:
  ```c
  // Get the element at index 1
  int* element = deque_int_at(&d, 1);
  ```

### Properties

#### `deque_<type>_size`
Returns the number of elements in the deque.

- **Signature**: `size_t deque_<type>_size(const deque_<type>* d)`
- **Usage**:
  ```c
  size_t current_size = deque_int_size(&d);
  ```

#### `deque_<type>_capacity`
Returns the current storage capacity of the deque.

- **Signature**: `size_t deque_<type>_capacity(const deque_<type>* d)`
- **Usage**:
  ```c
  size_t current_capacity = deque_int_capacity(&d);
  ```

#### `deque_<type>_is_empty`
Returns non-zero if the deque is empty.

- **Signature**: `int deque_<type>_is_empty(const deque_<type>* d)`
- **Usage**:
  ```c
  if (!deque_int_is_empty(&d)) {
      // ...
  }
  ```

## Limitations

- **No Arbitrary Insertion/Deletion**: This implementation does not support insertion or deletion at arbitrary positions within the deque, only at the ends.
- **Macro-based Instantiation**: Can lead to code bloat if used with many different types.
- **No Automatic Shrinking**: Capacity is never automatically reduced.
- **Manual Memory Management**: The user is responsible for managing memory if the deque stores pointers.

## Future Enhancements

- **`pop_..._value` functions**: Add `pop_front_value` and `pop_back_value` to retrieve a value while removing it.
- **Shrink-to-fit**: A function to reclaim unused capacity.
- **Iterators**: A proper iterator system for more flexible element access and traversal.
- **Custom Allocators**: Support for user-provided memory allocators.