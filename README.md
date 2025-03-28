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
make 								 # Show available options
make EXERCISE=01 run_example         # Run the example with main()
make EXERCISE=01 run_manual_test     # Run manual tests (without framework)
make EXERCISE=01 run_unity_test      # Run Unity tests (unit testing)
make clean                           # Clean build output (bin/)
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