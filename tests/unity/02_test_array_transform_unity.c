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
void test_array_transform_clamp_valid_range(void)
{
    const array_status_t status = array_clamp(g_test_array, g_array_length, 3, 6);
    TEST_ASSERT_EQUAL_INT32(ARRAY_STATUS_OK, status);

    const int32_t expected[] = {3, 3, 6, 6, 3, 6, 5, 6, 3};
    assert_arrays_equal(expected, g_test_array, g_array_length);
}

void test_array_transform_clamp_invalid_range_min_greater_than_max(void)
{
    const array_status_t status = array_clamp(g_test_array, g_array_length, 10, 2);
    TEST_ASSERT_EQUAL_INT32(ARRAY_STATUS_ERROR_INVALID_INPUT, status);
    assert_arrays_equal(g_original_array, g_test_array, g_array_length);
}

void test_array_transform_clamp_zero_size(void)
{
    const array_status_t status = array_clamp(g_test_array, 0U, 0, 10);
    TEST_ASSERT_EQUAL_INT32(ARRAY_STATUS_ERROR_EMPTY, status);
}

void test_array_transform_clamp_null_pointer(void)
{
    const array_status_t status = array_clamp(NULL, g_array_length, 0, 5);
    TEST_ASSERT_EQUAL_INT32(ARRAY_STATUS_ERROR_NULL, status);
}

// ----------- array_scale tests -----------

void test_array_transform_scale_safe_no_overflow(void)
{
    setUp();
    const array_status_t status = array_scale(g_test_array, g_array_length, 2, CLAMP_INT32);
    TEST_ASSERT_EQUAL_INT32(ARRAY_STATUS_OK, status);

    const int32_t expected[] = {-16, -18, 24, 18, 2, 16, 10, 14, 6};
    assert_arrays_equal(expected, g_test_array, g_array_length);
}

void test_array_transform_scale_safe_with_overflow(void)
{
    /* Using a large scale to trigger overflow with INT8 clamp */
    const array_status_t status = array_scale(g_test_array, g_array_length, 100, CLAMP_INT8);
    TEST_ASSERT_EQUAL_INT32(ARRAY_STATUS_WARNING_OVERFLOW_CLAMP, status);

    const int32_t expected[] = {-128, -128, 127, 127, 100, 127, 127, 127, 127};
    assert_arrays_equal(expected, g_test_array, g_array_length);
}

void test_array_transform_scale_safe_zero_size(void)
{
    const array_status_t status = array_scale(g_test_array, 0U, 10, CLAMP_INT32);
    TEST_ASSERT_EQUAL_INT32(ARRAY_STATUS_ERROR_EMPTY, status);
}

void test_array_transform_scale_safe_null_pointer(void)
{
    const array_status_t status = array_scale(NULL, g_array_length, 10, CLAMP_INT32);
    TEST_ASSERT_EQUAL_INT32(ARRAY_STATUS_ERROR_NULL, status);
}

// ----------- array_offset_safe tests -----------

void test_array_transform_offset_safe_signed(void)
{
    setUp();
    const array_status_t status = array_offset(g_test_array, g_array_length, 3, CLAMP_INT8);
    TEST_ASSERT_EQUAL_INT32(ARRAY_STATUS_WARNING_OVERFLOW_CLAMP, status);
    const int32_t expected[] = {-105, -106, 115, 112, 4, 111, 108, 110, 106};
    assert_arrays_equal(expected, g_test_array, g_array_length);
}

void test_array_transform_offset_safe_unsigned(void)
{
    uint32_t unsigned_array[] = {240, 250, 100, 0};
    const size_t size = sizeof(unsigned_array) / sizeof(unsigned_array[0]);
    const array_status_t status = array_offset_uint(unsigned_array, size, 20, CLAMP_UINT8);
    TEST_ASSERT_EQUAL_INT32(ARRAY_STATUS_WARNING_OVERFLOW_CLAMP, status);
    const uint32_t expected[] = {255, 255, 120, 20};
    for (size_t i = 0; i < size; ++i)
    {
        TEST_ASSERT_EQUAL_UINT32(expected[i], unsigned_array[i]);
    }
}

void test_array_transform_scale_unsigned_with_overflow(void)
{
    uint32_t unsigned_array[] = {100, 200, 300, 400};
    const size_t size = sizeof(unsigned_array) / sizeof(unsigned_array[0]);
    const array_status_t status = array_scale_uint(unsigned_array, size, 3, CLAMP_UINT8);
    TEST_ASSERT_EQUAL_INT32(ARRAY_STATUS_WARNING_OVERFLOW_CLAMP, status);
    const uint32_t expected[] = {300, 255, 255, 255};
    for (size_t i = 0; i < size; ++i)
    {
        TEST_ASSERT_EQUAL_UINT32(expected[i], unsigned_array[i]);
    }
}

int main(void)
{
    UNITY_BEGIN();

    // ----------- array_clamp tests -----------
    RUN_TEST(test_array_transform_clamp_valid_range);
    RUN_TEST(test_array_transform_clamp_invalid_range_min_greater_than_max);
    RUN_TEST(test_array_transform_clamp_zero_size);
    RUN_TEST(test_array_transform_clamp_null_pointer);

    // ----------- array_scale_safe tests -----------
    RUN_TEST(test_array_transform_scale_safe_no_overflow);
    RUN_TEST(test_array_transform_scale_safe_with_overflow);
    RUN_TEST(test_array_transform_scale_safe_zero_size);
    RUN_TEST(test_array_transform_scale_safe_null_pointer);

    // ----------- array_offset_safe tests -----------
    RUN_TEST(test_array_transform_offset_safe_signed);
    RUN_TEST(test_array_transform_offset_safe_unsigned);
    RUN_TEST(test_array_transform_scale_unsigned_with_overflow);

    return UNITY_END();
}
