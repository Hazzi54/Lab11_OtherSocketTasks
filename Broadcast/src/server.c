#include "func.h"

int main(int argc, char *argv[]) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0), size = sizeof(struct sockaddr_in);
    if(sock == -1)
        handle_error("socket");

    struct sockaddr_in broad_addr;
    broad_addr.sin_family = AF_INET;
    broad_addr.sin_port = htons(PORT);
    broad_addr.sin_addr.s_addr = inet_addr(IP);

    int val = 1;
    if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val)) == -1)
        handle_error("setsockopt");

    char buf[BUFSIZE];
    puts("Enter broadcast message:");
    fgets(buf, BUFSIZE, stdin);
    if(sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&broad_addr, size) == -1)
        handle_error("sendto");
    shutdown(sock, SHUT_RDWR);
    return 0;
}
