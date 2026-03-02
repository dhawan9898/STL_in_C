# Set (`cstl_set.h`)

A generic, type-safe sorted container that stores unique elements. It is implemented internally using an AVL tree, ensuring logarithmic time complexity for most operations. It is created using the `CSTL_SET(type)` macro.

## Performance

The Set is implemented using an AVL tree, which is a self-balancing binary search tree. This provides efficient performance guarantees:

- **`insert`**: O(log n)
- **`contains`**: O(log n)
- **`destroy`**: O(n)

## API Details

### Initialization

#### `set_<type>_init`
Initializes an empty set. A comparison function must be provided to define the order of elements.

- **Signature**: `void set_<type>_init(set_<type>* set, int (*compare)(const void*, const void*))`
- **Usage**:
  ```c
  // For a set of integers
  int compare_ints(const void* a, const void* b) {
      int arg1 = *(const int*)a;
      int arg2 = *(const int*)b;
      if (arg1 < arg2) return -1;
      if (arg1 > arg2) return 1;
      return 0;
  }

  CSTL_SET(int);
  set_int my_set;
  set_int_init(&my_set, compare_ints);
  ```

#### `set_<type>_destroy`
Frees all nodes in the set. Does not free the elements themselves if they are pointers.

- **Signature**: `void set_<type>_destroy(set_<type>* set)`
- **Usage**:
  ```c
  set_int_destroy(&my_set);
  ```

### Set Operations

#### `set_<type>_insert`
Inserts a unique element into the set. If the element already exists, the set remains unchanged.

- **Signature**: `int set_<type>_insert(set_<type>* set, type value)`
- **Usage**:
  ```c
  set_int_insert(&my_set, 10);
  set_int_insert(&my_set, 20);
  set_int_insert(&my_set, 10); // This will not insert a duplicate
  ```

#### `set_<type>_contains`
Checks if an element exists in the set.

- **Signature**: `int set_<type>_contains(const set_<type>* set, type value)`
- **Returns**: `1` if the element is found, `0` otherwise.
- **Usage**:
  ```c
  if (set_int_contains(&my_set, 10)) {
      printf("Set contains 10\n");
  }
  ```

### Properties

#### `set_<type>_size`
Returns the number of elements in the set.

- **Signature**: `size_t set_<type>_size(const set_<type>* set)`
- **Usage**:
  ```c
  size_t current_size = set_int_size(&my_set);
  ```

#### `set_<type>_is_empty`
Returns non-zero if the set is empty.

- **Signature**: `int set_<type>_is_empty(const set_<type>* set)`
- **Usage**:
  ```c
  if (set_int_is_empty(&my_set)) {
      printf("Set is empty.\n");
  }
  ```

## Limitations

- **No deletion**: Currently, there is no function to remove elements from the set.
- **No iteration**: The current implementation does not provide a way to iterate through the elements of the set.
- **No direct element access**: Elements can only be checked for existence, not directly retrieved by value.
- **Manual Memory Management for Pointers**: If the set stores pointers, the user is responsible for freeing the pointed-to memory.

## Future Enhancements

- **`set_<type>_erase`**: Implement a function for removing elements while maintaining the AVL tree properties.
- **Iterators**: Implement an iterator system to traverse the elements in sorted order (e.g., in-order traversal).
- **`set_<type>_find`**: A function that returns a pointer to the element if found, similar to `std::set::find`.
- **Set operations**: Implement union, intersection, and difference operations.
- **Custom Allocators**: Support for user-provided memory allocators.
