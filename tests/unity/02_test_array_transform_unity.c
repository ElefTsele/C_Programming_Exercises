#include "array/array_transform.h"
#include "unity.h"
#include <stddef.h> // size_t
#include <string.h> // for memcpy

// ---------------------------------------------------------------------
// array_clamp(int *array, size_t size, int min, int max)
//
// Returns ARRAY_STATUS_OK if successful,
// or an error code like ARRAY_STATUS_ERROR_INVALID_INPUT.
//
// It clamps each element of the array to the [min, max] range.
// Example: for min=3, max=6
//   -8 -> 3,  12 -> 6, 5 -> 5
// ---------------------------------------------------------------------

// Static base array used in all tests
static int original_array[] = {-8, -9, 12, 9, 1, 8, 5, 7, 3};
static const size_t array_len = sizeof(original_array) / sizeof(original_array[0]);

// Test array copied from original before each test
static int test_array[16];

void setUp(void)
{
    // Restore test_array to known state before each test
    memcpy(test_array, original_array, sizeof(original_array));
}

void tearDown(void)
{
    // No teardown needed for these tests
}

// ---------------------------------------------------------------------
// Test 1: Valid range, normal operation
// ---------------------------------------------------------------------
void test_Clamp_valid_range(void)
{
    array_status_t status = array_clamp(test_array, array_len, 3, 6);
    TEST_ASSERT_EQUAL_INT_MESSAGE(ARRAY_STATUS_OK, status,
                                  "Expected ARRAY_STATUS_OK on valid clamp");

    int expected[] = {3, 3, 6, 6, 3, 6, 5, 6, 3};
    for (size_t i = 0; i < array_len; i++)
    {
        TEST_ASSERT_EQUAL_INT(expected[i], test_array[i]);
    }
}

// ---------------------------------------------------------------------
// Test 2: min > max → invalid input
// ---------------------------------------------------------------------
void test_Clamp_invalid_range_min_greater_than_max(void)
{
    array_status_t status = array_clamp(test_array, array_len, 10, 2);

    TEST_ASSERT_EQUAL_INT_MESSAGE(ARRAY_STATUS_ERROR_INVALID_INPUT, status,
                                  "Expected ARRAY_STATUS_ERROR_INVALID_INPUT when min > max");

    for (size_t i = 0; i < array_len; i++)
    {
        TEST_ASSERT_EQUAL_INT(original_array[i], test_array[i]);
    }
}

// ---------------------------------------------------------------------
// Test 3: Zero-sized array
// ---------------------------------------------------------------------
void test_Clamp_zero_size(void)
{
    array_status_t status = array_clamp(test_array, 0, 0, 10);
    TEST_ASSERT_EQUAL_INT_MESSAGE(ARRAY_STATUS_ERROR_EMPTY, status,
                                  "Expected ARRAY_STATUS_ERROR_EMPTY for size=0");
}

// ---------------------------------------------------------------------
// Test 4: NULL pointer
// ---------------------------------------------------------------------
void test_Clamp_NULL_pointer(void)
{
    array_status_t status = array_clamp(NULL, array_len, 0, 5);
    TEST_ASSERT_EQUAL_INT_MESSAGE(ARRAY_STATUS_ERROR_NULL, status,
                                  "Expected ARRAY_STATUS_ERROR_NULL for NULL pointer");
}

// ---------------------------------------------------------------------
// Optional ideas (not implemented yet)
// ---------------------------------------------------------------------
// void test_Clamp_exceed_array_bounds(void)
// {
//     // Test with size greater than actual array size
// }

// ---------------------------------------------------------------------
// Main test runner
// ---------------------------------------------------------------------
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_Clamp_valid_range);
    RUN_TEST(test_Clamp_invalid_range_min_greater_than_max);
    RUN_TEST(test_Clamp_zero_size);
    RUN_TEST(test_Clamp_NULL_pointer);
    // RUN_TEST(test_Clamp_exceed_array_bounds);

    return UNITY_END();
}
