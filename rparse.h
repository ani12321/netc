#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"http-parser/http_parser.h"

typedef struct prop_s{
    char *key;
    char *value;
}prop_t;

typedef struct messages_s{
    int count;
    prop_t *messages;
}messages_t;




messages_t messages;
prop_t _message;


http_parser_settings settings;

int on_info(http_parser* p);
int on_complete(http_parser* p);
int on_data(http_parser* p, const char *at, size_t length);
int on_data_key(http_parser* p, const char *at, size_t length);
int on_data_value(http_parser* p, const char *at, size_t length);