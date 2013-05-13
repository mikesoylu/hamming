#include "DataLink.h"
#include "Hamming.h"
#include <cstdio>

int main(int argc, char **argv) {
    DataLink link;
    printf("=========TESTS==========");
    Hamming::test();
    printf("========================");
    if (argc == 2 && argv[1][1] == 's') {
        char *pack = new char[100];
        for (int i = 0; i<100; i++) {
            pack[i] = "abcdefghijklmnopqrst"[i%20];
        }
        pack[99] = 0;
        printf("sending: %s\n", pack);
        link.send(3000, pack, 100);
        delete [] pack;
    } else if (argc == 2 && argv[1][1] == 'r') {
        char *pack = new char[100];
        link.receive(3000, pack, 100);
        printf("recv'd: %s\n", pack);
        delete [] pack;
    }else {
        printf("oops\n");
    }
}
