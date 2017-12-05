#ifndef __TCPOPERATE__
#define __TCPOPERATE__

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

int tcp_connect(char *temp_server_ip, int server_port);


#endif
