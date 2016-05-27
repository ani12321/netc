#include "rparse.h"



http_parser_settings settings = {
    .on_message_begin = on_begin,
    .on_headers_complete = on_headers_complete,
    .on_message_complete = on_complete,
    .on_header_field = on_data_key,
    .on_header_value = on_data_value,
    .on_url = on_url,
    .on_status = on_status,
    .on_body = on_data
};

int on_begin(http_parser* p){
    printf("Begin\n");
    memset(&http, 0, sizeof(http_t));
    return 0;
}

int on_headers_complete(http_parser* p){
    return 0;
}

int on_complete(http_parser* p){    
    return 0;
}

int on_url(http_parser* p, const char *at, size_t length){
    
    http.url = malloc(sizeof(char) * (length + 1) );
    strncpy(http.url, at, length);
    http.url[length] = '\0';
    
    return 0;
}

int on_status(http_parser* p, const char *at, size_t length){
    
    char *rec = malloc(sizeof(char) * (length + 1) );
    strncpy(rec, at, length);
    rec[length] = '\0';
    http.status = rec;
    return 0;
}

int on_data(http_parser* p, const char *at, size_t length){
    
    http.body = malloc(sizeof(char) * (length + 1) );
    strncpy(http.body, at, length);
    http.body[length] = '\0';
    return 0;
}

int on_data_key(http_parser* p, const char *at, size_t length){
    char *rec = malloc(sizeof(char) * (length + 1) );
    strncpy(rec, at, length);
    rec[length] = '\0';
    
    _message.key = rec;
       
    return 0;
}

int on_data_value(http_parser* p, const char *at, size_t length){

    char *rec = malloc(sizeof(char) * (length + 1) );
    strncpy(rec, at, length);
    rec[length] = '\0';
    
    _message.value = rec;
    
    http.headers[http.count] = _message;
    http.count += 1;
    
    return 0;
}
