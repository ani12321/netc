/*
    Create a TCP socket
*/
 
#include<stdio.h>
#include<stdlib.h>
#include"net.h"
#include"rparse.h"
#include"netfile.h"
#include"strutils.h"

int main(int argc , char *argv[])
{
    net_socket_t s = net_init();
    if(!s) return 1;
    int c = net_connect(s, "127.0.0.1", 80);
    if(c < 0) return 1;
    
    //Send some data
    char *message = netfile_read();
    message = strcat(message, "\r\n\r\n");
    
    char *buffer;
    buffer = net_send(s, message, buffer); // response
    
    //write response to file as raw
    netfile_write(buffer);
     
    //parse response
    size_t parsed;
    struct http_parser parser;
    http_parser_init(&parser, HTTP_RESPONSE);
    parsed = http_parser_execute(&parser, &settings, buffer, strlen(buffer));
    
    // http global object
    printf("%d\n",http.count);
    printf("%s", http.status);
    for(int i=0; i<http.count; i++){
        printf("\n%s: %s", http.headers[i].key, http.headers[i].value);
    }
 
    return 0;
}