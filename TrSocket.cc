#include "TrSocket.hh"

//TrSocket::TrSocket() {}
//TrSocket::~TrSocket() {}

void TrSocket::setup(const char* serviceName, const char* host) {

	service = serviceName;
	hostname = host;
	memset(&hostInformation, 0, sizeof(hostInformation));
	hostInformation.ai_family = AF_UNSPEC;
	hostInformation.ai_socktype = SOCK_STREAM;
	hostInformation.ai_flags = AI_PASSIVE;
	int status = getaddrinfo(hostname, service, &hostInformation, &hostInformationList);
	std::cout << status << std::endl;
}

void TrSocket::create() {

	socketIdentifier = socket(hostInformationList->ai_family, hostInformationList->ai_socktype,hostInformationList->ai_protocol); 
	if (socketIdentifier == -1)  std::cout << "socket error " ;

}

void TrSocket::end() {
	close(socketIdentifier);
}
