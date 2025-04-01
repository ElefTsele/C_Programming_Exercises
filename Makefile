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
# -------------------------------------------------------
# -DDEBUG_LOG_ENABLED: Enable debug/test/error logging via log.h macros
# -------------------------------------------------------
# User chose to enable logging via make LOG=1
# Print notice for visibility in terminal
ifeq ($(LOG),1)
    CFLAGS += -DDEBUG_LOG_ENABLED
$(info Logging enabled: DEBUG_LOG_ENABLED defined)
endif

# Directories
SRC_DIR = src
INCLUDE_DIR = include
EXAMPLES_DIR = examples
TESTS_MANUAL_DIR = tests/manual
TESTS_UNIT_DIR = tests/unity
UNITY_DIR = lib/unity
# -----------------------------
# Output binary directory
# NOTE: Must be defined BEFORE used as a target
# -----------------------------
BIN_DIR = bin

# Create bin/ directory if it doesn't exist
# Cross-platform compatibility (Windows + Linux)
$(BIN_DIR):
ifeq ($(OS),Windows_NT)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
else
	@mkdir -p $(BIN_DIR)
endif

# Exercise variable (e.g., 01)
EXERCISE ?= 01

# Mappings for EXERCISE number to module name
ifeq ($(EXERCISE),01)
EXERCISE_NAME := array_stats
else
$(error Unknown EXERCISE number '$(EXERCISE)'. Add mapping in Makefile)
endif

# Header-only modules that don't need a .c file
HEADER_ONLY_EXERCISES := 01

ifneq ($(filter $(EXERCISE),$(HEADER_ONLY_EXERCISES)),)
SRC_FILES :=
else
SRC_FILES = $(SRC_DIR)/$(EXERCISE_NAME).c
endif

# File paths
EXAMPLE_FILE = $(EXAMPLES_DIR)/$(EXERCISE)_$(EXERCISE_NAME)_example.c
MANUAL_TEST_FILE = $(TESTS_MANUAL_DIR)/$(EXERCISE)_test_$(EXERCISE_NAME).c
UNITY_TEST_FILE = $(TESTS_UNIT_DIR)/$(EXERCISE)_test_$(EXERCISE_NAME)_unity.c

UNITY_SRC = $(UNITY_DIR)/unity.c

# Output binaries
EXAMPLE_BIN = $(BIN_DIR)/$(EXERCISE)_$(EXERCISE_NAME)_example
MANUAL_BIN = $(BIN_DIR)/$(EXERCISE)_$(EXERCISE_NAME)_manual
UNITY_BIN = $(BIN_DIR)/$(EXERCISE)_$(EXERCISE_NAME)_unity

# Targets
.PHONY: help run_example run_manual_test run_unity_test clean

help:
	$(info Available targets:)
	$(info make EXERCISE=01 run_example)
	$(info make EXERCISE=01 run_manual_test)
	$(info make EXERCISE=01 run_unity_test)
	$(info make clean)
	$(info make LOG=1 ...  (enable debug logging))

# Example
$(EXAMPLE_BIN): $(EXAMPLE_FILE) $(SRC_FILES) | bin
	@echo "Building example..."
	@$(CC) $(CFLAGS) $^ -o $@

run_example: $(EXAMPLE_BIN) | $(BIN_DIR)
	@echo "Running example:"
	@./$(EXAMPLE_BIN)

# Manual test
$(MANUAL_BIN): $(MANUAL_TEST_FILE) $(SRC_FILES) | bin
	@echo "Building manual test..."
	@$(CC) $(CFLAGS) $^ -o $@

run_manual_test: $(MANUAL_BIN)
	@echo "Running manual test:"
	@./$(MANUAL_BIN)

# Unity test
$(UNITY_BIN): $(UNITY_TEST_FILE) $(SRC_FILES) $(UNITY_SRC) | bin
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




