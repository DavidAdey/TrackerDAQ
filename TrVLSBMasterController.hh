#ifndef TRVLSBMASTERCONTROLLER_HH
#define TRVLSBMASTERCONTROLLER_HH

#include <iostream>
#include "TrVLSBController.hh"

class TrVLSBMasterController : public TrVLSBController {

	private:
		std::map<std::string, int> triggerModes;
		int modeRegisterValue;
	public:
		TrVLSBMasterController();
		void setTriggerRate(int, int);
		void setVetoPeriod(int);
		void setTriggerMode(std::string);
		void enableTrigger();
		void disableTrigger();
		int getSpillDone();
		void initialise();
		void setTriggerWindowSettings(int, int);
		
};

#endif
