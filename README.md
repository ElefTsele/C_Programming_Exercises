# C Programming Exercises

Practical C programming exercises, organized in a clean, modular structure with optional testing and professional coding practices.

---

## Design Philosophy

This project follows a professional, embedded-oriented coding style inspired by real-world practices:

- Header-only libraries with `static inline` for maximum performance and inlining
- Explicit `array_status_t` enums for robust and readable error handling
- CI/CD support for testing each exercise automatically (GitHub Actions)
- Modular folder structure: separates logic, examples, and tests clearly
- No external dependencies except Unity (for unit testing)

---

## Project Structure

```
C_Programming_Exercises/
├── build/                   # CMake build output
│   └── bin/                 # Output binaries (executables)
├── examples/                # Executable examples (main.c)
├── include/array/           # Modular header-only libraries
├── lib/unity/               # Unity framework source
├── tests/                   # Unit tests (per module, per function)
├── .github/workflows/       # GitHub Actions CI configuration
├── .gitignore               # Ignore build/output/temp files
├── CMakeLists.txt           # CMake build configuration
├── Doxyfile                 # Doxygen configuration
└── README.md
```

---

## Build Instructions

> Requires CMake 3.16+ and a C compiler (GCC, Clang, MinGW, etc.)

```bash
# Generate build system
cmake -B build

# Build all available targets
cmake --build build

```

---


## Executables & Naming

| Target               | Description                         |
|----------------------|-------------------------------------|
| `example_01`         | Run main example from exercise 01   |
| `unity_01_stats`     | Run Unity tests for stats module    |
| `unity_02_clamp`     | Run Unity tests for clamp function  |
| `unity_02_scale`     | Run Unity tests for scale function  |
| ...                  | Auto-generated based on file names  |

Each Unity test file (`clamp.c`, `scale.c`, etc.) is built independently.  
Tests follow the Unity style and can override `setUp()` / `tearDown()` as needed.

---

# Array Utilities

This directory contains modular, header-only libraries for common array operations,
designed for embedded systems and high-performance applications.

## Modules Overview

| Header              | Purpose                                        |
|---------------------|------------------------------------------------|
| `array_stats.h`     | Min, max, sum, mean                            |
| `array_transform.h` | Clamp, normalize, offset, scale                |
| `array_sorted.h`    | Optimized access when array is sorted (O(1))   |
| `array_noise.h`     | Median, trimmed mean, noise reduction          |

All functions are `static inline`, zero-overhead, and portable.

---

## Performance Note

> **If your arrays are already sorted**, you should use `array_sorted.h`.

The functions in `array_stats.h` and others are generic and scan the entire array.
However, when the array is guaranteed to be sorted, significant optimizations can be made:
- `array_min_sorted()` → returns `array[0]`
- `array_max_sorted()` → returns `array[size - 1]`
- `array_median_sorted()` → direct access to the middle element

These optimizations can reduce complexity from O(n) to O(1).

## Coming Soon

- [ ] `ctest` integration to run all Unity tests with one command
- [ ] `Doxygen` support for clean documentation
- [ ] Example validation with `valgrind` (memory checks)
- [ ] Code coverage reports (gcov/gcovr)


© 2025 - Maintained by Eleftherios Tselegkidis