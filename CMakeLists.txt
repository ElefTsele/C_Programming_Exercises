# ============================================================
# CMake config for C_Programming_Exercises
# Targets: Examples + Unity Tests
# C Standard: C99 
# ============================================================
cmake_minimum_required(VERSION 3.16)
project(C_Programming_Exercises C)



set(
    CMAKE_C_STANDARD 99
    CMAKE_C_STANDARD_REQUIRED YES
    CMAKE_C_EXTENSIONS NO
)

# Set output directory for all built binaries (executables)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
    include
    lib/unity
)

# ============================================================
# Global Compiler Options
# -Wall     : Enable all common warnings
# -Wextra   : Extra useful warnings
# -Wpedantic: ISO compliance
# -Werror   : Treat warnings as errors
# -std=c99  : Redundant here, but ensures CLI builds match
# ============================================================
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# ============================================================
# Examples
# Automatically add example targets: example_01, example_02...
# Naming convention: example_<filename>
# ============================================================
file(GLOB_RECURSE EXAMPLE_SOURCES "examples/*/main.c")

foreach(EXAMPLE_FILE ${EXAMPLE_SOURCES})
    get_filename_component(EXERCISE_DIR ${EXAMPLE_FILE} DIRECTORY)
    get_filename_component(EXERCISE_FOLDER ${EXERCISE_DIR} NAME)
    
    # Extract number from folder name (e.g., "01_array_stats" -> "01")
    string(REGEX MATCH "^[0-9]+" EXERCISE_NUM ${EXERCISE_FOLDER})

    # Create target: example_01, example_02, ...
    add_executable(example_${EXERCISE_NUM} ${EXAMPLE_FILE})
endforeach()

# ============================================================
# Unity Tests (per test file, e.g. unity_02_clamp, unity_02_scale)
# ============================================================
file(GLOB_RECURSE UNITY_TEST_FILES "tests/*/*.c")

foreach(TEST_FILE ${UNITY_TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)              # clamp
    get_filename_component(TEST_DIR ${TEST_FILE} DIRECTORY)             # tests/02_array_transform
    get_filename_component(EXERCISE_FOLDER ${TEST_DIR} NAME)            # 02_array_transform
    string(REGEX MATCH "^[0-9]+" EXERCISE_NUM ${EXERCISE_FOLDER})       # 02

    set(TARGET_NAME unity_${EXERCISE_NUM}_${TEST_NAME})

    add_executable(${TARGET_NAME}
        ${TEST_FILE}
        lib/unity/unity.c
    )

    add_test(
        NAME ${TARGET_NAME}
        COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}
    )
endforeach()

enable_testing()

message("
# ============================================================
Project C_Programming_Exercises
Available targets:
  
Run Examples: (cd build/bin/)
  example_01
  example_02

Run Unity Test: (cd build/bin/)
  unity_01_stats
  unity_02_clamp 
  unity_02_scale

Run CTEST: (cd build)
  ctest
  
Build:
  cmake -B build
  cmake --build build
============================================================
")
