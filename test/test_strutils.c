#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test/test_framework.h"
#include "strutils.h"

static void test_replace_basic(void) {
    char *r = replace("hello world", 'o', "0");
    ASSERT_STR_EQ(r, "hell0 w0rld");
    free(r);
}

static void test_replace_single(void) {
    char *r = replace("hello", 'h', "H");
    ASSERT_STR_EQ(r, "Hello");
    free(r);
}

static void test_replace_none(void) {
    char *r = replace("hello", 'z', "Z");
    ASSERT_STR_EQ(r, "hello");
    free(r);
}

static void test_replace_empty_input(void) {
    char *r = replace("", 'a', "b");
    ASSERT_STR_EQ(r, "");
    free(r);
}

static void test_replace_multichar_repl(void) {
    char *r = replace("a.b.c", '.', "::");
    ASSERT_STR_EQ(r, "a::b::c");
    free(r);
}

static void test_push_str_basic(void) {
    char *s = malloc(6);
    strcpy(s, "hello");
    s = push_str(s, " world");
    ASSERT_STR_EQ(s, "hello world");
    free(s);
}

static void test_push_str_empty_append(void) {
    char *s = malloc(6);
    strcpy(s, "hello");
    s = push_str(s, "");
    ASSERT_STR_EQ(s, "hello");
    free(s);
}

int main(void) {
    RUN_TEST(test_replace_basic);
    RUN_TEST(test_replace_single);
    RUN_TEST(test_replace_none);
    RUN_TEST(test_replace_empty_input);
    RUN_TEST(test_replace_multichar_repl);
    RUN_TEST(test_push_str_basic);
    RUN_TEST(test_push_str_empty_append);
    TEST_SUMMARY();
}
