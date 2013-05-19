// uchannel.h
// author:
// interface of the UChannel, unreliable channel.

#ifndef UCHANNEL_H
#define UCHANNEL_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>  
#include <fstream> 
#include <string>
#include <string.h>
#include <time.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

class UChannel{
	private:
		double packet_error_rate;
		double packet_second_error_rate;
		double packet_send_delay;
	public:
		UChannel();
		void diep(char *s);
		void u_send(int port, char* packet, int packet_length);
		void u_recv(int port, char* packet, int packet_length);
};

#endif
