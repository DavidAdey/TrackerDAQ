#ifndef TRSOCKET_HH
#define TRSOCKET_HH

#include <iostream>
#include <cstring>   
#include <string>   
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>

class TrSocket {

	protected:	
		struct addrinfo hostInformation;
		struct addrinfo *hostInformationList;
		const char *service;
		const char *hostname;
		int socketIdentifier;
	public:
		//TrSocket();
		//~TrSocket();
		void setup(const char*, const char*);
		void create();
		void end();

};

#endif
