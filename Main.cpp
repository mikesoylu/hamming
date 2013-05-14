#include "DataLink.h"
#include "Hamming.h"
#include <cstdio>

int main(int argc, char **argv) {
    DataLink link;
    if (argc == 2 && argv[1][1] == 's') {
        char *pack = new char[1031];
        for (int i = 0; i<1031; i++) {
            pack[i] = "abcdefghijklmnopqrst"[i%20];
        }
        for (int i = 0; i<1031; i++) {
            putchar(pack[i]);
        }
        putchar('\n');
        link.send(3000, pack, 1031);
        delete [] pack;
    } else if (argc == 2 && argv[1][1] == 'r') {
        char *pack = new char[1031];
        link.receive(3000, pack, 1031);
        for (int i = 0; i<1031; i++) {
            putchar(pack[i]);
        }
        putchar('\n');
        delete [] pack;
    }else {
        printf("oops\n");
    }
}
