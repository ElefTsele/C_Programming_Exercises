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
    ARRAY_STATUS_WARNING_OFFSET_IS_ZERO, /**< Offset was zero; no operation was performed */
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
 * @brief Type of arithmetic operation to be checked (scale or offset).
 *
 * Used in overflow-protected operations (e.g., multiplication or addition).
 */
typedef enum
{
    OPERATION_SCALE,
    OPERATION_OFFSET
} operation_check_type_t;

/**
 * @brief Checks if an arithmetic operation (scale or offset) would cause overflow.
 *
 * Performs static overflow checking on signed 32-bit integers based on the selected clamp type
 * (int8, int16, int32). Supports multiplication (`OPERATION_SCALE`) and addition
 * (`OPERATION_OFFSET`).
 *
 * This function does not perform the operation itself — it only determines whether it can
 * be safely performed without overflow. If overflow is detected, the caller is responsible
 * for clamping to the appropriate limit.
 *
 * @param value       The current array element to be operated on.
 * @param operand     The scaling or offset value to apply.
 * @param op          The type of arithmetic operation (scale or offset).
 * @param clamp_type  The clamping range (INT8, INT16, INT32).
 *
 * @retval true       Operation is safe — no overflow will occur.
 * @retval false      Operation would overflow — clamping is required.
 */
static inline bool safe_op_check_int32(int32_t value, int32_t operand, operation_check_type_t op,
                                       clamp_type_int_t clamp_type)
{
    int32_t min = INT32_MIN;
    int32_t max = INT32_MAX;

    switch (clamp_type)
    {
    case CLAMP_INT8:
        min = INT8_MIN;
        max = INT8_MAX;
        break;

    case CLAMP_INT16:
        min = INT16_MIN;
        max = INT16_MAX;
        break;

    default:
        break;
    }

    switch (op)
    {
    case OPERATION_SCALE:
        return !((value > 0 && operand > 0 && value > max / operand) ||
                 (value < 0 && operand < 0 && value < max / operand) ||
                 (value > 0 && operand < 0 && operand < min / value) ||
                 (value < 0 && operand > 0 && value < min / operand));

    case OPERATION_OFFSET:
        return !((operand > 0 && value > max - operand) || (operand < 0 && value < min - operand));
    default:
        return false;
    }
}

/**
 * @brief Checks for overflow in unsigned scale or offset operations.
 *
 * @param value  The current array element.
 * @param operand The scale or offset value.
 * @param op     The type of operation (scale or offset).
 * @param clamp_type The unsigned clamp type (e.g. UINT8, UINT16, UINT32).
 *
 * @retval true  No overflow will occur.
 * @retval false Operation would overflow and should be clamped.
 */
static inline bool safe_op_check_uint32(uint32_t value, uint32_t operand, operation_check_type_t op,
                                        clamp_type_uint_t clamp_type)
{
    uint32_t max = UINT32_MAX;

    switch (clamp_type)
    {
    case CLAMP_UINT8:
        max = UINT8_MAX;
        break;
    case CLAMP_UINT16:
        max = UINT16_MAX;
        break;
    default:
        break;
    }

    switch (op)
    {
    case OPERATION_SCALE:
        if (operand == 0U)
        {
            return true; // multiplication by 0 is always safe
        }
        return (value <= max / operand);

    case OPERATION_OFFSET:
        return (value <= max - operand);

    default:
        return false;
    }
}

/**
 * @brief Safely offsets each element in the array, with overflow protection.
 *
 * If any addition causes overflow or underflow, the result is clamped
 * based on the selected integer range (e.g. INT8, INT16, INT32).
 *
 * @param array  Pointer to the array to offset.
 * @param size   Number of elements in the array.
 * @param offset The value to add to each element.
 * @param type   Range to clamp against.
 *
 * @retval ARRAY_STATUS_OK                     All additions completed successfully.
 * @retval ARRAY_STATUS_WARNING_OVERFLOW_CLAMP One or more values were clamped.
 * @retval ARRAY_STATUS_WARNING_OFFSET_IS_ZERO No operation performed, offset was 0.
 * @retval ARRAY_STATUS_ERROR_NULL             Array pointer was NULL.
 * @retval ARRAY_STATUS_ERROR_EMPTY            Array size was 0.
 */
static inline array_status_t array_offset(int32_t* array, size_t size, int32_t offset,
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

    if (offset == 0)
    {
        return ARRAY_STATUS_WARNING_OFFSET_IS_ZERO;
    }

    bool clamped = false;

    for (size_t i = 0U; i < size; ++i)
    {
        if (!safe_op_check_int32(array[i], offset, OPERATION_OFFSET, type))
        {
            clamped = true;
            int32_t min = INT32_MIN;
            int32_t max = INT32_MAX;

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
            default:
                break;
            }

            array[i] = (offset > 0) ? max : min;
        }
        else
        {
            array[i] += offset;
        }
    }

    return clamped ? ARRAY_STATUS_WARNING_OVERFLOW_CLAMP : ARRAY_STATUS_OK;
}

