/**
 * @file array_transform.h
 * @brief Basic transform for integer arrays (clamp, scale, offset, normalize)
 *
 * @author Eleftherios Tselegkidis
 * @date 2025-04-01
 *
 * @warning For sorted arrays, prefer `array_sorted.h` for optimized O(1) versions.
 */
#ifndef ARRAY_TRANSFORM_H
#define ARRAY_TRANSFORM_H

// -----------------------------
//   Includes
// -----------------------------

#include <stddef.h>

// -----------------------------
//   Type Definitions
// -----------------------------

/**
 * @brief Status codes returned by array utility functions.
 */
typedef enum
{
    ARRAY_STATUS_OK = 0,             /**< Operation completed successfully */
    ARRAY_STATUS_ERROR_NULL,         /**< One or more NULL pointers passed */
    ARRAY_STATUS_ERROR_EMPTY,        /**< The array size is zero */
    ARRAY_STATUS_ERROR_INVALID_INPUT /**< The inputs can not be min>max */
} array_status_t;

// -----------------------------
//   Function Declarations (Inline Implementations)
// -----------------------------

/*
    array_clamp ok
    array_scale
    array_offset
    array_normalize
*/

/**
 * @brief Clamps each element of the array to a specified [min, max] range.
 *
 * Example:
 *   Input:  {1, 5, 12, -3}, min = 0, max = 10 → Output: {1, 5, 10, 0}
 *
 * @param array The input/output array (in-place modification).
 * @param size  The number of elements in the array.
 * @param min   The minimum allowed value.
 * @param max   The maximum allowed value.
 *
 * @retval ARRAY_STATUS_OK             Success.
 * @retval ARRAY_STATUS_ERROR_NULL     Input pointer is NULL.
 * @retval ARRAY_STATUS_ERROR_EMPTY    Array size is zero.
 * @retval ARRAY_STATUS_ERROR_INVALID_INPUT  min > max is invalid.
 */
static inline array_status_t array_clamp(int* array, size_t size, const int min, const int max)
{
    if (array == NULL)
    {
        return ARRAY_STATUS_ERROR_NULL;
    }

    if (size == 0U)
    {
        return ARRAY_STATUS_ERROR_EMPTY;
    }

    if (min > max)
    {
        return ARRAY_STATUS_ERROR_INVALID_INPUT;
    }

    for (size_t i = 0U; i < size; ++i)
    {
        if (array[i] < min)
        {
            array[i] = min;
        }
        else if (array[i] > max)
        {
            array[i] = max;
        }
    }

    return ARRAY_STATUS_OK;
}

/**
 * @brief Scale each element of the array.
 *
 * Example:
 *   Input:  {1, 2, 3, -4}, scale = 3 → Output: {3, 6, 9, -12}
 *
 * @param array The input/output array (in-place modification).
 * @param size  The number of elements in the array.
 * @param scale The scale factor.
 *
 * @retval ARRAY_STATUS_OK             Success.
 * @retval ARRAY_STATUS_ERROR_NULL     Input pointer is NULL.
 * @retval ARRAY_STATUS_ERROR_EMPTY    Array size is zero.
 */
static inline array_status_t array_scale(int* array, size_t size, const int scale)
{
    if (array == NULL)
    {
        return ARRAY_STATUS_ERROR_NULL;
    }
    if (size == 0U)
    {
        return ARRAY_STATUS_ERROR_EMPTY;
    }

    for (size_t i = 0; i < size; ++i)
    {
        array[i] = array[i] * scale;
    }

    return ARRAY_STATUS_OK;
}

#endif // ARRAY_TRANSFORM_H