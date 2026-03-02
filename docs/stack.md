# Stack (cstl_stack.h)

A generic, type-safe LIFO (Last-In-First-Out) stack. It is a standalone container and does not depend on the vector implementation.

## Features

- **Type-Safe Instantiation**: `CSTL_STACK(type)` creates a stack for any given type.
- **Standalone Implementation**: Has no dependency on other containers.
- **Automatic Capacity Growth**: Automatically doubles its capacity on overflow.
- **Error Handling**: All operations validate arguments and return error codes.
- **Initial Capacity**: Defaults to 4 elements, configurable via `CSTL_STACK_INITIAL_CAPACITY`.

## API Reference

### Initialization
- `void stack_<type>_init(stack_<type>* s)`: Initializes a stack with a default capacity.
- `void stack_<type>_destroy(stack_<type>* s)`: Frees the stack's internal storage.
- `int stack_<type>_reserve(stack_<type>* s, size_t n)`: Reserves capacity for at least `n` elements.

### Stack Operations
- `int stack_<type>_push(stack_<type>* s, type val)`: Pushes an element onto the top of the stack.
- `int stack_<type>_pop(stack_<type>* s)`: Removes the top element from the stack.
- `int stack_<type>_pop_value(stack_<type>* s, type* value_out)`: Pops the top element into an out-parameter.
- `type* stack_<type>_top(const stack_<type>* s)`: Returns a pointer to the top element without removing it.

### Properties
- `size_t stack_<type>_size(const stack_<type>* s)`: Returns the number of elements in the stack.
- `size_t stack_<type>_capacity(const stack_<type>* s)`: Returns the current storage capacity.
- `int stack_<type>_is_empty(const stack_<type>* s)`: Returns non-zero if the stack is empty.
