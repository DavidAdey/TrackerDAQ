#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
#include "TrGlobals.hh"
#include "TRandom.h"
#ifndef TRELECTRONICS_HH
#define TRELECTRONICS_HH

#define PEAKS 5

class TrElectronics {

	private:
		double pedestalList[BOARDS][BANKS][CHANNELS];
		double gainList[BOARDS][BANKS][CHANNELS];
		double qeList[BOARDS][BANKS][CHANNELS];
		double noiseRatios[BOARDS][BANKS][CHANNELS][PEAKS];
		std::map<std::string, double> parameters;
		TRandom* r;
		void generateNoiseRatios();
		void generateGains();
		void generatePedestals();
		double chargeFromPE(int, int, int, int);

	public:

		TrElectronics();
		int trigger(int, int, int, int, double);
		void setup();
};

#endif
