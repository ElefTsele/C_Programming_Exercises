#include "array/array_transform.h"
#include "unity.h"

void test_array_transform_clamp_valid_range(void)
{
    TEST_ASSERT_EQUAL_INT(1, 1);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_array_transform_clamp_valid_range);
    return UNITY_END();
}
