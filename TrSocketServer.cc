#include "TrSocketServer.hh"
#include <iostream>

//TrSocketServer::TrSocketServer() {}

int TrSocketServer::bindSocket() {
	int go = 1;
	int status = setsockopt(socketIdentifier, SOL_SOCKET, SO_REUSEADDR, &go, sizeof(int));
	status &= bind(socketIdentifier, hostInformationList->ai_addr, hostInformationList->ai_addrlen);
	return status;
}

int TrSocketServer::listenForConnection() {
	std::cout << "listending" << std::endl;
	int status = listen(socketIdentifier, 5);
	return status;
}

int TrSocketServer::acceptConnection() {
	struct sockaddr_storage clientAddress;
	socklen_t addressSize = sizeof(clientAddress);
	currentSocketID = accept(socketIdentifier, (struct sockaddr*)&clientAddress, &addressSize);
	return 0;
}

int TrSocketServer::receiveData() {
	ssize_t bytesReceived;	
	int buffer[4];
	bytesReceived = recv(currentSocketID, buffer, 4*sizeof(int), 0);
	std::cout << "received " ;
	for (int i=0; i<4; ++i) {
		std::cout << buffer[i] << std::endl;
	}
	return (int)buffer[0];//bytesReceived;
}

int TrSocketServer::sendData(int *dataPointer, int dataVolume) {
	return send(currentSocketID, dataPointer, dataVolume, 0);
}


