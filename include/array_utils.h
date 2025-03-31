#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

// -----------------------------
//   Includes
// -----------------------------

#include <limits.h>
#include <stddef.h>

// -----------------------------
//   Defines
// -----------------------------

/**
 * @brief Return value used to indicate an invalid result.
 */
#define ARRAY_UTILS_INVALID_RESULT INT_MAX

// -----------------------------
//   Type Definitions
// -----------------------------

/**
 * @brief Status codes returned by array utility functions.
 */
typedef enum
{
    ARRAY_OK = 0,     /**< Operation completed successfully */
    ARRAY_ERROR_NULL, /**< One or more NULL pointers passed */
    ARRAY_ERROR_EMPTY /**< The array size is zero */
} ArrayStatus;

// -----------------------------
//   Function Declarations (Inline Implementations)
// -----------------------------

/**
 * @brief Finds the minimum value in an integer array.
 *
 * @param array The input array (must not be NULL).
 * @param size The number of elements in the array.
 * @param out_min Pointer where the minimum value will be stored.
 *
 * @retval ARRAY_OK            Success
 * @retval ARRAY_ERROR_NULL    Input or output pointer is NULL
 * @retval ARRAY_ERROR_EMPTY   Array size is zero
 */
static inline ArrayStatus array_min(const int* array, size_t size, int* out_min)
{
    if (array == NULL || out_min == NULL)
    {
        return ARRAY_ERROR_NULL;
    }

    if (size == 0U)
    {
        return ARRAY_ERROR_EMPTY;
    }

    int min = array[0];
    for (size_t i = 1U; i < size; ++i)
    {
        if (array[i] < min)
            min = array[i];
    }

    *out_min = min;
    return ARRAY_OK;
}

/**
 * @brief Finds the maximum value in an integer array.
 *
 * @param array The input array (must not be NULL).
 * @param size The number of elements in the array.
 * @param out_max Pointer where the maximum value will be stored.
 *
 * @retval ARRAY_OK            Success
 * @retval ARRAY_ERROR_NULL    Input or output pointer is NULL
 * @retval ARRAY_ERROR_EMPTY   Array size is zero
 */
static inline ArrayStatus array_max(const int* array, size_t size, int* out_max)
{
    if (array == NULL || out_max == NULL)
    {
        return ARRAY_ERROR_NULL;
    }

    if (size == 0U)
    {
        return ARRAY_ERROR_EMPTY;
    }

    int max = array[0];
    for (size_t i = 1U; i < size; ++i)
    {
        if (array[i] > max)
            max = array[i];
    }

    *out_max = max;
    return ARRAY_OK;
}

/**
 * @brief Calculates the summation value of an integer array.

 * @param array     The input array (must not be NULL).
 * @param size      The number of elements in the array.
 * @param out_sum   Pointer where the summation result will be stored.
 *
 * @retval ARRAY_OK            Success
 * @retval ARRAY_ERROR_NULL    Input or output pointer is NULL
 * @retval ARRAY_ERROR_EMPTY   Array size is zero
 */
static inline ArrayStatus array_sum(const int* array, size_t size, int* out_sum)
{
    if (array == NULL || out_sum == NULL)
    {
        return ARRAY_ERROR_NULL;
    }

    if (size == 0U)
    {
        return ARRAY_ERROR_EMPTY;
    }

    int sum = 0;
    for (size_t i = 0U; i < size; ++i)
    {
        sum = sum + array[i];
    }

    *out_sum = sum;
    return ARRAY_OK;
}

#endif // ARRAY_UTILS_H
