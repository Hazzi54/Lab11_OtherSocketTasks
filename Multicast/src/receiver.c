#include "func.h"

int main(int argc, char *argv[]) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
        handle_error("socket");

    socklen_t size = sizeof(struct sockaddr_in);
    struct sockaddr_in my_addr, sender_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(sock, (struct sockaddr *)&my_addr, size) == -1)
        handle_error("bind");
    
    struct ip_mreq mr;
    mr.imr_multiaddr.s_addr = inet_addr(IP_MULTICAST);
    mr.imr_interface.s_addr = INADDR_ANY;
    if(setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mr, sizeof(mr)) == -1)
        handle_error("setsockopt");

    char buf[BUFSIZE];
    if(recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&sender_addr, &size) == -1)
        handle_error("recvfrom"); 

    shutdown(sock, SHUT_RDWR);
    puts(buf);
    return 0;
}
