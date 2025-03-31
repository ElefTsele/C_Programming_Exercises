#include "array_utils.h"
#include "common_macros.h" // for ARRAY_SIZE()
#include <stdio.h>

int main(void)
{
    int my_array[] = {5, 2, 6, 2, 7, 32, 7};
    size_t array_size = ARRAY_SIZE(my_array);

    int min = 0;
    int max = 0;
    int sum = 0;

    // Finds the minimum value in an integer array.
    array_status_t status = array_min(my_array, array_size, &min);
    if (status != ARRAY_STATUS_OK)
    {
        printf("Failed to find minimum (error code: %d)\n", status);
    }
    else
    {
        printf("Minimum value: %d\n", min);
    }

    // Finds the maximum value in an integer array.
    status = array_max(my_array, array_size, &max);
    if (status != ARRAY_STATUS_OK)
    {
        printf("Failed to find maximum (error code: %d)\n", status);
    }
    else
    {
        printf("Maximum value: %d\n", max);
    }

    // Calculates the summation value of an integer array.
    status = array_sum(my_array, array_size, &sum);
    if (status != ARRAY_STATUS_OK)
    {
        printf("Failed to calculate the summation (error code: %d)\n", status);
    }
    else
    {
        printf("Summation value: %d\n", sum);
    }

    return 0;
}
