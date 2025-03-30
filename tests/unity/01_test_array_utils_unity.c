#include "array_utils.h"
#include "unity.h"

// Optional setup function (before each test)
void setUp(void) {}

// Optional teardown function (after each test)
void tearDown(void) {}

void test_array_min_should_return_min(void)
{
    int array[] = {5, 2, 9, 3};
    int result = 0;
    ArrayStatus status = array_min(array, 4, &result);

    TEST_ASSERT_EQUAL(ARRAY_OK, status);
    TEST_ASSERT_EQUAL(2, result);
}

void test_array_max_should_return_max(void)
{
    int array[] = {1, 8, 4, 7};
    int result = 0;
    ArrayStatus status = array_max(array, 4, &result);

    TEST_ASSERT_EQUAL(ARRAY_OK, status);
    TEST_ASSERT_EQUAL(8, result);
}

void test_array_min_should_return_error_on_null_pointer(void)
{
    int result = 0;
    ArrayStatus status = array_min(NULL, 4, &result);
    TEST_ASSERT_EQUAL(ARRAY_ERROR_NULL, status);
}

void test_array_max_should_return_error_on_empty_array(void)
{
    int array[] = {};
    int result = 0;
    ArrayStatus status = array_max(array, 0, &result);
    TEST_ASSERT_EQUAL(ARRAY_ERROR_EMPTY, status);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_array_min_should_return_min);
    RUN_TEST(test_array_max_should_return_max);
    RUN_TEST(test_array_min_should_return_error_on_null_pointer);
    RUN_TEST(test_array_max_should_return_error_on_empty_array);

    return UNITY_END();
}
