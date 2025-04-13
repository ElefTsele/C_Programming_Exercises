#include "array/array_stats.h"
#include "unity.h"

// ----------- array_min/max tests -----------
void test_array_min_should_return_min(void)
{
    int array[] = {5, 2, 9, 3};
    int result = 0;
    array_status_t status = array_min(array, 4, &result);

    TEST_ASSERT_EQUAL(ARRAY_STATUS_OK, status);
    TEST_ASSERT_EQUAL(2, result);
}

void test_array_max_should_return_max(void)
{
    int array[] = {1, 8, 4, 7};
    int result = 0;
    array_status_t status = array_max(array, 4, &result);

    TEST_ASSERT_EQUAL(ARRAY_STATUS_OK, status);
    TEST_ASSERT_EQUAL(8, result);
}

void test_array_min_should_return_error_on_null_pointer(void)
{
    int result = 0;
    array_status_t status = array_min(NULL, 4, &result);
    TEST_ASSERT_EQUAL(ARRAY_STATUS_ERROR_NULL, status);
}

void test_array_max_should_return_error_on_empty_array(void)
{
    int array[] = {0};
    int result = 0;
    array_status_t status = array_max(array, 0, &result);
    TEST_ASSERT_EQUAL(ARRAY_STATUS_ERROR_EMPTY, status);
}

// ----------- array_sum tests -----------
void test_array_sum_should_return_correct_sum(void)
{
    int array[] = {1, 2, 8, 9};
    int result = 0;
    array_status_t status = array_sum(array, 4, &result);
    TEST_ASSERT_EQUAL(ARRAY_STATUS_OK, status);
    TEST_ASSERT_EQUAL(20, result);
}

void test_array_sum_should_return_error_on_null_input_pointer(void)
{
    int result = 0;
    array_status_t status = array_sum(NULL, 4, &result);
    TEST_ASSERT_EQUAL(ARRAY_STATUS_ERROR_NULL, status);
}
void test_array_sum_should_return_error_on_null_output_pointer(void)
{
    int array[] = {1, 2, 8, 9};
    array_status_t status = array_sum(array, 4, NULL);
    TEST_ASSERT_EQUAL(ARRAY_STATUS_ERROR_NULL, status);
}

void test_array_sum_should_return_error_on_empty_array(void)
{
    int array[] = {0};
    int result = 0;
    array_status_t status = array_sum(array, 0, &result);
    TEST_ASSERT_EQUAL(ARRAY_STATUS_ERROR_EMPTY, status);
}

void test_array_sum_should_handle_negative_numbers(void)
{
    int array[] = {-2, 5, -3, 4}; // sum = 4.
    int result = 0;
    array_status_t status = array_sum(array, 4, &result);
    TEST_ASSERT_EQUAL(ARRAY_STATUS_OK, status);
    TEST_ASSERT_EQUAL(4, result);
}

// ----------- array_mean tests -----------
void test_array_mean_should_return_correct_mean(void)
{
    int array[] = {4, 6, 8, 2}; // sum = 20, mean = 5
    int result = 0;
    array_status_t status = array_mean(array, 4, &result);
    TEST_ASSERT_EQUAL(ARRAY_STATUS_OK, status);
    TEST_ASSERT_EQUAL(5, result);
}

void test_array_mean_should_return_error_on_null_input_pointer(void)
{
    int result = 0;
    array_status_t status = array_mean(NULL, 4, &result);
    TEST_ASSERT_EQUAL(ARRAY_STATUS_ERROR_NULL, status);
}

void test_array_mean_should_return_error_on_null_output_pointer(void)
{
    int array[] = {1, 2, 3};
    array_status_t status = array_mean(array, 3, NULL);
    TEST_ASSERT_EQUAL(ARRAY_STATUS_ERROR_NULL, status);
}

void test_array_mean_should_return_error_on_zero_size(void)
{
    int array[] = {0};
    int result = 0;
    array_status_t status = array_mean(array, 0, &result);
    TEST_ASSERT_EQUAL(ARRAY_STATUS_ERROR_EMPTY, status);
}

void test_array_mean_with_single_element(void)
{
    int array[] = {42};
    int result = 0;
    array_status_t status = array_mean(array, 1, &result);
    TEST_ASSERT_EQUAL(ARRAY_STATUS_OK, status);
    TEST_ASSERT_EQUAL(42, result);
}

void test_array_mean_with_negative_numbers(void)
{
    int array[] = {-2, 6, -4, 10}; // sum = 10, mean = 2
    int result = 0;
    array_status_t status = array_mean(array, 4, &result);
    TEST_ASSERT_EQUAL(ARRAY_STATUS_OK, status);
    TEST_ASSERT_EQUAL(2, result);
}

int main(void)
{
    UNITY_BEGIN();

    // ----------- array_min/max tests -----------
    RUN_TEST(test_array_min_should_return_min);
    RUN_TEST(test_array_max_should_return_max);
    RUN_TEST(test_array_min_should_return_error_on_null_pointer);
    RUN_TEST(test_array_max_should_return_error_on_empty_array);

    // ----------- array_sum tests -----------
    RUN_TEST(test_array_sum_should_return_correct_sum);
    RUN_TEST(test_array_sum_should_return_error_on_null_input_pointer);
    RUN_TEST(test_array_sum_should_return_error_on_null_output_pointer);
    RUN_TEST(test_array_sum_should_return_error_on_empty_array);
    RUN_TEST(test_array_sum_should_handle_negative_numbers);

    // ----------- array_mean tests -----------
    RUN_TEST(test_array_mean_should_return_correct_mean);
    RUN_TEST(test_array_mean_should_return_error_on_null_input_pointer);
    RUN_TEST(test_array_mean_should_return_error_on_null_output_pointer);
    RUN_TEST(test_array_mean_should_return_error_on_zero_size);
    RUN_TEST(test_array_mean_with_single_element);
    RUN_TEST(test_array_mean_with_negative_numbers);

    return UNITY_END();
}