#ifndef DAQMANAGER_HH
#define DAQMANAGER_HH

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "TrReadout.hh"
#include "TrVMEModeChanger.hh"
#include "TrGenerator.hh"
#include "TrRunData.hh"
#include "TrSpillData.hh"
#include "TrSocketServer.hh"
#include <vector>
#include "CAENVMElib.h"

class TrDAQManager {

	protected:

		int host;
		int status; /* 0=idle, 1=triggering, 2=readout, 3=building, 4=writing */
		int connected;
		int nSpills;
		TrSocketServer socket;
		TrGenerator generator;
		TrRunData* dataBuffer;
		std::vector<TrSpillData> currentSpills;
		TrVMEModeChanger modeChanger;
		std::map<std::string, int> goCommands;
		void setStatus(int);
		TrReadout readoutController;
		std::string fileName;
	public:

		TrDAQManager(std::string);
		int setNumberOfSpills(int);
		int setTriggerMode();
		int setReadoutMode();
		int trigger(double);
		int trigger();
		int stopTrigger();
		int waitForSpill();
		int readout();
		int build();
		int write();
		void go();
		int getCommands();
		int transmit();
		TrRunData* getRunData();	

};

#endif
