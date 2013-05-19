// Hamming.h
// author: @mikesoylu

#ifndef HAMMING_H
#define HAMMING_H

#define IS_POWER_OF_TWO(x) (!(x & (x - 1)) && x)

class Hamming {
    private:
        int packet_length;
        char *packet;
        char *dest;

        bool getBit(char byte, int bit);
        void setBit(char &byte, int bit, bool value);

    public:
        Hamming(char *packet, char *dest, int packet_length):
            packet(packet), dest(dest), packet_length(packet_length) { };

        // encodes a packet of length getEncodedLength
        // dest should be alloc'd before calling.(use getEncodedLength)
        void encode();

        // decodes a packet of length getDecodedLength
        // dest should be alloc'd before calling.(use getDecodedLength)
        void decode();

        // returns length of a packet when encoded
        static int getEncodedLength(int packet_length);

        // returns length of a packet when decoded
        static int getDecodedLength(int packet_length);

#ifdef DEBUG
        // unit tests
        static bool test();
#endif
};

#endif
