# Queue (cstl_queue.h)

A generic, type-safe FIFO (First-In-First-Out) queue, implemented with a circular buffer for efficient O(1) operations. It is a standalone container.

## Features

- **Type-Safe Instantiation**: `CSTL_QUEUE(type)` creates a queue for any given type.
- **Circular Buffer**: Efficient O(1) enqueue and dequeue operations with automatic wraparound.
- **Standalone Implementation**: No dependency on other containers.
- **Automatic Capacity Growth**: Doubles capacity on overflow.
- **Error Handling**: All operations validate arguments and return error codes.
- **Initial Capacity**: Defaults to 4 elements, configurable via `CSTL_QUEUE_INITIAL_CAPACITY`.

## API Reference

### Initialization
- `void queue_<type>_init(queue_<type>* q)`: Initializes a queue with a default capacity.
- `void queue_<type>_destroy(queue_<type>* q)`: Frees the queue's internal storage.
- `int queue_<type>_reserve(queue_<type>* q, size_t n)`: Reserves capacity for at least `n` elements, compacting the circular buffer if necessary.

### Queue Operations
- `int queue_<type>_enqueue(queue_<type>* q, type val)`: Adds an element to the back of the queue.
- `int queue_<type>_dequeue(queue_<type>* q)`: Removes the element from the front of the queue.
- `int queue_<type>_dequeue_value(queue_<type>* q, type* value_out)`: Dequeues the front element into an out-parameter.
- `type* queue_<type>_front(const queue_<type>* q)`: Returns a pointer to the front element.
- `type* queue_<type>_back(const queue_<type>* q)`: Returns a pointer to the back element.

### Properties
- `size_t queue_<type>_size(const queue_<type>* q)`: Returns the number of elements in the queue.
- `size_t queue_<type>_capacity(const queue_<type>* q)`: Returns the current storage capacity.
- `int queue_<type>_is_empty(const queue_<type>* q)`: Returns non-zero if the queue is empty.
