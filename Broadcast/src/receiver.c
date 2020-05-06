#include "func.h"

int main(int argc, char *argv[]) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
        handle_error("socket");

    socklen_t size = sizeof(struct sockaddr_in);
    struct sockaddr_in broad_addr;
    broad_addr.sin_family = AF_INET;
    broad_addr.sin_port = htons(PORT);
    broad_addr.sin_addr.s_addr = INADDR_BROADCAST;
    
    if(bind(sock, (struct sockaddr *)&broad_addr, size) == -1)
        handle_error("bind");  

    char buf[BUFSIZE];
    if(recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&broad_addr, &size) == -1)
        handle_error("recvfrom"); 

    shutdown(sock, SHUT_RDWR);
    puts(buf);
    return 0;
}
