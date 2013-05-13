// uchannel.cpp
// author:
// The implementation of UChannel, unreliable channel.

#include "UChannel.h"

UChannel::UChannel(){
	//packet_error_rate = 0.8;
	packet_error_rate = 0.0;
	packet_second_error_rate = 0.0;
	//packet_send_delay = 0.05;
	packet_send_delay = 0.1;
}

void UChannel::diep(char * s)
{
    perror(s);
    exit(1);
};

void UChannel::u_send(int port, char* packet, int packet_length) {
        
	if (packet_length < 1 || packet_length > 50) return;

	usleep(packet_send_delay*1000000);

        double random;
	struct sockaddr_in si_other;
	int s, i, slen=sizeof(si_other);

	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1) diep("socket");

	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(port);

	if (inet_aton("127.0.0.1", &si_other.sin_addr)==0) {

	   fprintf(stderr, "inet_aton() failed\n");
   	   exit(1);
	}

        random = ((double)rand()/(double)RAND_MAX);

        // Packet has error
        if (random < packet_error_rate) {

            // add error to the buffer
	    int number = rand() % packet_length; //0..packet_length-1
	    int randomBit = rand() % 8;	// 0..7
 
            packet[number] ^= 1 << randomBit;

	    // add second error to the buffer
	    random = ((double)rand()/(double)RAND_MAX);
	    if (random < packet_second_error_rate){
		number = rand() % packet_length;
		randomBit = rand() % 8;
		packet[number] ^= 1 << randomBit;

	    }
        }

	printf("Sending packet: %s\n", packet);

        // send the response to the client at "address" and "port" 
	if (sendto(s, packet, packet_length, 0, (struct sockaddr*)&si_other, slen)==-1)  diep("sendto()");
        close(s);

}

void UChannel::u_recv(int port, char* packet, int packet_length) {

        if (packet_length < 1 || packet_length > 50) { std::cout << "packet length problem" << std::endl; return; }

	struct sockaddr_in si_me, si_other;
        int s, i, slen=sizeof(si_other);

        if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1) diep("socket");
     
        memset((char *) &si_me, 0, sizeof(si_me));
        si_me.sin_family = AF_INET;
        si_me.sin_port = htons(port);
        si_me.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(s, (struct sockaddr*)&si_me, sizeof(si_me))==-1) diep("bind");

	if (recvfrom(s, packet, packet_length, 0, (struct sockaddr *)&si_other, (socklen_t*)&slen)==-1) diep("recvfrom()");
        
	printf("Received packet: %s\n", packet);

        close(s);

}    
