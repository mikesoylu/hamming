// 	DataLink.h
// 	author: @mikesoylu

#ifndef DATA_LINK_H
#define DATA_LINK_H

#define SUBPACKET_SIZE 30

class DataLink {
	private:
	public:
		void send(int port, char* packet, int packet_length);
        void receive(int port, char* packet, int packet_length);
};

#endif
