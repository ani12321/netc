/*
    Create a TCP socket
*/
 
#include<stdio.h>
#include<stdlib.h>
#include"net.h"
#include"http-parser/http_parser.h"

typedef struct prop_s{
    char *key;
    char *value;
}prop_t;



static const char data[] =
    "POST /joyent/http-parser HTTP/1.1\r\n"
    "Host: github.com\r\n"
    "DNT: 1\r\n"
    "Accept-Encoding: gzip, deflate, sdch\r\n"
    "Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.6,en;q=0.4\r\n"
    "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_1) "
        "AppleWebKit/537.36 (KHTML, like Gecko) "
        "Chrome/39.0.2171.65 Safari/537.36\r\n"
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,"
        "image/webp,*/*;q=0.8\r\n"
    "Referer: https://github.com/joyent/http-parser\r\n"
    "Connection: keep-alive\r\n"
    "Transfer-Encoding: chunked\r\n"
    "Cache-Control: max-age=0\r\n\r\nb\r\nhello world\r\n0\r\n\r\n";
    
    
static const size_t data_len = sizeof(data) - 1;

static int on_info(http_parser* p){
    return 0;
}
static int on_data(http_parser* p, const char *at, size_t length){
    return 0;
}

static http_parser_settings settings = {
  .on_message_begin = on_info,
  .on_headers_complete = on_info,
  .on_message_complete = on_info,
  .on_header_field = on_data,
  .on_header_value = on_data,
  .on_url = on_data,
  .on_status = on_data,
  .on_body = on_data
};



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
    
    
    
    
    size_t parsed;
    struct http_parser parser;
    http_parser_init(&parser, HTTP_REQUEST);
    
    parsed = http_parser_execute(&parser, &settings, data, data_len);
    printf("%d",parsed);
    
    FILE *file = fopen("response.txt", "w");
    fprintf(file, buffer);
    fclose(file);
 
    return 0;
}