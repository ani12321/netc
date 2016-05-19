/*
    Create a TCP socket
*/
 
#include<stdio.h>
#include<stdlib.h>
#include"net.h"
#include"rparse.h"


int main(int argc , char *argv[])
{
    SOCKET s = net_init();
    if(!s) return 1;
    int c = net_connect(s, "127.0.0.1", 80);
    if(c < 0) return 1;
    
    //Send some data
    char *message = "GET / HTTP/1.1\r\n"
        "Host: 127.0.0.1\r\n"
        "Connection: close\r\n"
        "Cache-Control: max-age=0\r\n"
        "Upgrade-Insecure-Requests: 1\r\n"
        "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.19 Safari/537.36\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
        "Accept-Encoding: gzip, deflate, sdch\r\n\r\n";

    
    char *buffer;
    buffer = net_send(s, message, buffer);
    
    FILE *file = fopen("response.txt", "w");
    fprintf(file, buffer);
    fclose(file);
     
    
    size_t parsed;
    struct http_parser parser;
    http_parser_init(&parser, HTTP_REQUEST);
    
    parsed = http_parser_execute(&parser, &settings, message, strlen(message));
    //printf("%d",parsed);
    
 
    return 0;
}