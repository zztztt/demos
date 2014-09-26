#ifndef _NET_H_
#define _NET_H_
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define NET_ERROR (-1)
#define LISTENQ 20

void setnonblocking(int fd);
int TcpServerConnect(char *addr, int port);

#endif
