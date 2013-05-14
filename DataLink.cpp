// DataLink.cpp
// author: @mikesoylu

#include "DataLink.h"
#include "Hamming.h"
#include "UChannel.h"
#include <algorithm>

using std::min;

void DataLink::send(int port, char* packet, int packet_length) {
    UChannel channel;
    for (int i = 0; i < packet_length; ) {
        // get size of the current subpacket
        int subpacket_length = min(packet_length-i, SUBPACKET_SIZE);

#ifdef DEBUG
        printf("alloc'ing %d bytes for encoded data\n", Hamming::getEncodedLength(subpacket_length));
#endif
        // alloc space for the encoded subpacket
        char *encoded = new char[Hamming::getEncodedLength(subpacket_length)];

        // encode data
        Hamming encoder(packet+i, encoded, subpacket_length);
        encoder.encode();

        // send it off
        channel.u_send(port, encoded, Hamming::getEncodedLength(subpacket_length));

        // clean up
        delete [] encoded;

        i += subpacket_length;
    }
}

void DataLink::receive(int port, char* packet, int packet_length) {
    UChannel channel;
    for (int i = 0; i < packet_length; ) {
        // get size of the current subpacket
        int subpacket_length = min(packet_length-i, SUBPACKET_SIZE);
        int encoded_length = Hamming::getEncodedLength(subpacket_length);

#ifdef DEBUG
        printf("alloc'ing %d bytes for encoded data\n", encoded_length);
#endif

        // alloc space for the encoded subpacket
        char *encoded = new char[encoded_length];
        char *decoded = new char[subpacket_length];

        // receive encoded data
        channel.u_recv(port, encoded, encoded_length);

        // decode the encoded data
        Hamming decoder(encoded, decoded, encoded_length);
        decoder.decode();

        // copy decoded data to packet
        memcpy(packet+i, decoded, subpacket_length);

        // clean up
        delete [] encoded;
        delete [] decoded;

        i+= subpacket_length;
    }
}
