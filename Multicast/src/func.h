#ifndef _MULTICAST_FUNC
#define _MULTICAST_FUNC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 

#define IP_MULTICAST "224.0.0.1"
#define PORT 7777
#define BUFSIZE 100
#define BACKLOG 5
#define NUM_THREADS 16

void handle_error(char *);

#endif
