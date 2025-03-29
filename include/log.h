#ifndef LOG_H
#define LOG_H

#include <stdio.h>

/**
 * @brief Enables logging macros when defined via Makefile.
 *
 * To enable logging, add -DDEBUG_LOG_ENABLED to the CFLAGS.
 */
#ifdef DEBUG_LOG_ENABLED
#define LOG_DEBUG(fmt, ...) fprintf(stderr, "[DEBUG] " fmt "\n", ##__VA_ARGS__)
#define LOG_TEST(fmt, ...) fprintf(stderr, "[TEST]  " fmt "\n", ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) fprintf(stderr, "E> " fmt "\n", ##__VA_ARGS__)
#define LOG_TEST_OK(fmt, ...) fprintf(stderr, "T> " fmt "\n", ##__VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...)
#define LOG_TEST(fmt, ...)
#define LOG_ERROR(fmt, ...)
#define LOG_TEST_OK(fmt, ...)
#endif

#endif // LOG_H