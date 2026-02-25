#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifdef _WIN32
    #include<winsock2.h>
    #pragma comment(lib,"ws2_32.lib") //Winsock Library
    typedef SOCKET net_socket_t;
    #define NET_INVALID_SOCKET INVALID_SOCKET
#else
    #include<sys/socket.h>
    #include<netinet/in.h>
    #include<arpa/inet.h>
    #include<unistd.h>
    typedef int net_socket_t;
    #define NET_INVALID_SOCKET (-1)
#endif

#define CHUNK 512
#define MAX_REQ_SIZE 8192


net_socket_t net_init();
int net_connect(net_socket_t s, char *addr, int port);
char *net_send(net_socket_t s, char *message, char *buffer);
void net_close(net_socket_t s);
