#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

// -----------------------------
//   Includes
// -----------------------------

#include <limits.h>
#include <stddef.h>

/**
 * @brief Return value used to indicate an invalid result.
 */
#define ARRAY_UTILS_INVALID_RESULT INT_MAX

/**
 * @brief Status codes returned by array utility functions.
 */
typedef enum
{
    ARRAY_OK = 0,     /**< Operation completed successfully */
    ARRAY_ERROR_NULL, /**< One or more NULL pointers passed */
    ARRAY_ERROR_EMPTY /**< The array size is zero */
} ArrayStatus;

/**
 * @brief Finds the minimum value in an integer array.
 *
 * @param array The input array (must not be NULL).
 * @param size The number of elements in the array.
 * @param out_min Pointer where the minimum value will be stored.
 * @return ArrayStatus Returns ARRAY_OK if successful, or an error code.
 */
ArrayStatus array_find_min(const int* array, size_t size, int* out_min);

/**
 * @brief Finds the maximum value in an integer array.
 *
 * @param array The input array (must not be NULL).
 * @param size The number of elements in the array.
 * @param out_max Pointer where the maximum value will be stored.
 * @return ArrayStatus Returns ARRAY_OK if successful, or an error code.
 */
ArrayStatus array_find_max(const int* array, size_t size, int* out_max);

#endif // ARRAY_UTILS_H
