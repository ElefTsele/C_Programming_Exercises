# C Programming Exercises

Practical C programming exercises, organized in a clean, modular structure with optional testing and professional coding practices.

Based on the excellent "C Programming Examples" playlist by [Portfolio Courses](https://www.youtube.com/@PortfolioCourses), this repository expands each example with:

- Modular C code (`.h` / `.c`)
- Robust error handling and status enums
- Common macros (array size, clamp, swap, etc.)
- Unit testing setup using Unity
- Future CI/CD integration

---

## Attribution

> Original exercise logic and problem descriptions are derived from  
> the [Portfolio Courses](https://www.youtube.com/@PortfolioCourses) YouTube channel.  
> This repository restructures and extends those examples for modularity and educational use.

---

## Project Structure

```
C_Programming_Exercises/
├── include/                   # Header files (.h)
├── src/                       # Source files (.c)
├── examples/                  # Executable examples (each with its own `main()`)
├── tests/
│   ├── manual/                # Manual tests (no framework)
│   └── unity/                 # Unit tests using Unity framework
├── lib/
│   └── unity/                 # Unity framework source
├── bin/                       # Output binaries
├── Makefile                   # Build system
└── README.md
```

---

## Build & Run

```sh
make help                                # Show available options
make EXERCISE=01 run_example             # Run the example with main()
make EXERCISE=01 run_manual_test         # Run manual tests (without framework)
make EXERCISE=01 run_unity_test          # Run Unity tests (with Unity framework)
make clean                               # Clean build output (bin/)
make LOG=1 EXERCISE=01 run_example       # Enable debug logging (if supported)
make check_includes                      # Show all include paths used in the code
```

---

## Adding a New Exercise

1. Create the appropriate files (.c and .h) with the correct names and folders.
2. Add a mapping for the new exercise in the Makefile:

```sh
ifeq ($(EXERCISE),02)
EXERCISE_NAME := new_module_name
endif
```

# Array Utilities

This directory contains modular, header-only libraries for common array operations,
designed for embedded systems and high-performance applications.

## Modules

- `array_stats.h` – Basic statistics: sum, mean, min, max
- `array_transform.h` – Value transformations: clamp, scale, normalize
- `array_sorted.h` – Optimized operations for sorted arrays (e.g. min/max in O(1))
- `array_noise.h` – Filtering functions (median, average excluding extremes, etc.)

---

## Performance Note

> **If your arrays are already sorted**, you should use `array_sorted.h`.

The functions in `array_stats.h` and others are generic and scan the entire array.
However, when the array is guaranteed to be sorted, significant optimizations can be made:
- `array_min_sorted()` → returns `array[0]`
- `array_max_sorted()` → returns `array[size - 1]`
- `array_median_sorted()` → direct access to the middle element

**These optimizations can reduce complexity from O(n) to O(1).**

