#include "array/array_transform.h"
#include "unity.h"

void test_clamp_valid_range(void)
{
    int32_t arr[] = {1, 2, 3};
    array_clamp(arr, 3, 2, 2);
    TEST_ASSERT_EQUAL_INT32(2, arr[0]);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_clamp_valid_range);
    return UNITY_END();
}
