#include "net.h"

SOCKET net_init()
{
    WSADATA wsa;
    SOCKET s;
    
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
    }
     
     
    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
 
    
    return s;
}

int net_connect(SOCKET s, char *addr, int port)
{
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(addr);
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
    
    
    return connect(s , (struct sockaddr *)&server , sizeof(server));
}

char *net_send(SOCKET s, char *message, char *buffer)
{
    char server_reply[20000], chunk[CHUNK];
    int irecv_size, total = 0, recv_size;
    
    if( send(s , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return NULL;
    }
    
    do {
        memset(chunk ,0 , CHUNK); //clear buffer
        irecv_size = recv(s, chunk, CHUNK, 0); //get socket response
        strcat(server_reply, chunk); 
        total += irecv_size;
        
        if(irecv_size == 0) closesocket(s);
        else if(irecv_size < 0){
            puts("Error on response");
            return NULL;
        }
    }
    while(irecv_size > 0);
    
    server_reply[total] = '\0';
    
    buffer = malloc(strlen(server_reply));
    strcpy(buffer, server_reply);
    
    return buffer;
}

void net_close(SOCKET s)
{
    closesocket(s);
}
