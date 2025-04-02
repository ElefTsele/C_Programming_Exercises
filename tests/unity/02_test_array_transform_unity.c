#include "array/array_transform.h"
#include "unity.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static int32_t g_original_array[] = {-8, -9, 12, 9, 1, 8, 5, 7, 3};
static const size_t g_array_length = sizeof(g_original_array) / sizeof(g_original_array[0]);
static int32_t g_test_array[16];

void setUp(void)
{
    (void) memcpy(g_test_array, g_original_array, sizeof(g_original_array));
}

void tearDown(void) {}

static void assert_arrays_equal(const int32_t* expected, const int32_t* actual, size_t length)
{
    size_t index = 0U;
    for (index = 0U; index < length; ++index)
    {
        TEST_ASSERT_EQUAL_INT32(expected[index], actual[index]);
    }
}

// ----------- array_clamp tests -----------
void test_Clamp_valid_range(void)
{
    const array_status_t status = array_clamp(g_test_array, g_array_length, 3, 6);
    TEST_ASSERT_EQUAL_INT32(ARRAY_STATUS_OK, status);

    const int32_t expected[] = {3, 3, 6, 6, 3, 6, 5, 6, 3};
    assert_arrays_equal(expected, g_test_array, g_array_length);
}

void test_Clamp_invalid_range_min_greater_than_max(void)
{
    const array_status_t status = array_clamp(g_test_array, g_array_length, 10, 2);
    TEST_ASSERT_EQUAL_INT32(ARRAY_STATUS_ERROR_INVALID_INPUT, status);
    assert_arrays_equal(g_original_array, g_test_array, g_array_length);
}

void test_Clamp_zero_size(void)
{
    const array_status_t status = array_clamp(g_test_array, 0U, 0, 10);
    TEST_ASSERT_EQUAL_INT32(ARRAY_STATUS_ERROR_EMPTY, status);
}

void test_Clamp_NULL_pointer(void)
{
    const array_status_t status = array_clamp(NULL, g_array_length, 0, 5);
    TEST_ASSERT_EQUAL_INT32(ARRAY_STATUS_ERROR_NULL, status);
}

int main(void)
{
    UNITY_BEGIN();

    // ----------- array_clamp tests -----------
    RUN_TEST(test_Clamp_valid_range);
    RUN_TEST(test_Clamp_invalid_range_min_greater_than_max);
    RUN_TEST(test_Clamp_zero_size);
    RUN_TEST(test_Clamp_NULL_pointer);

    return UNITY_END();
}
