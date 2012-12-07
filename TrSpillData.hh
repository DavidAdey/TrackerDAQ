#include <vector>
#include "TrGlobals.hh"
#include "TrHistogram.hh"
#include "TrHeaders.hh"

#ifndef TRSPILLDATA_HH
#define TRSPILLDATA_HH

class TrSpillData {

	private:

		TrSpillHeader header;
		TrHistogram data[BOARDS][BANKS][CHANNELS];

	public:
		TrSpillData();
		void addHistogram(int, int, int, TrHistogram);
		TrHistogram* getHistogram(int, int, int);

};

#endif
