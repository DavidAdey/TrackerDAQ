#include "TrSocket.hh"

class TrSocketServer : public TrSocket {

	private:
		int currentSocketID;
		char incomingDataBuffer[1000];
	public:
		//TrSocketServer();	
		int sendData(int*, int);
		int receiveData();
		int bindSocket();
		int listenForConnection();
		int acceptConnection();
};
