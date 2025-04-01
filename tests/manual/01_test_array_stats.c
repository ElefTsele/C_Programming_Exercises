// No manual test created for array_sum – Unity test provides full coverage.
// No manual test created for array_mean – Unity test provides full coverage.

#include "array/array_stats.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    int a[] = {3, 5, 1, 8, 2};
    int result;

    // Test min.
    array_status_t s = array_min(a, 5, &result);
    assert(s == ARRAY_STATUS_OK);
    assert(result == 1);

    // Test max.
    s = array_max(a, 5, &result);
    assert(s == ARRAY_STATUS_OK);
    assert(result == 8);

    // Test error: size == 0.
    s = array_min(a, 0, &result);
    assert(s == ARRAY_STATUS_ERROR_EMPTY);

    // Test error: NULL pointer.
    s = array_max(NULL, 5, &result);
    assert(s == ARRAY_STATUS_ERROR_NULL);

    s = array_max(a, 5, NULL);
    assert(s == ARRAY_STATUS_ERROR_NULL);

    // Tests passed.
    printf("All tests passed.\n");

    return 0;
}