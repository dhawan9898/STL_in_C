# Priority Queue (`cstl_priority_queue.h`)

A generic, type-safe priority queue, implemented with a binary heap. It allows for efficient retrieval of the element with the highest priority. It is created using the `CSTL_PRIORITY_QUEUE(type)` macro.

## Performance

The priority queue is implemented as a binary heap, which provides the following performance characteristics:

- **`push`**: O(log n), due to the heapify-up operation.
- **`pop`**: O(log n), due to the heapify-down operation.
- **`top`**: O(1), as the highest priority element is always at the root of the heap.

## API Details

### Initialization

#### `priority_queue_<type>_init`
Initializes a priority queue with a custom comparison function.

- **Signature**: `void priority_queue_<type>_init(priority_queue_<type>* pq, int (*compare)(const void*, const void*))`
- **Usage**:
  ```c
  // For a max-heap of integers
  int compare_ints_max(const void* a, const void* b) {
      int arg1 = *(const int*)a;
      int arg2 = *(const int*)b;
      if (arg1 < arg2) return -1;
      if (arg1 > arg2) return 1;
      return 0;
  }

  CSTL_PRIORITY_QUEUE(int);
  priority_queue_int pq;
  priority_queue_int_init(&pq, compare_ints_max);
  ```

#### `priority_queue_<type>_destroy`
Frees the priority queue's internal storage.

- **Signature**: `void priority_queue_<type>_destroy(priority_queue_<type>* pq)`
- **Usage**:
  ```c
  priority_queue_int_destroy(&pq);
  ```

### Priority Queue Operations

#### `priority_queue_<type>_push`
Adds an element to the priority queue.

- **Signature**: `int priority_queue_<type>_push(priority_queue_<type>* pq, type value)`
- **Usage**:
  ```c
  priority_queue_int_push(&pq, 20);
  priority_queue_int_push(&pq, 10);
  ```

#### `priority_queue_<type>_pop`
Removes the element with the highest priority from the queue.

- **Signature**: `int priority_queue_<type>_pop(priority_queue_<type>* pq)`
- **Usage**:
  ```c
  priority_queue_int_pop(&pq);
  ```

#### `priority_queue_<type>_top`
Returns a pointer to the element with the highest priority. Returns `NULL` if the queue is empty.

- **Signature**: `type* priority_queue_<type>_top(const priority_queue_<type>* pq)`
- **Usage**:
  ```c
  int* top_val = priority_queue_int_top(&pq);
  if (top_val) {
      printf("Top element: %d\n", *top_val);
  }
  ```

### Properties

#### `priority_queue_<type>_size`
Returns the number of elements in the priority queue.

- **Signature**: `size_t priority_queue_<type>_size(const priority_queue_<type>* pq)`
- **Usage**:
  ```c
  size_t current_size = priority_queue_int_size(&pq);
  ```

#### `priority_queue_<type>_is_empty`
Returns non-zero if the priority queue is empty.

- **Signature**: `int priority_queue_<type>_is_empty(const priority_queue_<type>* pq)`
- **Usage**:
  ```c
  if (priority_queue_int_is_empty(&pq)) {
      // ...
  }
  ```

## Limitations

- **Requires Comparison Function**: The user must provide a valid comparison function for the priority queue to work correctly.
- **No Direct Element Access**: This implementation does not allow direct access to elements other than the top one.
- **Underlying Container**: The implementation is tied to the `cstl_vector.h` implementation.

## Future Enhancements

- **`pop_value`**: A function to pop the top element and return its value in one operation.
- **`update_priority`**: A function to change the priority of an element already in the queue.
- **Custom Allocators**: Support for user-provided memory allocators for the underlying vector.
- **D-ary heap**: Allow the user to specify the number of children in the heap to potentially improve performance in some use cases.
