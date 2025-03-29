.SILENT:

ifeq ($(OS),Windows_NT)
    RM = del /Q /F
    CP = copy /Y
    ifdef ComSpec
        SHELL := $(ComSpec)
    endif
    ifdef COMSPEC
        SHELL := $(COMSPEC)
    endif
    BIN_SLASH = \\
else
    RM = rm -f
    CP = cp -f
    BIN_SLASH = /
endif

# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c99

# Directories
SRC_DIR = src
INCLUDE_DIR = include
EXAMPLES_DIR = examples
TESTS_MANUAL_DIR = tests/manual
TESTS_UNIT_DIR = tests/unity
UNITY_DIR = lib/unity
BIN_DIR = bin

# Exercise variable (e.g., 01)
EXERCISE ?= 01

# Mappings for EXERCISE number to module name
ifeq ($(EXERCISE),01)
EXERCISE_NAME := array_utils
else
$(error Unknown EXERCISE number '$(EXERCISE)'. Add mapping in Makefile)
endif

# File paths
SRC_FILES = $(SRC_DIR)/$(EXERCISE_NAME).c
EXAMPLE_FILE = $(EXAMPLES_DIR)/$(EXERCISE)_$(EXERCISE_NAME)_example.c
MANUAL_TEST_FILE = $(TESTS_MANUAL_DIR)/$(EXERCISE)_test_$(EXERCISE_NAME).c
UNITY_TEST_FILE = $(TESTS_UNIT_DIR)/$(EXERCISE)_test_$(EXERCISE_NAME)_unity.c


UNITY_SRC = $(UNITY_DIR)/unity.c

# Output binaries
EXAMPLE_BIN = $(BIN_DIR)/$(EXERCISE)_$(EXERCISE_NAME)_example
MANUAL_BIN = $(BIN_DIR)/$(EXERCISE)_$(EXERCISE_NAME)_manual
UNITY_BIN = $(BIN_DIR)/$(EXERCISE)_$(EXERCISE_NAME)_unity

# Targets
.PHONY: all run_example run_manual_test run_unity_test clean

all:
	@echo "Available targets: run_example, run_manual_test, run_unity_test, make clean"

# Example
$(EXAMPLE_BIN): $(EXAMPLE_FILE) $(SRC_FILES)
	@echo "Building example..."
	@$(CC) $(CFLAGS) $^ -o $@

run_example: $(EXAMPLE_BIN)
	@echo "Running example:"
	@./$(EXAMPLE_BIN)

# Manual test
$(MANUAL_BIN): $(MANUAL_TEST_FILE) $(SRC_FILES)
	@echo "Building manual test..."
	@$(CC) $(CFLAGS) $^ -o $@

run_manual_test: $(MANUAL_BIN)
	@echo "Running manual test:"
	@./$(MANUAL_BIN)

# Unity test
$(UNITY_BIN): $(UNITY_TEST_FILE) $(SRC_FILES) $(UNITY_SRC)
	@echo "Building Unity test..."
	@$(CC) $(CFLAGS) $^ -I$(UNITY_DIR) -o $@

run_unity_test: $(UNITY_BIN)
	@echo "Running Unity test:"
	@./$(UNITY_BIN)

# Clean
clean:
	@echo Cleaning project...
	-$(RM) $(BIN_DIR)$(BIN_SLASH)*.exe
	@echo Clean complete.




