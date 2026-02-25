#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test/test_framework.h"
#include "rparse.h"

static void parse(const char *response) {
    struct http_parser parser;
    http_parser_init(&parser, HTTP_RESPONSE);
    http_parser_execute(&parser, &settings, response, strlen(response));
}

static void test_rparse_status_200(void) {
    parse("HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n");
    ASSERT_STR_EQ(http.status, "OK");
}

static void test_rparse_status_404(void) {
    parse("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
    ASSERT_STR_EQ(http.status, "Not Found");
}

static void test_rparse_single_header(void) {
    parse("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
    ASSERT_EQ(http.count, 1);
    ASSERT_STR_EQ(http.headers[0].key, "Content-Type");
    ASSERT_STR_EQ(http.headers[0].value, "text/plain");
}

static void test_rparse_multiple_headers(void) {
    parse("HTTP/1.1 200 OK\r\n"
          "Content-Type: text/html\r\n"
          "Content-Length: 5\r\n"
          "X-Custom: abc\r\n\r\nHello");
    ASSERT_EQ(http.count, 3);
    ASSERT_STR_EQ(http.headers[1].key, "Content-Length");
    ASSERT_STR_EQ(http.headers[2].key, "X-Custom");
    ASSERT_STR_EQ(http.headers[2].value, "abc");
}

static void test_rparse_body(void) {
    parse("HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nHello");
    ASSERT_STR_EQ(http.body, "Hello");
}

static void test_rparse_begin_resets_state(void) {
    parse("HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n");
    /* second parse must clear previous result via on_begin */
    parse("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
    ASSERT_STR_EQ(http.status, "Not Found");
    ASSERT_EQ(http.count, 1);
}

static void test_rparse_empty_body(void) {
    parse("HTTP/1.1 204 No Content\r\nContent-Length: 0\r\n\r\n");
    ASSERT_TRUE(http.body == NULL);
}

int main(void) {
    RUN_TEST(test_rparse_status_200);
    RUN_TEST(test_rparse_status_404);
    RUN_TEST(test_rparse_single_header);
    RUN_TEST(test_rparse_multiple_headers);
    RUN_TEST(test_rparse_body);
    RUN_TEST(test_rparse_begin_resets_state);
    RUN_TEST(test_rparse_empty_body);
    TEST_SUMMARY();
}
