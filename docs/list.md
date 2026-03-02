# List (`cstl_list.h`)

A generic, type-safe doubly-linked list. It provides efficient O(1) insertion and deletion at both ends of the list. It is created using the `CSTL_LIST(type)` macro.

## Performance

- **`push_front` / `push_back`**: O(1).
- **`pop_front` / `pop_back`**: O(1).
- **`front` / `back`**: O(1).
- **Iteration**: O(n) to iterate through the list.
- **`at` (not implemented)**: Accessing an element by index would be an O(n) operation as it requires traversing the list from the beginning or end.

## API Details

### Initialization

#### `list_<type>_init`
Initializes an empty list.

- **Signature**: `void list_<type>_init(list_<type>* list)`
- **Usage**:
  ```c
  CSTL_LIST(int);
  list_int l;
  list_int_init(&l);
  ```

#### `list_<type>_destroy`
Frees all nodes in the list. Does not free the elements themselves if they are pointers.

- **Signature**: `void list_<type>_destroy(list_<type>* list)`
- **Usage**:
  ```c
  list_int_destroy(&l);
  ```

### Insertion

#### `list_<type>_push_front`
Adds an element to the front of the list.

- **Signature**: `int list_<type>_push_front(list_<type>* list, type value)`
- **Usage**:
  ```c
  list_int_push_front(&l, 10);
  ```

#### `list_<type>_push_back`
Adds an element to the back of the list.

- **Signature**: `int list_<type>_push_back(list_<type>* list, type value)`
- **Usage**:
  ```c
  list_int_push_back(&l, 20);
  ```

### Removal

#### `list_<type>_pop_front`
Removes the element from the front of the list.

- **Signature**: `int list_<type>_pop_front(list_<type>* list)`
- **Usage**:
  ```c
  list_int_pop_front(&l);
  ```

#### `list_<type>_pop_back`
Removes the element from the back of the list.

- **Signature**: `int list_<type>_pop_back(list_<type>* list)`
- **Usage**:
  ```c
  list_int_pop_back(&l);
  ```

### Access

#### `list_<type>_front`
Returns a pointer to the front element. Returns `NULL` if the list is empty.

- **Signature**: `type* list_<type>_front(const list_<type>* list)`
- **Usage**:
  ```c
  int* front_val = list_int_front(&l);
  ```

#### `list_<type>_back`
Returns a pointer to the back element. Returns `NULL` if the list is empty.

- **Signature**: `type* list_<type>_back(const list_<type>* list)`
- **Usage**:
  ```c
  int* back_val = list_int_back(&l);
  ```

### Properties

#### `list_<type>_size`
Returns the number of elements in the list.

- **Signature**: `size_t list_<type>_size(const list_<type>* list)`
- **Usage**:
  ```c
  size_t current_size = list_int_size(&l);
  ```

#### `list_<type>_is_empty`
Returns non-zero if the list is empty.

- **Signature**: `int list_<type>_is_empty(const list_<type>* list)`
- **Usage**:
  ```c
  if (list_int_is_empty(&l)) {
      // ...
  }
  ```

### Iterators

#### `list_<type>_begin`
Returns an iterator to the beginning of the list.

- **Signature**: `list_iterator_<type> list_<type>_begin(const list_<type>* list)`

#### `list_<type>_end`
Returns an iterator to the end of the list (a NULL pointer).

- **Signature**: `list_iterator_<type> list_<type>_end(const list_<type>* list)`

#### `list_<type>_next`
Advances the iterator to the next element.

- **Signature**: `void list_<type>_next(list_iterator_<type>* it)`

#### `list_<type>_deref`
Dereferences the iterator to get a pointer to the value.

- **Signature**: `type* list_<type>_deref(const list_iterator_<type>* it)`

- **Usage**:
  ```c
  list_iterator_int it;
  for (it = list_int_begin(&l); it.node != list_int_end(&l).node; list_int_next(&it)) {
      int* val = list_int_deref(&it);
      printf("%d\n", *val);
  }
  ```

## Limitations

- **No random access**: Accessing elements by index is an O(n) operation and is not provided by the current API.
- **Memory overhead**: Each element requires extra storage for two pointers (next and prev), which can be significant for small data types.
- **Manual Memory Management**: If the list stores pointers, the user is responsible for freeing the pointed-to memory.

## Future Enhancements

- **`insert` and `erase`**: Functions to insert and erase elements at a specific iterator position.
- **`splice`**: A function to move elements from one list to another.
- **`sort`**: A `list_sort` function.
- **Bidirectional iterators**: Add `prev` function to move iterator backwards.
- **Custom Allocators**: Support for user-provided memory allocators.
