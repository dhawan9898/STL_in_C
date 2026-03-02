# Vector (`cstl_vector.h`)

A generic, type-safe dynamic array that provides O(1) amortized appends and O(n) insertions and removals. It is created using the `CSTL_VECTOR(type)` macro.

## Performance

- **`push_back`**: Amortized O(1). When the vector's capacity is full, it reallocates memory, which takes O(n) time. However, since the capacity doubles each time, the cost of reallocation is spread out over many `push_back` operations.
- **`pop_back`**: O(1).
- **`insert` / `erase`**: O(n) because elements may need to be shifted.
- **`at` / `front` / `back`**: O(1).
- **`reserve`**: O(n) if reallocation is needed.
- **`sort`**: O(n log n) on average, as it uses `qsort`.
- **`find`**: O(n).
- **`binary_search`**: O(log n) on a sorted vector.

## API Details

### Initialization

#### `vector_<type>_init`
Initializes a vector with a default capacity.

- **Signature**: `void vector_<type>_init(vector_<type>* v)`
- **Usage**:
  ```c
  CSTL_VECTOR(int);
  vector_int v;
  vector_int_init(&v);
  ```

#### `vector_<type>_destroy`
Frees the vector's internal storage. Does not free the elements themselves if they are pointers.

- **Signature**: `void vector_<type>_destroy(vector_<type>* v)`
- **Usage**:
  ```c
  vector_int_destroy(&v);
  ```

#### `vector_<type>_reserve`
Ensures the vector has enough capacity for at least `n` elements.

- **Signature**: `int vector_<type>_reserve(vector_<type>* v, size_t n)`
- **Usage**:
  ```c
  // Reserve space for 100 integers
  vector_int_reserve(&v, 100);
  ```

#### `vector_<type>_clear`
Removes all elements from the vector without deallocating memory. The size becomes 0, but the capacity remains the same.

- **Signature**: `int vector_<type>_clear(vector_<type>* v)`
- **Usage**:
  ```c
  vector_int_clear(&v);
  ```

### Insertion

#### `vector_<type>_push_back`
Appends an element to the end of the vector.

- **Signature**: `int vector_<type>_push_back(vector_<type>* v, type d)`
- **Usage**:
  ```c
  vector_int_push_back(&v, 42);
  ```

#### `vector_<type>_insert`
Inserts an element at a specific index, shifting subsequent elements.

- **Signature**: `int vector_<type>_insert(vector_<type>* v, size_t i, type d)`
- **Usage**:
  ```c
  // Insert 99 at the beginning
  vector_int_insert(&v, 0, 99);
  ```

### Removal

#### `vector_<type>_pop_back`
Removes the last element from the vector.

- **Signature**: `int vector_<type>_pop_back(vector_<type>* v)`
- **Usage**:
  ```c
  vector_int_pop_back(&v);
  ```

#### `vector_<type>_erase`
Removes the element at a specific index.

- **Signature**: `int vector_<type>_erase(vector_<type>* v, size_t i)`
- **Usage**:
  ```c
  // Erase the first element
  vector_int_erase(&v, 0);
  ```

#### `vector_<type>_erase_range`
Removes a range of elements from index `s` to `e-1`.

- **Signature**: `int vector_<type>_erase_range(vector_<type>* v, size_t s, size_t e)`
- **Usage**:
  ```c
  // Erase elements from index 1 to 3
  vector_int_erase_range(&v, 1, 4);
  ```

### Access

#### `vector_<type>_at`
Returns a pointer to the element at a specific index. Returns `NULL` if the index is out of bounds.

- **Signature**: `type* vector_<type>_at(const vector_<type>* v, size_t i)`
- **Usage**:
  ```c
  int* element = vector_int_at(&v, 0);
  if (element) {
      printf("Element at index 0: %d\n", *element);
  }
  ```

#### `vector_<type>_front`
Returns a pointer to the first element. Returns `NULL` if the vector is empty.

- **Signature**: `type* vector_<type>_front(const vector_<type>* v)`
- **Usage**:
  ```c
  int* first = vector_int_front(&v);
  ```

#### `vector_<type>_back`
Returns a pointer to the last element. Returns `NULL` if the vector is empty.

- **Signature**: `type* vector_<type>_back(const vector_<type>* v)`
- **Usage**:
  ```c
  int* last = vector_int_back(&v);
  ```

### Properties

#### `vector_<type>_size`
Returns the number of elements in the vector.

- **Signature**: `size_t vector_<type>_size(const vector_<type>* v)`
- **Usage**:
  ```c
  size_t size = vector_int_size(&v);
  ```

#### `vector_<type>_capacity`
Returns the current storage capacity of the vector.

- **Signature**: `size_t vector_<type>_capacity(const vector_<type>* v)`
- **Usage**:
  ```c
  size_t capacity = vector_int_capacity(&v);
  ```

#### `vector_<type>_is_empty`
Returns non-zero if the vector is empty.

- **Signature**: `int vector_<type>_is_empty(const vector_<type>* v)`
- **Usage**:
  ```c
  if (!vector_int_is_empty(&v)) {
      // ...
  }
  ```

### Algorithms

#### `vector_<type>_copy`
Creates a deep copy of a source vector. The destination vector must be initialized.

- **Signature**: `int vector_<type>_copy(vector_<type>* dst, vector_<type>* src)`
- **Usage**:
  ```c
  vector_int v_copy;
  vector_int_init(&v_copy);
  vector_int_copy(&v_copy, &v);
  ```

#### `vector_<type>_sort`
Sorts the vector. Requires a `compare_<type>` function to be defined.

- **Signature**: `void vector_<type>_sort(vector_<type>* v)`
- **Usage**:
  ```c
  // Requires a compare_int function
  vector_int_sort(&v);
  ```

#### `vector_<type>_find`
Performs a linear search to find an element. Returns the index via the `idx` output parameter.

- **Signature**: `int vector_<type>_find(const vector_<type>* v, type val, size_t* idx)`
- **Usage**:
  ```c
  size_t found_idx;
  if (vector_int_find(&v, 42, &found_idx) == CSTL_SUCCESS) {
      printf("Found 42 at index %zu\n", found_idx);
  }
  ```

#### `vector_<type>_binary_search`
Performs a binary search on a sorted vector.

- **Signature**: `int vector_<type>_binary_search(const vector_<type>* v, type val, size_t* idx)`
- **Usage**:
  ```c
  size_t found_idx;
  // Assumes 'v' is sorted
  if (vector_int_binary_search(&v, 42, &found_idx) == CSTL_SUCCESS) {
      printf("Found 42 at index %zu\n", found_idx);
  }
  ```

## Limitations

- **Macro-based Instantiation**: The `CSTL_VECTOR(type)` macro generates code for each type, which can lead to code bloat if many different vector types are used.
- **No Shrinking**: The vector's capacity only grows; it never shrinks automatically.
- **Manual Memory Management for Pointers**: If the vector stores pointers, the user is responsible for freeing the memory for each element before calling `vector_<type>_destroy`.

## Future Enhancements

- **Shrink-to-fit**: A function to reduce the capacity to match the size could be added to reclaim memory.
- **Iterators**: A more advanced iterator system could be implemented for more flexible looping and algorithms.
- **Custom Allocators**: Allow users to provide their own memory allocator functions.