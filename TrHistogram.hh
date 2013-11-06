#include "TrGlobals.hh"
#include "TrHeaders.hh"
#include <iostream>
#include <vector>
#include <stdlib.h>

#ifndef TRHISTOGRAM_HH
#define TRHISTOGRAM_HH

class TrHistogram {

	private:

		std::vector<int> bins;
		TrHistogramHeader header;
	public:

		TrHistogram();
		void fill(int);
		void setBinValue(int,int);
		int getBinValue(int);
		void convertFromBuffer(int*,int);
		int* convertToBuffer();
		void add(TrHistogram*);
		void addHeader(TrHistogramHeader);

		TrHistogramHeader* getHeader() {return &header;};
};

#endif
