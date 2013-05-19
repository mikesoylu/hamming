// Hamming.cpp
// author: @mikesoylu

#include "Hamming.h"
#include <math.h>

bool Hamming::getBit(unsigned char byte, int bit) {
    unsigned char i = 1;
    i <<= bit;
    return byte&i;
}

void Hamming::encode(char *packet, char *dest, int packet_length) {
    int j = 0;
    for (int i = 0; i < getEncodedLength(packet_length); i++) {
        // is it a parity bit?
        if (!IS_POWER_OF_TWO(i+1)) {
            dest[i] = '#';
        }
    }
}

void Hamming::decode(char *packet, char *dest, int packet_length) {
}

int Hamming::getEncodedLength(int packet_length) {
    int i;
    // turn it into packet length in bits
    packet_length <<= 3;
    for (i = 1; i < packet_length; i++) {
        if (i*i > packet_length + 1) {
            break;
        }
    }
    return (int)ceil(packet_length/8.0) + i;
}

int Hamming::getDecodedLength(int packet_length) {
    int i, j = 0;
    // turn it into packet length in bits
    packet_length <<= 3;
    for (i = 1; i < packet_length + 1; i++) {
        if (!IS_POWER_OF_TWO(i)) {
            j++;
        }
    }
    return (int)ceil(j/8.0);
}
