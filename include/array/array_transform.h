/**
 * @file array_transform.h
 * @brief Basic transforms for integer arrays (clamp, scale, offset, normalize)
 *
 * @author Eleftherios Tselegkidis
 * @date 2025-04-01
 *
 * @warning For sorted arrays, prefer `array_sorted.h` for optimized O(1) versions.
 */
#ifndef ARRAY_TRANSFORM_H
#define ARRAY_TRANSFORM_H

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Status codes returned by array utility functions.
 */
typedef enum
{
    ARRAY_STATUS_OK = 0,                 /**< Operation completed successfully */
    ARRAY_STATUS_WARNING_OVERFLOW_CLAMP, /**< Values were clamped to prevent overflow */
    ARRAY_STATUS_ERROR_NULL,             /**< NULL pointer was passed */
    ARRAY_STATUS_ERROR_EMPTY,            /**< Array size was zero */
    ARRAY_STATUS_ERROR_INVALID_INPUT     /**< Invalid input parameters (e.g., min > max) */
} array_status_t;

/**
 * @brief Clamp type selector for signed integer ranges.
 */
typedef enum
{
    CLAMP_INT8,
    CLAMP_INT16,
    CLAMP_INT32,
} clamp_type_int_t;

/**
 * @brief Clamp type selector for unsigned integer ranges.
 */
typedef enum
{
    CLAMP_UINT8,
    CLAMP_UINT16,
    CLAMP_UINT32
} clamp_type_uint_t;

/**
 * @brief Safe multiplication with overflow detection for signed 32-bit integers.
 */
static inline bool safe_mul_check_int32(int32_t value, int32_t factor, int32_t* result,
                                        clamp_type_int_t type)
{
    int32_t min, max;

    switch (type)
    {
    case CLAMP_INT8:
        min = INT8_MIN;
        max = INT8_MAX;
        break;
    case CLAMP_INT16:
        min = INT16_MIN;
        max = INT16_MAX;
        break;
    case CLAMP_INT32:
    default:
        min = INT32_MIN;
        max = INT32_MAX;
        break;
    }

    if ((value > 0 && factor > 0 && value > max / factor) ||
        (value < 0 && factor < 0 && value < max / factor) ||
        (value > 0 && factor < 0 && factor < min / value) ||
        (value < 0 && factor > 0 && value < min / factor))
    {
        *result = (value > 0) ? max : min;
        return false;
    }

    *result = value * factor;
    return true;
}

/**
 * @brief Safe multiplication with overflow detection for unsigned 32-bit integers.
 */
static inline bool safe_mul_check_uint32(uint32_t value, uint32_t factor, uint32_t* result,
                                         clamp_type_uint_t type)
{
    uint32_t max;

    switch (type)
    {
    case CLAMP_UINT8:
        max = UINT8_MAX;
        break;
    case CLAMP_UINT16:
        max = UINT16_MAX;
        break;
    case CLAMP_UINT32:
    default:
        max = UINT32_MAX;
        break;
    }

    if (factor != 0U && value > (max / factor))
    {
        *result = max;
        return false;
    }

    *result = value * factor;
    return true;
}

/**
 * @brief Clamps each element of the array to a specified [min, max] range.
 */
static inline array_status_t array_clamp(int32_t* array, size_t size, int32_t min, int32_t max)
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
 * @brief Scales array elements safely with overflow protection.
 *
 * @param array  The array to scale (in-place).
 * @param size   Number of elements.
 * @param factor Scaling factor.
 * @param type   Clamp type selector (signed).
 *
 * @retval ARRAY_STATUS_OK                     No overflow.
 * @retval ARRAY_STATUS_WARNING_OVERFLOW_CLAMP Clamped due to overflow.
 * @retval ARRAY_STATUS_ERROR_NULL             Null pointer.
 * @retval ARRAY_STATUS_ERROR_EMPTY            Zero-length array.
 */
static inline array_status_t array_scale_safe(int32_t* array, size_t size, int32_t factor,
                                              clamp_type_int_t type)
{
    if (array == NULL)
    {
        return ARRAY_STATUS_ERROR_NULL;
    }
    if (size == 0U)
    {
        return ARRAY_STATUS_ERROR_EMPTY;
    }

    bool clamped = false;
    int32_t scaled;

    for (size_t i = 0U; i < size; ++i)
    {
        if (!safe_mul_check_int32(array[i], factor, &scaled, type))
        {
            clamped = true;
        }
        array[i] = scaled;
    }

    return clamped ? ARRAY_STATUS_WARNING_OVERFLOW_CLAMP : ARRAY_STATUS_OK;
}

/**
 * @brief Unsigned variant of array_scale_safe.
 */
static inline array_status_t array_scale_safe_uint(uint32_t* array, size_t size, uint32_t factor,
                                                   clamp_type_uint_t type)
{
    if (array == NULL)
    {
        return ARRAY_STATUS_ERROR_NULL;
    }
    if (size == 0U)
    {
        return ARRAY_STATUS_ERROR_EMPTY;
    }

    bool clamped = false;
    uint32_t scaled;

    for (size_t i = 0U; i < size; ++i)
    {
        if (!safe_mul_check_uint32(array[i], factor, &scaled, type))
        {
            clamped = true;
        }
        array[i] = scaled;
    }

    return clamped ? ARRAY_STATUS_WARNING_OVERFLOW_CLAMP : ARRAY_STATUS_OK;
}

#endif // ARRAY_TRANSFORM_H
