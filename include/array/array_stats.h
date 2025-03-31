#ifndef ARRAY_STATS_H
#define ARRAY_STATS_H

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
    ARRAY_STATUS_OK = 0,     /**< Operation completed successfully */
    ARRAY_STATUS_ERROR_NULL, /**< One or more NULL pointers passed */
    ARRAY_STATUS_ERROR_EMPTY /**< The array size is zero */
} array_status_t;

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
 * @retval ARRAY_STATUS_OK            Success.
 * @retval ARRAY_STATUS_ERROR_NULL    Input or output pointer is NULL.
 * @retval ARRAY_STATUS_ERROR_EMPTY   Array size is zero.
 */
static inline array_status_t array_min(const int* array, size_t size, int* out_min)
{
    if (array == NULL || out_min == NULL)
    {
        return ARRAY_STATUS_ERROR_NULL;
    }

    if (size == 0U)
    {
        return ARRAY_STATUS_ERROR_EMPTY;
    }

    int min = array[0];
    for (size_t i = 1U; i < size; ++i)
    {
        if (array[i] < min)
            min = array[i];
    }

    *out_min = min;
    return ARRAY_STATUS_OK;
}

/**
 * @brief Finds the maximum value in an integer array.
 *
 * @param array The input array (must not be NULL).
 * @param size The number of elements in the array.
 * @param out_max Pointer where the maximum value will be stored.
 *
 * @retval ARRAY_STATUS_OK            Success.
 * @retval ARRAY_STATUS_ERROR_NULL    Input or output pointer is NULL.
 * @retval ARRAY_STATUS_ERROR_EMPTY   Array size is zero.
 */
static inline array_status_t array_max(const int* array, size_t size, int* out_max)
{
    if (array == NULL || out_max == NULL)
    {
        return ARRAY_STATUS_ERROR_NULL;
    }

    if (size == 0U)
    {
        return ARRAY_STATUS_ERROR_EMPTY;
    }

    int max = array[0];
    for (size_t i = 1U; i < size; ++i)
    {
        if (array[i] > max)
            max = array[i];
    }

    *out_max = max;
    return ARRAY_STATUS_OK;
}

/**
 * @brief Calculates the summation value of an integer array.
 *
 * @param array     The input array (must not be NULL).
 * @param size      The number of elements in the array.
 * @param out_sum   Pointer where the summation result will be stored.
 *
 * @retval ARRAY_STATUS_OK            Success.
 * @retval ARRAY_STATUS_ERROR_NULL    Input or output pointer is NULL.
 * @retval ARRAY_STATUS_ERROR_EMPTY   Array size is zero.
 */
static inline array_status_t array_sum(const int* array, size_t size, int* out_sum)
{
    if (array == NULL || out_sum == NULL)
    {
        return ARRAY_STATUS_ERROR_NULL;
    }

    if (size == 0U)
    {
        return ARRAY_STATUS_ERROR_EMPTY;
    }

    int sum = 0;
    for (size_t i = 0U; i < size; ++i)
    {
        sum = sum + array[i];
    }

    *out_sum = sum;
    return ARRAY_STATUS_OK;
}

/**
 * @brief Calculates the mean value of an integer array.
 *
 * @param array     The input array (must not be NULL).
 * @param size      The number of elements in the array.
 * @param out_mean  Pointer where the mean result will be stored.
 *
 * @retval ARRAY_STATUS_OK            Success.
 * @retval ARRAY_STATUS_ERROR_NULL    Input or output pointer is NULL.
 * @retval ARRAY_STATUS_ERROR_EMPTY   Array size is zero.
 */
static inline array_status_t array_mean(const int* array, size_t size, int* out_mean)
{
    if (array == NULL || out_mean == NULL)
    {
        return ARRAY_STATUS_ERROR_NULL;
    }

    if (size == 0U)
    {
        return ARRAY_STATUS_ERROR_EMPTY;
    }

    int sum = 0;
    array_status_t status = array_sum(array, size, &sum);
    if (status != ARRAY_STATUS_OK)
    {
        return status;
    }

    *out_mean = sum / (int) size;

    return ARRAY_STATUS_OK;
}

#endif // ARRAY_STATS_H
