#include "TrElectronics.hh"
#include "TrSpillData.hh"
#include "TrGlobals.hh"
#include "TrHistogram.hh"


#include <map>
#include <string>
#include <stdlib.h>
#ifndef TRGENERATOR_HH
#define TRGENERATOR_HH

class TrGenerator {

	private:
		TrElectronics electronics;
		std::map<std::string,int> settings;
		double bias;
	
	public:
		TrGenerator();
		void setup(std::string);
		void simulate();
		void setBias(double);
		TrSpillData generate();
		TrSpillData generateRandom();
		TrSpillData generateSimulated();
};

#endif
