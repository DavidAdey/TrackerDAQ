#include <map>
#include <string>
#include <iostream>
#include "TrVLSBMasterController.hh"
#include "TrVLSBController.hh"
#ifndef TRVMEMODECHANGER_HH
#define TRVMEMODECHANGER_HH

class TrVMEModeChanger {

	private:
		std::map<std::string, int> modeValues;

	public:
		TrVMEModeChanger();
		void setVMEAccess();
		void setDataAccess();

};

#endif
