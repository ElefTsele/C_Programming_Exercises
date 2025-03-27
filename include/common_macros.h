#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

// -----------------------------
//   Generic Value Macros
// -----------------------------

// Calculates the number of elements in a static array
// = sizeof(my_array) / sizeof(my_array[0]);
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Returns the minimum of two values
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

// Returns the maximum of two values
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

// Clamps a value between min and max
#define CLAMP(val, min_val, max_val) (MAX((min_val), MIN((val), (max_val))))

// ==============================
//   Utility Macros
// ==============================

// Swaps two values (requires a temp variable declaration)
#define SWAP(type, a, b)  do {  type tmp = (a);  (a) = (b);  (b) = tmp;  } while (0)

// Returns the absolute value
#define ABS(x) (((x) < 0) ? -(x) : (x))

// Checks if a number is even
#define IS_EVEN(x) (((x) % 2) == 0)

// Checks if a number is odd
#define IS_ODD(x) (((x) % 2) != 0)

// -----------------------------
//   BIT Manipulation Macros
// -----------------------------

// Create bitmask from bit position
#define BIT(n) (1U << (n))

// Set specific bit
#define SET_BIT(reg, bit)    ((reg) |= BIT(bit))

// Clear specific bit
#define CLEAR_BIT(reg, bit)  ((reg) &= ~BIT(bit))

// Toggle specific bit
#define TOGGLE_BIT(reg, bit) ((reg) ^= BIT(bit))

// Check if bit is set (non-zero if set)
#define IS_BIT_SET(reg, bit) (((reg) & BIT(bit)) != 0)

// Check if bit is clear (non-zero if clear)
#define IS_BIT_CLEAR(reg, bit) (((reg) & BIT(bit)) == 0)

// -----------------------------
//   Type-Safe Helper (GCC-specific)
// -----------------------------

// Swap two values of the same type (type-safe, GCC extension)
#define SWAP_SAFE(a, b)    do {  __typeof__(a) _tmp = (a);  (a) = (b);  (b) = _tmp;  } while (0)

// -----------------------------
//   Structure Utilities
// -----------------------------

// Get pointer to struct from member pointer (Linux-style)
#define container_of(ptr, type, member)    ((type *)((char *)(ptr) - offsetof(type, member)))

// -----------------------------
//   Range checking
// -----------------------------

// Check if x is within [min, max] range
#define IN_RANGE(x, min, max) (((x) >= (min)) && ((x) <= (max)))

// Clamp + assign: x = clamp(x, min, max)
#define CLAMP_ASSIGN(x, min, max)   do {  if ((x) < (min)) (x) = (min);  else if ((x) > (max)) (x) = (max);  } while (0)


#endif