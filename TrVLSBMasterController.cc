#include "TrVLSBMasterController.hh"

TrVLSBMasterController::TrVLSBMasterController() {}

void TrVLSBMasterController::initialise() {

	TrVLSBController::initialise();
	triggerModes.insert( std::pair<std::string, int> ("internal",0) );
	triggerModes.insert( std::pair<std::string, int> ("external",1) );
	triggerModes.insert( std::pair<std::string, int> ("internalSuppressed",2) );
	triggerModes.insert( std::pair<std::string, int> ("externalSuppressed",3) );

}

void TrVLSBMasterController::setTriggerMode(std::string mode) {

	try {
		switch(triggerModes[mode]) {

			case 0: // internal triggers
				modeRegisterValue = triggerSetting["internal"];
				modeRegisterValue = triggerSetting["noZeroSuppression"];
				break;
			case 1: // external
				modeRegisterValue = triggerSetting["external"];
				modeRegisterValue |= triggerSetting["noZeroSuppression"];	
				modeRegisterValue |= triggerSetting["noVeto"];
				modeRegisterValue |= triggerSetting["continuousSpill"];
				break;
			case 2:
				modeRegisterValue = triggerSetting["internal"];
				break;
			case 3:	
				modeRegisterValue = triggerSetting["external"];	
				modeRegisterValue |= triggerSetting["noVeto"];
				modeRegisterValue |= triggerSetting["continuousSpill"];
				break;
			default:
				break; // How did this happen?
		}
	}
	catch(...) {
		std::cout << "Trigger mode exception," << std::endl;
		std::cout << "Fixing by defaulting to internal mode setting" << std::endl;
		modeRegisterValue = triggerSetting["internal"];
	}
	
}

void TrVLSBMasterController::enableTrigger() {
	modeRegisterValue |= triggerSetting["spillEnable"];
	CAENVME_WriteCycle(0, addresses["control"], &modeRegisterValue, addressModifier, dataWidth);

}

void TrVLSBMasterController::disableTrigger() {	
	CAENVME_WriteCycle(0, addresses["control"], &triggerSetting["spillDisable"], addressModifier, dataWidth);
}

void TrVLSBMasterController::setTriggerWindowSettings(int windowOpen, int windowClose) {
	//int windowRegisterValue = (windowOpen & 0x1F) + ((windowClose & 0x1F) << 8);
}

void TrVLSBMasterController::setTriggerRate(int period, int triggers) {
	//int triggerRateRegisterValue = (period & 0xFFFF) + ((triggers & 0xFFFF) << 16);
}

int TrVLSBMasterController::getSpillDone() {
	int done(0);
	while (!done) {
		CAENVME_ReadCycle(0, addresses[""], &done, addressModifier, dataWidth);
	}
	return done;
}
