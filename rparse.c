#include "rparse.h"



http_parser_settings settings = {
    .on_message_begin = on_info,
    .on_headers_complete = on_info,
    .on_message_complete = on_complete,
    .on_header_field = on_data_key,
    .on_header_value = on_data_value,
    .on_url = on_data,
    .on_status = on_data,
    .on_body = on_data
};

int on_info(http_parser* p){
    
    return 0;
}

int on_complete(http_parser* p){
    
    for(int i=0; i<messages.count; i++){
        
        printf("%s\n", messages.messages[i].value);
    }
    
    return 0;
}

int on_data(http_parser* p, const char *at, size_t length){
    
    char *rec = malloc(sizeof(char) * (length + 1) );
    strncpy(rec, at, length);
    rec[length] = '\0';
    
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
    
    messages.messages = (prop_t *)realloc(messages.messages, messages.count * sizeof(prop_t));
    messages.messages[0] = _message;
    messages.count += 1;
    
    return 0;
}
