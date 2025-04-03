#include "array/array_debug.h"
#include "array/array_transform.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    const int32_t original_array[] = {-8, -9, 12, 9, 1, 8, 5, 7, 3};
    size_t size = sizeof(original_array) / sizeof(original_array[0]);

    int32_t test_array[size];

    int32_t min = 3;
    int32_t max = 6;
    int32_t scale_factor = 3;

    array_status_t status;

    // -------------------------------------------
    // Test Clamp
    // -------------------------------------------
    memcpy(test_array, original_array, sizeof(original_array));
    printf("\nOriginal array for clamp test:\n");
    array_print(test_array, size);

    status = array_clamp(test_array, size, min, max);
    if (status != ARRAY_STATUS_OK)
    {
        printf("Failed to clamp the array (error code: %d)\n", status);
    }
    else
    {
        printf("Clamped array (min=%d, max=%d):\n", min, max);
        array_print(test_array, size);
    }

    // -------------------------------------------
    // Test Scale
    // -------------------------------------------
    memcpy(test_array, original_array, sizeof(original_array));
    printf("\nOriginal array for scale test:\n");
    array_print(test_array, size);

    status = array_scale_safe(test_array, size, scale_factor, CLAMP_INT32);
    if (status == ARRAY_STATUS_WARNING_OVERFLOW_CLAMP)
    {
        printf("Warning: Overflow occurred, values clamped.\n");
    }
    else if (status != ARRAY_STATUS_OK)
    {
        printf("Failed to scale the array (error code: %d)\n", status);
    }

    printf("Scaled array (factor=%d):\n", scale_factor);
    array_print(test_array, size);
    printf("\n");

    return 0;
}
