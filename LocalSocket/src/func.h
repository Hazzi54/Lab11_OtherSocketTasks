#ifndef _MULTICAST_FUNC
#define _MULTICAST_FUNC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/socket.h>

#define SNAME "/tmp/udpser"
#define CNAME "/tmp/udpcli"
#define BUFSIZE 100

void handle_error(char *);

#endif
