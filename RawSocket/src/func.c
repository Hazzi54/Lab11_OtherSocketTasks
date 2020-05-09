#include "func.h"

void handle_error(char *mess) {
    perror(mess);
    exit(EXIT_FAILURE);
}

struct header_mask {
    short int src;
    short int dest;
    short int len;
    short int sum;
};

void fill_header_transp(char *buf, int size) {
    struct header_mask *m = buf;
    m->src = htons(RAW_PORT);
    m->dest = htons(PORT);
    m->len = htons(size);
    m->sum = 0;
}
