#include "TrVMEModeChanger.hh"

TrVMEModeChanger::TrVMEModeChanger() {

	modeValues["vme"] = 0x1;
	modeValues["data"] = 0x2;

}

void TrVMEModeChanger::setVMEAccess() {

	//std::cout << modeValues["vme"] << std::endl;

}

void TrVMEModeChanger::setDataAccess() {

	//std::cout << modeValues["data"] << std::endl;

}
