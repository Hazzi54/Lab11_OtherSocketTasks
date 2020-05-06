#include "func.h"

int main(int argc, char *argv[]) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0), size = sizeof(struct sockaddr_in);
    if(sock == -1)
        handle_error("socket");

    struct sockaddr_in multi_addr;
    multi_addr.sin_family = AF_INET;
    multi_addr.sin_port = htons(PORT);
    multi_addr.sin_addr.s_addr = inet_addr(IP_MULTICAST);

    char buf[BUFSIZE];
    puts("Enter broadcast message:");
    fgets(buf, BUFSIZE, stdin);
    if(sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&multi_addr, size) == -1)
        handle_error("sendto");
    shutdown(sock, SHUT_RDWR);
    return 0;
}
