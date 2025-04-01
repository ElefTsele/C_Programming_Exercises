/**
 * @file array_debug.h
 * @brief Debug utilities for integer arrays (e.g. print)
 *
 * @author Eleftherios Tselegkidis
 * @date 2025-04-01
 */

#ifndef ARRAY_DEBUG_H
#define ARRAY_DEBUG_H

// -----------------------------
//   Includes
// -----------------------------

#include <stddef.h>
#include <stdio.h>

// -----------------------------
//   Function Declarations (Inline Implementations)
// -----------------------------

/**
 * @brief Prints the contents of an integer array.
 *
 * @param array The input array (must not be NULL).
 * @param size The number of elements in the array.
 */
static inline void array_print(const int* array, size_t size)
{
    if (array == NULL || size == 0U)
    {
        printf("Array is NULL or empty.\n");
        return;
    }

    printf("[ ");
    for (size_t i = 0U; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("]\n");
}

#endif // ARRAY_DEBUG_H
