#include <map>
#include <string>
#include <vector>
#include "CAENVMElib.h"
#include "CAENVMEtypes.h"
#include "TrSpillData.hh"
#include "TrGenerator.hh"
#include "TrGlobals.hh"
#include "TrVLSBController.hh"
#include "TrVLSBMasterController.hh"

#ifndef TRREADOUT_HH
#define TRREADOUT_HH

class TrVLSBController;

class TrReadout {

	private:
		/* Variables */
		TrSpillData currentSpill;
		std::map<std::string,int> vmeCommands;
		int bankLengths[BOARDS][BANKS];
		int vmeStatus;
		TrVLSBMasterController master;
		std::vector<TrVLSBController> vlsbs;
		/* Functions */
		/*unsigned long setupAddressArray();	
		unsigned long readVLSBBanks();
		void fillCurrentSpill(unsigned long);
		void resetCurrentSpill();
		void getBankLengths();
*/
	public:
		TrReadout();
		void setDataMode();
		void setReadoutMode();
		void enableTrigger();
		int pollSpillDone();
		void disableTrigger();
		TrSpillData* readout();
		TrSpillData* readout(TrGenerator);
		TrSpillData compress(int*, int, int);

};

#endif
