/*
    Create a TCP socket
*/
 
#include<stdio.h>
#include<stdlib.h>
#include"net.h"

typedef struct prop_s{
    char *key;
    char *value;
}prop_t;





int main(int argc , char *argv[])
{
    SOCKET s = net_init();
    if(!s) return 1;
    int c = net_connect(s, "192.168.111.222", 80);
    if(c < 0) return 1;
    
    //Send some data
    char *message = "GET /login.aspx HTTP/1.1\r\n"
        "Host: 192.168.111.222\r\n"
        "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; rv:45.0) Gecko/20100101 Firefox/45.0\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
        "Connection: close\r\n"
        "Accept-Language: en-GB,en;q=0.5\r\n"
        "Accept-Encoding: gzip, deflate\r\n\r\n";
    
    char *buffer;
    buffer = net_send(s, message, buffer);
    
    
    FILE *file = fopen("response.txt", "w");
    fprintf(file, buffer);
    fclose(file);
 
    return 0;
}