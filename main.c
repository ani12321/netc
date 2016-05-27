/*
    Create a TCP socket
*/
 
#include<stdio.h>
#include<stdlib.h>
#include"net.h"
#include"rparse.h"
#include"netfile.h"

/* return a new string with every instance of ch replaced by repl */
char *replace(const char *s, char ch, const char *repl) {
    int count = 0;
    const char *t;
    for(t=s; *t; t++)
        count += (*t == ch);

    size_t rlen = strlen(repl);
    char *res = malloc(strlen(s) + (rlen-1)*count + 1);
    char *ptr = res;
    for(t=s; *t; t++) {
        if(*t == ch) {
            memcpy(ptr, repl, rlen);
            ptr += rlen;
        } else {
            *ptr++ = *t;
        }
    }
    *ptr = 0;
    return res;
}

char *push_str(char *s, char *ch)
{
    int len = strlen(s);
    s = (char*)realloc(s, len * sizeof(char) + strlen(ch));
    for(int i=0; i<strlen(ch); i++)
        s[len + i] = ch[i];
        
    return s;
}


int main(int argc , char *argv[])
{
    SOCKET s = net_init();
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