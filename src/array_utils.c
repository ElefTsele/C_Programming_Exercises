#include "array_utils.h"
#include <stdio.h>

#define DEBUG_LOG_ENABLED

#ifdef DEBUG_LOG_ENABLED
#define LOG_ERROR(msg) printf("[ERROR] %s\n", msg)
#else
#define LOG_ERROR(msg)
#endif

/**
 * @brief Internal implementation of array_find_min.
 */
ArrayStatus array_find_min(const int* array, size_t size, int* out_min)
{
    if (array == NULL || out_min == NULL)
    {
        LOG_ERROR("array_find_min: NULL pointer");
        return ARRAY_ERROR_NULL;
    }

    if (size == 0)
    {
        LOG_ERROR("array_find_min: size is zero");
        return ARRAY_ERROR_EMPTY;
    }

    int min = array[0];
    for (size_t i = 1; i < size; i++)
    {
        if (array[i] < min)
            min = array[i];
    }

    *out_min = min;
    return ARRAY_OK;
}

/**
 * @brief Internal implementation of array_find_max.
 */
ArrayStatus array_find_max(const int* array, size_t size, int* out_max)
{
    if (array == NULL || out_max == NULL)
    {
        LOG_ERROR("array_find_max: NULL pointer");
        return ARRAY_ERROR_NULL;
    }

    if (size == 0)
    {
        LOG_ERROR("array_find_max: size is zero");
        return ARRAY_ERROR_EMPTY;
    }

    int max = array[0];
    for (size_t i = 1; i < size; i++)
    {
        if (array[i] > max)
            max = array[i];
    }

    *out_max = max;
    return ARRAY_OK;
}
