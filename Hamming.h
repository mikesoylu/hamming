// Hamming.h
// author: @mikesoylu

#ifndef HAMMING_H
#define HAMMING_H

#define IS_POWER_OF_TWO(x) (!((x) & ((x) - 1)) && (x))

class Hamming {
    private:
        int packet_length;
        char *packet;
        char *dest;

        static bool getBit(unsigned char byte, int bit);
        static void setBit(char &byte, int bit, bool value);

        // gets the value of a parity bit at position bit which IS_POWER_OF_TWO
        bool getParityBit(char *data, int bit, int data_bits);

    public:
        Hamming(char *packet, char *dest, int packet_length):
            packet(packet), dest(dest), packet_length(packet_length) { };

        // encodes packet of length getEncodedLength to dest
        // dest should be alloc'd before calling.(use getEncodedLength)
        void encode();

        // decodes a packet of length getDecodedLength to dest
        // dest should be alloc'd before calling.(use getDecodedLength)
        void decode();

        // returns length of a packet when encoded
        static int getEncodedLength(int packet_length);

        // returns length of a packet when decoded
        static int getDecodedLength(int packet_length);

        // unit tests
        static bool test();
};

#endif
