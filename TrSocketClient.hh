#include "TrSocket.hh"
#include <map>
#include <string>

class TrSocketClient : public TrSocket {

	private:
		
	public:
		TrSocketClient();
		int connectToServer();
		int sendData(int*, int);
		int* receiveData(int);
		void* receiveThreadedData(void*);
};
