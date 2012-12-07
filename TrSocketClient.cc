#include "TrSocketClient.hh"
#include <iostream>
TrSocketClient::TrSocketClient() {}

int TrSocketClient::connectToServer() {
	int status = connect(socketIdentifier, hostInformationList->ai_addr, hostInformationList->ai_addrlen);
	return status;
}

int TrSocketClient::sendData(int *dataPointer, int dataVolume) {
	std::cout << "Sending " << *dataPointer << std::endl;
	int status = send(socketIdentifier, dataPointer, dataVolume, 0);
	return status;
}

int* TrSocketClient::receiveData(int dataWords) {
	ssize_t bytesReceived;	
	int dataBuffer[dataWords];
	bytesReceived = recv(socketIdentifier, dataBuffer, dataWords*sizeof(int), 0);
	int* dataPointer = (int*)calloc(dataWords, sizeof(int));
	for (int word=0; word<dataWords; ++word) {
		*dataPointer = dataBuffer[word];
		++dataPointer;
	}
	dataPointer -= dataWords;
	return dataPointer;
}

/*
void* TrSocketClient::receiveThreadedData(void *words) {
	int dataWords = *(int*)words;
	ssize_t bytesReceived;	
	int dataBuffer[dataWords];
	bytesReceived = recv(socketIdentifier, dataBuffer, dataWords*sizeof(int), 0);
	int* dataPointer = (int*)calloc(dataWords, sizeof(int));
	for (int word=0; word<dataWords; ++word) {
		*dataPointer = dataBuffer[word];
		++dataPointer;
	}
	dataPointer -= dataWords;
//	return dataPointer;
}*/
