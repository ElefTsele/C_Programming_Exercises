#include "array/array_debug.h"
#include "array/array_transform.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    const int32_t* array_s;
    const uint32_t* array_u;
    size_t size;
    int32_t min;
    int32_t max;
    int32_t scale;
    int32_t offset;
    uint32_t scale_u;
    uint32_t offset_u;
} ExampleContext;

static void init_example_context(ExampleContext* ctx)
{
    static const int32_t original_array[] = {-8, -9, 12, 9, 1, 8, 5, 7, 3};
    static const uint32_t original_array_u[] = {8, 9, 12, 9, 1, 8, 5, 7, 3};
    size_t size = sizeof(original_array) / sizeof(original_array[0]);

    ctx->array_s = original_array;
    ctx->array_u = original_array_u;
    ctx->size = size;

    ctx->min = 3;
    ctx->max = 6;
    ctx->scale = 3;
    ctx->offset = 10;

    ctx->scale_u = 50;
    ctx->offset_u = 250;
}

/* =============================== *
 *         EXAMPLE: CLAMP         *
 * =============================== */
static void run_example_clamp(const ExampleContext* ctx)
{
    int32_t array[ctx->size];
    memcpy(array, ctx->array_s, ctx->size * sizeof(int32_t));

    printf("\n[Clamp] Original array:\n");
    array_print(array, ctx->size);

    array_status_t status = array_clamp(array, ctx->size, ctx->min, ctx->max);
    if (status != ARRAY_STATUS_OK)
        printf("Clamp failed (status=%d)\n", status);
    else
    {
        printf("Clamped array to range [%d, %d]:\n", ctx->min, ctx->max);
        array_print(array, ctx->size);
    }
}

/* =============================== *
 *         EXAMPLE: SCALE         *
 * =============================== */
static void run_example_scale(const ExampleContext* ctx)
{
    int32_t array[ctx->size];
    memcpy(array, ctx->array_s, ctx->size * sizeof(int32_t));

    printf("\n[Scale] Original array:\n");
    array_print(array, ctx->size);

    array_status_t status = array_scale(array, ctx->size, ctx->scale, CLAMP_INT32);
    if (status == ARRAY_STATUS_WARNING_OVERFLOW_CLAMP)
        printf("Scale warning: Overflow occurred, values clamped.\n");
    else if (status != ARRAY_STATUS_OK)
        printf("Scale failed (status=%d)\n", status);

    printf("Scaled array by factor %d:\n", ctx->scale);
    array_print(array, ctx->size);
}

/* =============================== *
 *         EXAMPLE: OFFSET        *
 * =============================== */
static void run_example_offset(const ExampleContext* ctx)
{
    int32_t array[ctx->size];
    memcpy(array, ctx->array_s, ctx->size * sizeof(int32_t));

    printf("\n[Offset] Original array:\n");
    array_print(array, ctx->size);

    array_status_t status = array_offset(array, ctx->size, ctx->offset, CLAMP_INT16);
    if (status == ARRAY_STATUS_WARNING_OVERFLOW_CLAMP)
        printf("Offset warning: Overflow occurred, values clamped.\n");
    else if (status != ARRAY_STATUS_OK)
        printf("Offset failed (status=%d)\n", status);

    printf("Offset array by value %d:\n", ctx->offset);
    array_print(array, ctx->size);
}

/* =============================== *
 *      EXAMPLE: SCALE UNSIGNED   *
 * =============================== */
static void run_example_scale_uint(const ExampleContext* ctx)
{
    uint32_t array[ctx->size];
    memcpy(array, ctx->array_u, ctx->size * sizeof(uint32_t));

    printf("\n[Scale Unsigned] Original array:\n");
    array_print_u(array, ctx->size);

    array_status_t status = array_scale_uint(array, ctx->size, ctx->scale_u, CLAMP_UINT8);
    if (status == ARRAY_STATUS_WARNING_OVERFLOW_CLAMP)
        printf("Unsigned scale warning: Overflow occurred, values clamped.\n");
    else if (status != ARRAY_STATUS_OK)
        printf("Unsigned scale failed (status=%d)\n", status);

    printf("Scaled unsigned array by %u:\n", ctx->scale_u);
    array_print_u(array, ctx->size);
}

/* =============================== *
 *     EXAMPLE: OFFSET UNSIGNED   *
 * =============================== */
static void run_example_offset_uint(const ExampleContext* ctx)
{
    uint32_t array[ctx->size];
    memcpy(array, ctx->array_u, ctx->size * sizeof(uint32_t));

    printf("\n[Offset Unsigned] Original array:\n");
    array_print_u(array, ctx->size);

    array_status_t status = array_offset_uint(array, ctx->size, ctx->offset_u, CLAMP_UINT8);
    if (status == ARRAY_STATUS_WARNING_OVERFLOW_CLAMP)
        printf("Unsigned offset warning: Overflow occurred, values clamped.\n");
    else if (status != ARRAY_STATUS_OK)
        printf("Unsigned offset failed (status=%d)\n", status);

    printf("Offset unsigned array by %u:\n", ctx->offset_u);
    array_print_u(array, ctx->size);
}

int main(void)
{
    ExampleContext ctx;
    init_example_context(&ctx);

    run_example_clamp(&ctx);
    run_example_scale(&ctx);
    run_example_offset(&ctx);
    run_example_scale_uint(&ctx);
    run_example_offset_uint(&ctx);

    return 0;
}
