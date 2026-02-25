#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <string.h>

static int __tests_passed  = 0;
static int __tests_failed  = 0;
static int __current_failed = 0;

#define ASSERT_TRUE(expr) do { \
    if (!(expr)) { \
        printf("  assertion failed at line %d: %s\n", __LINE__, #expr); \
        __current_failed = 1; \
    } \
} while(0)

#define ASSERT_EQ(a, b)     ASSERT_TRUE((a) == (b))
#define ASSERT_STR_EQ(a, b) ASSERT_TRUE((a) != NULL && strcmp((a), (b)) == 0)
#define ASSERT_NOT_NULL(p)  ASSERT_TRUE((p) != NULL)
#define ASSERT_NULL(p)      ASSERT_TRUE((p) == NULL)

#define RUN_TEST(fn) do { \
    __current_failed = 0; \
    fn(); \
    if (__current_failed) { \
        printf("[FAIL] " #fn "\n"); \
        __tests_failed++; \
    } else { \
        printf("[PASS] " #fn "\n"); \
        __tests_passed++; \
    } \
} while(0)

#define TEST_SUMMARY() do { \
    printf("\n%d passed, %d failed\n", __tests_passed, __tests_failed); \
    return __tests_failed > 0 ? 1 : 0; \
} while(0)

#endif
