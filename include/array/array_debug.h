/**
 * @file array_debug.h
 * @brief Debug utilities for integer arrays (e.g. print)
 *
 * @author Eleftherios Tselegkidis
 * @date 2025-04-01
 */

#ifndef ARRAY_DEBUG_H
#define ARRAY_DEBUG_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @brief Prints the contents of a signed integer array.
 *
 * @param array The input array (must not be NULL).
 * @param size  The number of elements in the array.
 */
static inline void array_print(const int32_t* array, size_t size)
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

/**
 * @brief Prints the contents of an unsigned integer array.
 *
 * @param array The input array (must not be NULL).
 * @param size  The number of elements in the array.
 */
static inline void array_print_u(const uint32_t* array, size_t size)
{
    if (array == NULL || size == 0U)
    {
        printf("Array is NULL or empty.\n");
        return;
    }

    printf("[ ");
    for (size_t i = 0U; i < size; ++i)
    {
        printf("%u ", array[i]);
    }
    printf("]\n");
}

#endif // ARRAY_DEBUG_H
