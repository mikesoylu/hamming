// Hamming.cpp
// author: @mikesoylu

#include "Hamming.h"
#include <math.h>
#include <stdio.h>

bool Hamming::getBit(char byte, int bit) {
    char mask = 1 << bit;
    return byte&mask;
}

void Hamming::setBit(char &byte, int bit, bool value) {
    char mask = 1 << bit;
    if (value) {
        byte |= mask;
    } else {
        byte &= ~mask;
    }
}

void Hamming::encode() {
    int destBit = 0;
    // write data bits to dest
    for (int i = 0; i < packet_length; i++) {
        for (int j = 0; j < 8; j++) {
            // is it not a parity bit?
            if (!IS_POWER_OF_TWO(i*8 + j + 1)) {
                // then set dest bit to packet bit
                setBit(dest[destBit/8], destBit%8, getBit(packet[i], j));
                destBit++;
            }
        }
    }
    // write parity bits
    for (int i = 1; i < destBit; i <<= 1) {
        int numOnes = 0;
        for (int j = i-1+i; j < destBit; j += i) {
            if (getBit(dest[j/8], j%8)) {
                numOnes++;
            }
        }
        // set parity bit to 1 if numOnes is odd
        setBit(dest[i-1], (i-1)%8, numOnes&1);
    }
}

void Hamming::decode() {
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
    return (int)ceil((packet_length + i)/8.0);
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
    return j/8;
}

#ifdef DEBUG
bool Hamming::test() {
    printf("test: getEncodedLength(1) == 2\nreturns:%d\n", getEncodedLength(1));
    printf("test: getEncodedLength(2) == 3\nreturns:%d\n", getEncodedLength(2));
    printf("test: getDecodedLength(3) == 2\nreturns:%d\n", getDecodedLength(3));

    {
        printf("test: encode(\"");
        for (int i = 0; i < 2; i++) {
            printf("%u ", "ab"[i]);
        }
        printf("\")\nreturns:");
        int len = getEncodedLength(2);
        char *encoded = new char[len];
        Hamming h("ab", encoded, 2);
        h.encode();
        for (int i = 0; i < len; i++) {
            printf("%u ", encoded[i]);
        }
        printf("\n");
        delete [] encoded;
    }
    {
        printf("test: encode(\"");
        for (int i = 0; i < 4; i++) {
            printf("%u ", "qwer"[i]);
        }
        printf("\")\nreturns:");
        int len = getEncodedLength(4);
        char *encoded = new char[len];
        Hamming h("ab", encoded, 4);
        h.encode();
        for (int i = 0; i < len; i++) {
            printf("%u ", encoded[i]);
        }
        printf("\n");
        delete [] encoded;
    }
}
#endif
