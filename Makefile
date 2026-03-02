# Makefile for STL_in_C

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude

# Build directory
BUILD_DIR = build
TEST_SRC = $(wildcard test/test_*.c)
TESTS = $(patsubst test/%.c,$(BUILD_DIR)/%,$(TEST_SRC))

.PHONY: all test clean

all: $(TESTS)

$(BUILD_DIR)/%: test/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) "$<" -o "$@"

test: all
	@echo "--- Running all tests ---"
	@for t in $(TESTS); do \
		echo "\n--- Running $$(basename $$t) Tests ---"; \
		./$$t; \
	done
	@echo "\n--- All tests completed ---"

clean:
	rm -rf $(BUILD_DIR)