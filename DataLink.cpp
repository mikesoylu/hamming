// DataLink.cpp
// author: @mikesoylu

#include "DataLink.h"
#include "Hamming.h"
#include "UChannel.h"
#include <math.h>

void DataLink::send(int port, char* packet, int packet_length) {
    for (int i = 0; i < packet_length; i += SUBPACKET_SIZE) {
        // get size of the current subpacket
        int subpacket_length = min(packet_length-i, SUBPACKET_SIZE);

        // alloc space for the encoded subpacket
        char *encoded = new char[Hamming::getEncodedLength(subpacket_length)];

        // encode data
        Hamming encoder(packet+i, encoded, subpacket_length);
        encoder.encode();

        // send it off
        u_send(port, encoded, subpacket_length);

        // clean up
        delete [] encoded;
    }
}

void DataLink::receive(int port, char* packet, int packet_length) {
    for (int i = 0; i < packet_length; i += SUBPACKET_SIZE) {
        // get size of the current subpacket
        int subpacket_length = min(packet_length-i, SUBPACKET_SIZE);
        int encoded_length = Hamming::getEncodedLength(subpacket_length);

        // alloc space for the encoded subpacket
        char *encoded = new char[encoded_length];

        // receive encoded data
        u_recv(port, encoded, encoded_length);

        // decode the encoded data
        Hamming decoder(encoded, packet+i, encoded_length);
        decoder.decode();

        // clean up
        delete [] encoded;
    }
}
