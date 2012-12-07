#ifndef TRDAQSENIORMANAGER_HH
#define TRDAQSENIORMANAGER_HH

#include "TrDAQManager.hh"
#include "TrSocketClient.hh"

#include <map>

class TrDAQSeniorManager : public TrDAQManager {

	private:
		std::map<int, TrSocketClient> employeeConnections;
		std::map<int, int> employeeStatuses;
	public:
	//	TrDAQSeniorManager();
		int setup();
		int sendGoCommand();
		int listenForData();
};

#endif
