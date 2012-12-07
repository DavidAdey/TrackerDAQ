#ifndef TRVMEDEVICE_HH
#define TRVMEDEVICE_HH

#include <string>

#include "CAENVMElib.h"
#include "CAENVMEtypes.h"
//#include "TrReadout.hh"

class TrVMEDevice {

	protected:
		std::string vmeController;
		int dLink;
		CVAddressModifier addressModifier;
		CVDataWidth dataWidth;
		int baseAddress;
	public:
		TrVMEDevice();
		void initialise();
		void setVMEController(std::string);
		void setDLink(int);
		//virtual int setBaseAddress(int);
		int getBaseAddress() const;

};

#endif
