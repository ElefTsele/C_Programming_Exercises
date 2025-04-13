#include "array/array_debug.h"
#include "array/array_transform.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const int32_t original_array[] = {-8, -9, 12, 9, 1, 8, 5, 7, 3};
    size_t size = sizeof(original_array) / sizeof(original_array[0]);
    int32_t test_array[size];
    array_status_t status;

    int32_t min = 3;
    int32_t max = 6;
    int32_t scale_factor = 3;
    int32_t offset_value = 10;

    // -------------------------------------------
    // Test Clamp
    // -------------------------------------------
    memcpy(test_array, original_array, sizeof(original_array));
    printf("\n[Clamp] Original array:\n");
    array_print(test_array, size);

    status = array_clamp(test_array, size, min, max);
    if (status != ARRAY_STATUS_OK)
    {
        printf("Clamp failed (status=%d)\n", status);
    }
    else
    {
        printf("Clamped array to range [%d, %d]:\n", min, max);
        array_print(test_array, size);
    }

    // -------------------------------------------
    // Test Scale (Signed)
    // -------------------------------------------
    memcpy(test_array, original_array, sizeof(original_array));
    printf("\n[Scale] Original array:\n");
    array_print(test_array, size);

    status = array_scale(test_array, size, scale_factor, CLAMP_INT32);
    if (status == ARRAY_STATUS_WARNING_OVERFLOW_CLAMP)
    {
        printf("Scale warning: Overflow occurred, values clamped.\n");
    }
    else if (status != ARRAY_STATUS_OK)
    {
        printf("Scale failed (status=%d)\n", status);
    }
    printf("Scaled array by factor %d:\n", scale_factor);
    array_print(test_array, size);

    // -------------------------------------------
    // Test Offset (Signed)
    // -------------------------------------------
    memcpy(test_array, original_array, sizeof(original_array));
    printf("\n[Offset] Original array:\n");
    array_print(test_array, size);

    status = array_offset(test_array, size, offset_value, CLAMP_INT16);
    if (status == ARRAY_STATUS_WARNING_OVERFLOW_CLAMP)
    {
        printf("Offset warning: Overflow occurred, values clamped.\n");
    }
    else if (status != ARRAY_STATUS_OK)
    {
        printf("Offset failed (status=%d)\n", status);
    }
    printf("Offset array by value %d:\n", offset_value);
    array_print(test_array, size);

    // -------------------------------------------
    // Test Unsigned Scale
    // -------------------------------------------
    const uint32_t original_array_u[] = {8, 9, 12, 9, 1, 8, 5, 7, 3};
    uint32_t test_array_u[size];
    memcpy(test_array_u, original_array_u, sizeof(original_array_u));
    printf("\n[Scale Unsigned] Original array:\n");
    array_print_u(test_array_u, size);

    status = array_scale_uint(test_array_u, size, 50, CLAMP_UINT8);
    if (status == ARRAY_STATUS_WARNING_OVERFLOW_CLAMP)
    {
        printf("Unsigned scale warning: Overflow occurred, values clamped.\n");
    }
    else if (status != ARRAY_STATUS_OK)
    {
        printf("Unsigned scale failed (status=%d)\n", status);
    }
    printf("Scaled unsigned array by 50:\n");
    array_print_u(test_array_u, size);

    // -------------------------------------------
    // Test Unsigned Offset
    // -------------------------------------------
    memcpy(test_array_u, original_array_u, sizeof(original_array_u));
    printf("\n[Offset Unsigned] Original array:\n");
    array_print_u(test_array_u, size);

    status = array_offset_uint(test_array_u, size, 250, CLAMP_UINT8);
    if (status == ARRAY_STATUS_WARNING_OVERFLOW_CLAMP)
    {
        printf("Unsigned offset warning: Overflow occurred, values clamped.\n");
    }
    else if (status != ARRAY_STATUS_OK)
    {
        printf("Unsigned offset failed (status=%d)\n", status);
    }
    printf("Offset unsigned array by 250:\n");
    array_print_u(test_array_u, size);

    return 0;
}
