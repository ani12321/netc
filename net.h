#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define CHUNK 512


SOCKET net_init();
int net_connect(SOCKET s, char *addr, int port);
char *net_send(SOCKET s, char *message, char *buffer);
void net_close(SOCKET s);