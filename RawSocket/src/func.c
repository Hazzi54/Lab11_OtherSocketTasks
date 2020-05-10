#include "func.h"

void handle_error(char *mess) {
    perror(mess);
    exit(EXIT_FAILURE);
}

struct header_mask_udp {
    short int src;
    short int dest;
    short int len;
    short int sum;
};

struct header_mask_ip {
    char verIHL;
    char DS;
    short int len;
    short int Id;
    short int flOffset;
    char TTL;
    char TransProto;
    short int sum;
    int src;
    int dest;
};

void fill_header_transp(char *buf, int size) {
    struct header_mask_udp *m = (struct header_mask_udp *)buf;
    m->src = htons(RAW_PORT);
    m->dest = htons(PORT);
    m->len = htons(size);
    m->sum = 0;
}

void fill_header_ip(char *buf, int size) {
    struct header_mask_ip *m = (struct header_mask_ip *)buf;
    m->verIHL = 0x45;
    m->DS = 0;
    m->len = htons(size);
    m->Id = 0;
    m->flOffset = 0;
    m->TTL = 255;
    m->TransProto = IPPROTO_UDP;
    m->sum = 0;
    m->src = inet_addr(IP);
    m->dest = inet_addr(IP);
}