/**
 * @brief Safely offsets each element in an unsigned array, with overflow protection.
 *
 * If any addition exceeds the maximum allowed value for the selected type (e.g. UINT8, UINT16),
 * the value is clamped to the maximum.
 *
 * @param array  Pointer to the unsigned array to offset.
 * @param size   Number of elements in the array.
 * @param offset The unsigned value to add to each element.
 * @param type   The clamp limit type (UINT8, UINT16, UINT32).
 *
 * @retval ARRAY_STATUS_OK                     All additions were successful.
 * @retval ARRAY_STATUS_WARNING_OVERFLOW_CLAMP One or more values were clamped to prevent overflow.
 * @retval ARRAY_STATUS_WARNING_OFFSET_IS_ZERO Offset was zero, no operation performed.
 * @retval ARRAY_STATUS_ERROR_NULL             Array pointer is NULL.
 * @retval ARRAY_STATUS_ERROR_EMPTY            Array size is zero.
 */
// NOTE:
// This function does not use `safe_op_check_uint32()` because
// in unsigned arithmetic, overflow detection is simpler and faster.
// Specifically, checking `a + b > MAX` is sufficient since unsigned integers
// wrap around on overflow and cannot be negative.
//
// If a unified approach is needed (e.g., via function pointer abstraction),
// this can be refactored later with `safe_op_check_uint32()`
// at the cost of a slight performance tradeoff.
static inline array_status_t array_offset_uint(uint32_t* array, size_t size, uint32_t offset,
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

    if (offset == 0U)
    {
        return ARRAY_STATUS_WARNING_OFFSET_IS_ZERO;
    }

    bool clamped = false;
    uint32_t max = UINT32_MAX;

    switch (type)
    {
    case CLAMP_UINT8:
        max = UINT8_MAX;
        break;
    case CLAMP_UINT16:
        max = UINT16_MAX;
        break;
    default:
        break;
    }

    for (size_t i = 0U; i < size; ++i)
    {
        if (array[i] > (max - offset))
        {
            array[i] = max;
            clamped = true;
        }
        else
        {
            array[i] += offset;
        }
    }

    return clamped ? ARRAY_STATUS_WARNING_OVERFLOW_CLAMP : ARRAY_STATUS_OK;
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

static inline array_status_t array_scale(int32_t* array, size_t size, int32_t factor,
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

    int32_t min = INT32_MIN;
    int32_t max = INT32_MAX;

    if (type == CLAMP_INT8)
    {
        min = INT8_MIN;
        max = INT8_MAX;
    }

    if (type == CLAMP_INT16)
    {
        min = INT16_MIN;
        max = INT16_MAX;
    }

    for (size_t i = 0U; i < size; ++i)
    {
        if (!safe_op_check_int32(array[i], factor, OPERATION_SCALE, type))
        {
            array[i] = (factor > 0) ? max : min;
            clamped = true;
        }
        else
        {
            array[i] *= factor;
        }
    }

    return clamped ? ARRAY_STATUS_WARNING_OVERFLOW_CLAMP : ARRAY_STATUS_OK;
}

/**
 * @brief Safely scales each element of an unsigned array by a given factor, with overflow
 * protection.
 *
 * If the result exceeds the type's maximum (e.g. UINT8_MAX), the value is clamped to the max.
 *
 * @param array   Pointer to the unsigned input/output array (modified in-place).
 * @param size    Number of elements in the array.
 * @param factor  Multiplication factor.
 * @param type    Unsigned integer range to clamp against.
 *
 * @retval ARRAY_STATUS_OK                     All elements scaled successfully.
 * @retval ARRAY_STATUS_WARNING_OVERFLOW_CLAMP One or more values were clamped.
 * @retval ARRAY_STATUS_ERROR_NULL             Null pointer input.
 * @retval ARRAY_STATUS_ERROR_EMPTY            Zero-length array.
 */
static inline array_status_t array_scale_uint(uint32_t* array, size_t size, uint32_t factor,
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

    // Select clamping max based on desired type
    uint32_t max = UINT32_MAX;
    if (type == CLAMP_UINT8)
    {
        max = UINT8_MAX;
    }
    else if (type == CLAMP_UINT16)
    {
        max = UINT16_MAX;
    }

    // Scale each element with overflow detection
    for (size_t i = 0U; i < size; ++i)
    {
        if ((factor != 0U) && (array[i] > (max / factor)))
        {
            array[i] = max; // Clamp on overflow
            clamped = true;
        }
        else
        {
            array[i] *= factor;
        }
    }

    return clamped ? ARRAY_STATUS_WARNING_OVERFLOW_CLAMP : ARRAY_STATUS_OK;
}

#endif // ARRAY_TRANSFORM_H
