#include "func.h"

int main(int argc, char *argv[]) {
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(sock == -1)
        handle_error("socket");

    struct sockaddr_in receiver;
    receiver.sin_family = AF_INET;
    receiver.sin_port = htons(PORT);
    receiver.sin_addr.s_addr = inet_addr(IP);
    
    char buff[MAXSIZE], *prebuf = malloc(MAXSIZE - 8);
    fgets(prebuf, MAXSIZE - 8, stdin);
    char *ptr = buff;
    ptr += 8;
    strcpy(ptr, prebuf);
    free(prebuf);

    fill_header_transp(buff, strlen(buff) + 1);
    socklen_t sizeAddr = sizeof(struct sockaddr_in);
    if(sendto(sock, buff, sizeof(buff), 0, (struct sockaddr *)&receiver, sizeAddr) == -1)
        handle_error("sendto");

    char buf2[MAXSIZE];
    short int *pShort;
    int i = 1;
    while(1) {
        if(recvfrom(sock, buf2, MAXSIZE, 0, (struct sockaddr *)&receiver, &sizeAddr) == -1)
            handle_error("recvfrom");
        i++;

        pShort = buf2;
        pShort += 11;
        if(ntohs(*pShort) == RAW_PORT)
            break;
    }
    
    char *ptr_string = buf2, msg[strlen(buf2 - 8)];
    ptr_string += 28;
    strcpy(msg, ptr_string);
    puts(msg);
    shutdown(sock, SHUT_RDWR);
    return 0;
}
