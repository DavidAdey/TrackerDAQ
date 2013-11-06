#include "TrDAQSeniorManager.hh"
#include <pthread.h>

//TrDAQSeniorManager::TrDAQSeniorManager() {}

int TrDAQSeniorManager::setup() {

	TrSocketClient trackerOne = TrSocketClient();
	//trackerOne.setup();
	const char* port = "5556";
	const char* host = "localhost";
	trackerOne.setup(port, host);
	employeeConnections.insert(std::pair<int, TrSocketClient>(1,trackerOne));
	return 0;
}

int TrDAQSeniorManager::sendGoCommand() {
	std::map<int, TrSocketClient>::iterator it;
	int readBacks = 0;
	//int size = sizeof(int);
	//int *volume = &size;
	for (it=employeeConnections.begin(); it != employeeConnections.end(); it++) {
		//pthread_t thread;
		(it->second).sendData(&goCommands["go"],sizeof(int));
		//int threadID = pthread_create( &thread, NULL, (it->second).receiveThreadedData, (void*)volume);
		readBacks |= *(it->second).receiveData(sizeof(int));
	}
	if (readBacks == 0x3) {}
	return readBacks;
}
	
int TrDAQSeniorManager::listenForData() {
	return 0;
}
	
