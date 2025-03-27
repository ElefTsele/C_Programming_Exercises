#include <stdio.h>
#include "array_utils.h"
#include "common_macros.h"  // for ARRAY_SIZE()

int main(void)
{
    int my_array[] = {5, 2, 6, 2, 7, 32, 7};
    size_t array_size = ARRAY_SIZE(my_array);

    int min = 0;
    int max = 0;

    // Find minimum value in the array
    ArrayStatus status = array_find_min(my_array, array_size, &min);
    if (status != ARRAY_OK) {
        printf("Failed to find minimum (error code: %d)\n", status);
    } else {
        printf("Minimum value: %d\n", min);
    }

    // Find maximum value in the array
    status = array_find_max(my_array, array_size, &max);
    if (status != ARRAY_OK) {
        printf("Failed to find maximum (error code: %d)\n", status);
    } else {
        printf("Maximum value: %d\n", max);
    }

    return 0;
}
