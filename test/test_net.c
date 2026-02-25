#include <stdio.h>
#include <stdlib.h>
#include "test/test_framework.h"
#include "net.h"

static void test_net_init_valid(void) {
    net_socket_t s = net_init();
    ASSERT_TRUE(s != NET_INVALID_SOCKET);
    net_close(s);
}

static void test_net_close_no_crash(void) {
    net_socket_t s = net_init();
    if (s == NET_INVALID_SOCKET) return; /* skip if socket creation failed */
    net_close(s);
    ASSERT_EQ(1, 1); /* reaching here means no crash */
}

static void test_net_connect_refused(void) {
    net_socket_t s = net_init();
    ASSERT_TRUE(s != NET_INVALID_SOCKET);
    if (s == NET_INVALID_SOCKET) return;
    /* port 19283 is almost certainly not listening on loopback */
    int result = net_connect(s, "127.0.0.1", 19283);
    ASSERT_EQ(result, -1);
    net_close(s);
}

int main(void) {
    RUN_TEST(test_net_init_valid);
    RUN_TEST(test_net_close_no_crash);
    RUN_TEST(test_net_connect_refused);
    TEST_SUMMARY();
}
