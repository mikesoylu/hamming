// DataLink.cpp
// author: @mikesoylu

#include "DataLink.h"
#include "Hamming.h"
#include "UChannel.h"

void DataLink::send(int port, char* packet, int packet_length) {
    u_send(port, packet, packet_length);
}

void DataLink::receive(int port, char* packet, int packet_length) {
    u_recv(port, packet, packet_length);
}
