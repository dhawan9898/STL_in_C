# Makefile for STL_in_C

CC = gcc
# Add -I to include the include directory
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude
LDFLAGS = 

# Build directory
BUILD_DIR = build
# Test executables
TESTS = $(BUILD_DIR)/test_vector $(BUILD_DIR)/test_stack $(BUILD_DIR)/test_queue $(BUILD_DIR)/test_deque

.PHONY: all test clean

all: $(TESTS)

# Explicit rules for each test
$(BUILD_DIR)/test_vector: test/test_vector.c include/cstl_vector.h include/cstl_common.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(BUILD_DIR)/test_stack: test/test_stack.c include/cstl_stack.h include/cstl_common.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(BUILD_DIR)/test_queue: test/test_queue.c include/cstl_queue.h include/cstl_common.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(BUILD_DIR)/test_deque: test/test_deque.c include/cstl_deque.h include/cstl_common.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Command to run all tests
test: all
	@echo "--- Running Vector Tests ---"
	./$(BUILD_DIR)/test_vector
	@echo "\n--- Running Stack Tests ---"
	./$(BUILD_DIR)/test_stack
	@echo "\n--- Running Queue Tests ---"
	./$(BUILD_DIR)/test_queue
	@echo "\n--- Running Deque Tests ---"
	./$(BUILD_DIR)/test_deque
	@echo "\n--- All tests completed ---"

# Command to clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)
