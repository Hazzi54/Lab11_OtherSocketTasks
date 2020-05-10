#include "func.h"

int main(int argc, char *argv[]) {
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(sock == -1)
        handle_error("socket");

    struct sockaddr_in receiver;
    receiver.sin_family = AF_INET;
    receiver.sin_port = htons(PORT);
    receiver.sin_addr.s_addr = inet_addr(IP);

    int val = 1;
    if(setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &val, sizeof(val)) == -1)
        handle_error("setsockopt");
    
    char buff[MAXSIZE];
    memset(buff, 0, MAXSIZE);
    char *ptr = buff;
    fill_header_ip(ptr, MAXSIZE);
    ptr += 20;
    fill_header_transp(ptr, MAXSIZE - 20);
    ptr += 8;
    fgets(ptr, MAXSIZE - 28, stdin);

    socklen_t sizeAddr = sizeof(struct sockaddr_in);
    if(sendto(sock, buff, sizeof(buff), 0, (struct sockaddr *)&receiver, sizeAddr) == -1)
        handle_error("sendto");

    char buf2[MAXSIZE];
    short int *pShort;
    while(1) {
        if(recvfrom(sock, buf2, MAXSIZE, 0, (struct sockaddr *)&receiver, &sizeAddr) == -1)
            handle_error("recvfrom");
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
