// Hamming.h
// author: @mikesoylu

#ifndef HAMMING_H
#define HAMMING_H

#define IS_POWER_OF_TWO(x) (!(x & (x - 1)) && x)

class Hamming {
    private:
    public:
        // encodes a packet of length getEncodedLength
        void encode(char *packet, char *dest, int packet_length);
        // decodes a packet of length getDecodedLength
        void decode(char *packet, char *dest, int packet_length);
        // returns lenght of a packet when encoded
        int getEncodedLength(int packet_length);
        // returns lenght of a packet when decoded
        int getDecodedLength(int packet_length);
};

#endif
