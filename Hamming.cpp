// Hamming.cpp
// author: @mikesoylu

#include "Hamming.h"

void Hamming::encode(char *packet, char *dest, int packet_length) {
    for (int i = 0; i < packet_length; i++) {

    }
}

void Hamming::decode(char *packet, char *dest, int packet_length) {
}

int Hamming::getEncodedLength(int packet_length) {
    int i;
    for (i = 1; i < packet_length; i++) {
        if (i*i > packet_length+1) {
            break;
        }
    }
    return packet_length+i;
}

int Hamming::getDecodedLength(int packet_length) {
    int i, j = 0;
    for (i = 1; i < packet_length+1; i++) {
        if (!IS_POWER_OF_TWO(i)) {
            j++;
        }
    }
    return j;
}
