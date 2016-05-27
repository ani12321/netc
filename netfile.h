#include<stdio.h>
#include<stdlib.h>

#define RESPONSE_FILE "response.net"
#define REQUEST_FILE "request.net"

int netfile_write(char *data);
char *netfile_read();