#include <vector>
#include "TrHistogram.hh"
#include "TrSpillData.hh"

#ifndef TRRUNDATA_HH
#define TRRUNDATA_HH

class TrRunData {

	private:

		TrHistogram data[BOARDS][BANKS][CHANNELS];

	public:
		TrRunData();
		TrHistogram* getHistogram(int, int, int);
		void addSpill(TrSpillData, int);
		void print();
		int *getData();

};

#endif
