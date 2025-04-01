#include "array/array_debug.h"
#include "array/array_transform.h"
#include <stdio.h>

int main(void)
{
    int my_array[] = {-8, -9, 12, 9, 1, 8, 5, 7, 3};
    size_t size = sizeof(my_array) / sizeof(my_array[0]);
    int min = 3;
    int max = 6;

    printf("Original array:\n");
    array_print(my_array, size);

    // Clamps each element of the array to a specified [min, max] range.
    array_status_t status = array_clamp(my_array, size, min, max);

    if (status != ARRAY_STATUS_OK)
    {
        printf("Failed to clamp the array (error code: %d)\n", status);
    }
    else
    {
        printf("Clamp(min=%d,max=%d)\n", min, max);
        array_print(my_array, size);
    }

    return 0;
}
