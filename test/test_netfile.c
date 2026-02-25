#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "test/test_framework.h"
#include "netfile.h"

static void test_netfile_write_success(void) {
    int result = netfile_write("test data");
    ASSERT_EQ(result, 1);
    unlink(RESPONSE_FILE);
}

static void test_netfile_write_content(void) {
    netfile_write("hello netc");
    FILE *f = fopen(RESPONSE_FILE, "r");
    ASSERT_NOT_NULL(f);
    if (!f) return;
    char buf[64] = {0};
    fgets(buf, sizeof(buf), f);
    fclose(f);
    ASSERT_STR_EQ(buf, "hello netc");
    unlink(RESPONSE_FILE);
}

static void test_netfile_read_success(void) {
    FILE *f = fopen(REQUEST_FILE, "w");
    ASSERT_NOT_NULL(f);
    if (!f) return;
    fputs("GET / HTTP/1.1\r\n", f);
    fclose(f);

    char *result = netfile_read();
    ASSERT_NOT_NULL(result);
    ASSERT_STR_EQ(result, "GET / HTTP/1.1\r\n");
    free(result);
    unlink(REQUEST_FILE);
}

static void test_netfile_read_missing_file(void) {
    unlink(REQUEST_FILE);
    char *result = netfile_read();
    ASSERT_NULL(result);
}

int main(void) {
    RUN_TEST(test_netfile_write_success);
    RUN_TEST(test_netfile_write_content);
    RUN_TEST(test_netfile_read_success);
    RUN_TEST(test_netfile_read_missing_file);
    TEST_SUMMARY();
}
