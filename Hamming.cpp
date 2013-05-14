// Hamming.cpp
// author: @mikesoylu

#include "Hamming.h"
#include <math.h>
#include <stdio.h>

bool Hamming::getBit(unsigned char byte, int bit) {
    unsigned char mask = 128 >> bit;
    return byte&mask;
}

void Hamming::setBit(char &byte, int bit, bool value) {
    char mask = 128 >> bit;
    if (value) {
        byte |= mask;
    } else {
        byte &= ~mask;
    }
}

bool Hamming::getParityBit(char *data, int bit, int data_bits) {
    int numOnes = 0;
    for (int j = bit-1; j < data_bits; j += 2*bit) {
        for (int k = j; k < j+bit && k < data_bits; k++) {
            // skip the first one
            if (j == bit-1 && k == j) {
                continue;
            }
            if (getBit(data[k/8], k%8)) {
                numOnes++;
            }
        }
    }
    // set parity bit to 1 if numOnes is odd
    return numOnes&1;
}

void Hamming::encode() {
    int destBit = 0;
    // write data bits to dest
    for (int i = 0; i < packet_length; i++) {
        for (int j = 0; j < 8; j++) {
            // is it not a parity bit?
            if (IS_POWER_OF_TWO(destBit+1)) {
                // then set dest bit to packet bit
                destBit++;
                j--;
            } else {
                setBit(dest[destBit/8], destBit%8, getBit(packet[i], j));
                destBit++;
            }
        }
    }

    // the full length in bits
    int fullLen = ((int)ceil(destBit/8.0)) << 3;
#ifdef DEBUG
    printf("full length of the packet: %d\n", fullLen);
#endif

    // 0-out the unused bits
    for (int i = destBit; i < fullLen; i++) {
        setBit(dest[i/8], i%8, false);
    }

    // write parity bits
    for (int i = 1; i < fullLen; i <<= 1) {
        setBit(dest[(i-1)/8], (i-1)%8, getParityBit(dest, i, fullLen));
    }
}

void Hamming::decode() {
    int errBit = -1;
    // fix error
    for (int i = 1; i < packet_length*8; i <<= 1) {
        if (getBit(packet[(i-1)/8], (i-1)%8) != getParityBit(packet, i, packet_length*8)) {
            if (-1 == errBit) {
                errBit = 0;
            }
            errBit += i;
        }
    }
    if (errBit != -1) {
        // pull to 0 index
        errBit -= 1;
        setBit(packet[errBit/8], errBit%8, !getBit(packet[errBit/8], errBit%8));
#ifdef DEBUG
        printf("fixed error at %d\n", errBit);
#endif
    }
    // write data
    int destBit = 0;
    for (int i = 0; i < packet_length; i++) {
        for (int j = 0; j < 8; j++) {
            int bit = i*8 + j;
            // is it a parity bit
            if (!IS_POWER_OF_TWO(bit + 1)) {
                setBit(dest[destBit/8], destBit%8, getBit(packet[i], j));
                destBit++;
            }
        }
    }
}

int Hamming::getEncodedLength(int packet_length) {
    if (packet_length < 31) {
        return packet_length + 1;
    }
    return packet_length + 2;
}

int Hamming::getDecodedLength(int packet_length) {
    if (packet_length < 33) {
        return packet_length - 1;
    }
    return packet_length - 2;
}

bool Hamming::test() {
    // 200 == 11001000
    printf("test: getBit(200, 7)\nreturns:%d\n", getBit(200, 0));
    printf("test: getBit(200, 3)\nreturns:%d\n", getBit(200, 4));
    printf("test: getBit(200, 6)\nreturns:%d\n", getBit(200, 1));
    {
        char c = 192;
        setBit(c, 4, true);
        printf("test: setBit(192, 3, true)\nreturns:%u\n", 0xFF&c);
    }
    for (int i = 20; i< 40; i++) {
        printf("test: getEncodedLength(%d)\nreturns:%d\n", i, getEncodedLength(i));
    }
    for (int i = 20; i< 40; i++) {
        printf("test: getDecodedLength(%d)\nreturns:%d\n", i, getDecodedLength(i));
    }
    {
        printf("test: encode(\"");
        for (int i = 0; i < 1; i++) {
            printf("%x ", 0xFF&"\x9A"[i]);
        }
        printf("\")\nreturns:");
        int len = getEncodedLength(1);
        char *encoded = new char[len];
        Hamming h("\x9A", encoded, 1);
        h.encode();
        for (int i = 0; i < len; i++) {
            printf("%x ", 0xFF&encoded[i]);
        }
        printf("\ndecoded:");
        char *decoded = new char[1];
        Hamming h2(encoded, decoded, len);
        h2.decode();
        for (int i = 0; i < 1; i++) {
            printf("%x ", 0xFF&decoded[i]);
        }
        printf("\n");
        delete [] encoded;
        delete [] decoded;
    }
    {
        printf("test: encode(\"");
        for (int i = 0; i < 2; i++) {
            printf("%x ", 0xFF&"ab"[i]);
        }
        printf("\")\nreturns:");
        int len = getEncodedLength(2);
        char *encoded = new char[len];
        Hamming h("ab", encoded, 2);
        h.encode();
        for (int i = 0; i < len; i++) {
            printf("%x ", 0xFF&encoded[i]);
        }
        printf("\ndecoded:");
        char *decoded = new char[2];
        Hamming h2(encoded, decoded, len);
        h2.decode();
        for (int i = 0; i < 2; i++) {
            printf("%x ", 0xFF&decoded[i]);
        }
        printf("\n");
        delete [] encoded;
        delete [] decoded;
    }
    {
        printf("test: encode(\"");
        for (int i = 0; i < 4; i++) {
            printf("%x ", 0xFF&"qwer"[i]);
        }
        printf("\")\nreturns:");
        int len = getEncodedLength(4);
        char *encoded = new char[len];
        Hamming h("qwer", encoded, 4);
        h.encode();
        for (int i = 0; i < len; i++) {
            printf("%x ", 0xFF&encoded[i]);
        }
        printf("\ndecoded:");
        char *decoded = new char[4];
        Hamming h2(encoded, decoded, len);
        h2.decode();
        for (int i = 0; i < 4; i++) {
            printf("%x ", 0xFF&decoded[i]);
        }
        printf("\n");
        delete [] encoded;
        delete [] decoded;
    }
}
