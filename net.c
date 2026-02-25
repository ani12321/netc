#include "net.h"

net_socket_t net_init()
{
    net_socket_t s;

#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return NET_INVALID_SOCKET;
    }
#endif

    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == NET_INVALID_SOCKET)
    {
#ifdef _WIN32
        printf("Could not create socket : %d" , WSAGetLastError());
#else
        printf("Could not create socket\n");
#endif
        return NET_INVALID_SOCKET;
    }

    return s;
}

int net_connect(net_socket_t s, char *addr, int port)
{
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(addr);
    server.sin_family = AF_INET;
    server.sin_port = htons( port );

    return connect(s , (struct sockaddr *)&server , sizeof(server));
}

char *net_send(net_socket_t s, char *message, char *buffer)
{
    char server_reply[MAX_REQ_SIZE] = "", chunk[CHUNK];
    int irecv_size, total = 0;

    if( send(s , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return NULL;
    }
    do {
        memset(chunk ,0 , CHUNK); //clear buffer
        irecv_size = recv(s, chunk, CHUNK, 0); //get socket response

        if(irecv_size == 0) net_close(s);
        else if(irecv_size < 0){
            puts("Error on response");
            return 0;
        }
        else{
            chunk[CHUNK-1] = '\0';
            strcat(server_reply, chunk);

            total += irecv_size;
        }
    }
    while(irecv_size > 0);
    buffer = malloc(total);
    strcpy(buffer, server_reply);

    return buffer;
}

void net_close(net_socket_t s)
{
#ifdef _WIN32
    closesocket(s);
    WSACleanup();
#else
    close(s);
#endif
}
