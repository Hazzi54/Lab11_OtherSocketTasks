#ifndef _RAWSOCK_FUNC
#define _RAWSOCK_FUNC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 

#define IP "127.0.0.1"
#define PORT 7777
#define RAW_PORT 7000
#define BUFSIZE 100
#define MAXSIZE 0xFF

void handle_error(char *);
void fill_header_transp(char *, int);

#endif
