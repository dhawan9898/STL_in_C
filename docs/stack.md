# Stack (`cstl_stack.h`)

A generic, type-safe LIFO (Last-In-First-Out) stack. It is a standalone container created using the `CSTL_STACK(type)` macro.

## Performance

- **`push`**: Amortized O(1). If the stack is full, it reallocates, which takes O(n) time.
- **`pop`**: O(1).
- **`top`**: O(1).
- **`reserve`**: O(n) if reallocation is needed.

## API Details

### Initialization

#### `stack_<type>_init`
Initializes a stack with a default capacity.

- **Signature**: `void stack_<type>_init(stack_<type>* s)`
- **Usage**:
  ```c
  CSTL_STACK(int);
  stack_int s;
  stack_int_init(&s);
  ```

#### `stack_<type>_destroy`
Frees the stack's internal storage. Does not free the elements themselves if they are pointers.

- **Signature**: `void stack_<type>_destroy(stack_<type>* s)`
- **Usage**:
  ```c
  stack_int_destroy(&s);
  ```

#### `stack_<type>_reserve`
Reserves capacity for at least `n` elements, preventing reallocations on subsequent pushes.

- **Signature**: `int stack_<type>_reserve(stack_<type>* s, size_t n)`
- **Usage**:
  ```c
  // Reserve space for 30 integers
  stack_int_reserve(&s, 30);
  ```

### Stack Operations

#### `stack_<type>_push`
Pushes an element onto the top of the stack.

- **Signature**: `int stack_<type>_push(stack_<type>* s, type val)`
- **Usage**:
  ```c
  stack_int_push(&s, 10);
  stack_int_push(&s, 20); // Stack: [10, 20]
  ```

#### `stack_<type>_pop`
Removes the top element from the stack.

- **Signature**: `int stack_<type>_pop(stack_<type>* s)`
- **Usage**:
  ```c
  stack_int_pop(&s); // Stack: [10]
  ```

#### `stack_<type>_pop_value`
Pops the top element and copies its value into an `out` parameter.

- **Signature**: `int stack_<type>_pop_value(stack_<type>* s, type* value_out)`
- **Usage**:
  ```c
  int val;
  if (stack_int_pop_value(&s, &val) == CSTL_SUCCESS) {
      printf("Popped value: %d\n", val);
  }
  ```

#### `stack_<type>_top`
Returns a pointer to the top element without removing it. Returns `NULL` if the stack is empty.

- **Signature**: `type* stack_<type>_top(const stack_<type>* s)`
- **Usage**:
  ```c
  int* top_val = stack_int_top(&s);
  if (top_val) {
      printf("Top value: %d\n", *top_val);
  }
  ```

### Properties

#### `stack_<type>_size`
Returns the number of elements in the stack.

- **Signature**: `size_t stack_<type>_size(const stack_<type>* s)`
- **Usage**:
  ```c
  size_t current_size = stack_int_size(&s);
  ```

#### `stack_<type>_capacity`
Returns the current storage capacity of the stack.

- **Signature**: `size_t stack_<type>_capacity(const stack_<type>* s)`
- **Usage**:
  ```c
  size_t current_capacity = stack_int_capacity(&s);
  ```

#### `stack_<type>_is_empty`
Returns non-zero if the stack is empty.

- **Signature**: `int stack_<type>_is_empty(const stack_<type>* s)`
- **Usage**:
  ```c
  if (stack_int_is_empty(&s)) {
      printf("Stack is empty.\n");
  }
  ```

## Limitations

- **Macro-based Instantiation**: Leads to code bloat if many different stack types are used.
- **No Shrinking**: The stack's capacity only grows; it never shrinks automatically.
- **Manual Memory Management for Pointers**: The user is responsible for freeing memory for pointer elements.

## Future Enhancements

- **Shrink-to-fit**: A function to reduce capacity to match the current size.
- **Iterators**: A system for iterating over the stack's elements from top to bottom.
- **Custom Allocators**: Allow users to provide their own memory allocation functions.