# Queue (`cstl_queue.h`)

A generic, type-safe FIFO (First-In-First-Out) queue, implemented with a circular buffer for efficient O(1) operations. It is created using the `CSTL_QUEUE(type)` macro.

## Performance

The circular buffer implementation allows for efficient operations:

- **`enqueue`**: Amortized O(1). It's O(1) unless the queue's capacity is full, triggering a reallocation which is O(n).
- **`dequeue`**: O(1).
- **`front` / `back`**: O(1).
- **`reserve`**: O(n) if reallocation is needed, as existing elements are copied to the new memory block.

## API Details

### Initialization

#### `queue_<type>_init`
Initializes a queue with a default capacity.

- **Signature**: `void queue_<type>_init(queue_<type>* q)`
- **Usage**:
  ```c
  CSTL_QUEUE(int);
  queue_int q;
  queue_int_init(&q);
  ```

#### `queue_<type>_destroy`
Frees the queue's internal storage. Does not free the elements themselves if they are pointers.

- **Signature**: `void queue_<type>_destroy(queue_<type>* q)`
- **Usage**:
  ```c
  queue_int_destroy(&q);
  ```

#### `queue_<type>_reserve`
Reserves capacity for at least `n` elements. This can be used to pre-allocate memory and avoid reallocations during `enqueue` operations.

- **Signature**: `int queue_<type>_reserve(queue_<type>* q, size_t n)`
- **Usage**:
  ```c
  // Reserve space for 50 integers
  queue_int_reserve(&q, 50);
  ```

### Queue Operations

#### `queue_<type>_enqueue`
Adds an element to the back of the queue.

- **Signature**: `int queue_<type>_enqueue(queue_<type>* q, type val)`
- **Usage**:
  ```c
  queue_int_enqueue(&q, 10);
  queue_int_enqueue(&q, 20);
  ```

#### `queue_<type>_dequeue`
Removes the element from the front of the queue.

- **Signature**: `int queue_<type>_dequeue(queue_<type>* q)`
- **Usage**:
  ```c
  queue_int_dequeue(&q);
  ```

#### `queue_<type>_dequeue_value`
Dequeues the front element and copies its value into an `out` parameter.

- **Signature**: `int queue_<type>_dequeue_value(queue_<type>* q, type* value_out)`
- **Usage**:
  ```c
  int val;
  if (queue_int_dequeue_value(&q, &val) == CSTL_SUCCESS) {
      printf("Dequeued value: %d\n", val);
  }
  ```

#### `queue_<type>_front`
Returns a pointer to the front element without removing it. Returns `NULL` if the queue is empty.

- **Signature**: `type* queue_<type>_front(const queue_<type>* q)`
- **Usage**:
  ```c
  int* front_val = queue_int_front(&q);
  if (front_val) {
      printf("Front value: %d\n", *front_val);
  }
  ```

#### `queue_<type>_back`
Returns a pointer to the back element without removing it. Returns `NULL` if the queue is empty.

- **Signature**: `type* queue_<type>_back(const queue_<type>* q)`
- **Usage**:
  ```c
  int* back_val = queue_int_back(&q);
  if (back_val) {
      printf("Back value: %d\n", *back_val);
  }
  ```

### Properties

#### `queue_<type>_size`
Returns the number of elements in the queue.

- **Signature**: `size_t queue_<type>_size(const queue_<type>* q)`
- **Usage**:
  ```c
  size_t current_size = queue_int_size(&q);
  ```

#### `queue_<type>_capacity`
Returns the current storage capacity of the queue.

- **Signature**: `size_t queue_<type>_capacity(const queue_<type>* q)`
- **Usage**:
  ```c
  size_t current_capacity = queue_int_capacity(&q);
  ```

#### `queue_<type>_is_empty`
Returns non-zero if the queue is empty.

- **Signature**: `int queue_<type>_is_empty(const queue_<type>* q)`
- **Usage**:
  ```c
  if (queue_int_is_empty(&q)) {
      printf("Queue is empty.\n");
  }
  ```

## Limitations

- **Macro-based Instantiation**: Generates code for each type, which can lead to code bloat.
- **No Shrinking**: The queue's capacity only grows; it never shrinks automatically.
- **Manual Memory Management for Pointers**: If the queue stores pointers, the user is responsible for freeing the pointed-to memory.

## Future Enhancements

- **Shrink-to-fit**: A function to reduce capacity to match the size would be a useful addition for memory optimization.
- **Iterators**: A system for iterating over the queue's elements without dequeueing them.
- **Custom Allocators**: Allowing users to provide custom memory allocation functions.