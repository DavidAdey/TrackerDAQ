#include "TrGenerator.hh"

TrGenerator::TrGenerator() {

	electronics = TrElectronics();
	electronics.setup();
}

TrSpillData TrGenerator::generateRandom() {

	TrSpillData spill = TrSpillData();
	std::cout << "generating random" << std::endl;
	unsigned int triggersPerSpill = 100;
	for (unsigned int trigger=0; trigger<triggersPerSpill; ++trigger) {
	for (int i=0; i<BOARDS; i++) {
		for (int j=0; j<BANKS; j++) {
			for (int k=0; k<CHANNELS; k++) {

				TrHistogram h = TrHistogram();
				int* p = (int*)malloc(sizeof(int)*HISTOGRAMRANGE);
				int* ptr = p;
				int* ps = p;	
				for (int bin=0; bin<HISTOGRAMRANGE; bin++) {
					*ptr = rand();
					++ptr;	
				}
				h.convertFromBuffer(ps, HISTOGRAMRANGE);
				h.addHeader(TrHistogramHeader(i,j,k,0));
				spill.addHistogram(i,j,k,h);
				std::cout << i << " " << j << " " << k << std::endl;
				free(p);
				std::cout << "Memory freed" << std::endl;
				//delete ptr;
				//delete ps;
			}
		}
	}
	}
	return spill;
}

void TrGenerator::setBias(double b) {
	bias = b;
}

TrSpillData TrGenerator::generateSimulated() {

	TrSpillData spill = TrSpillData();		
	unsigned int triggersPerSpill = 100;
	for (unsigned int trigger=0; trigger<triggersPerSpill; ++trigger) {
		for (int i=0; i<BOARDS; i++) {
			for (int j=0; j<BANKS; j++) {
				for (int k=0; k<CHANNELS; k++) {
					TrHistogram *h = new TrHistogram();
					int* p = (int*)calloc(HISTOGRAMRANGE,sizeof(int));
					int* ptr = p;
					int* ps = p;		
					int adc = electronics.trigger(i,j,k, 1, bias);//(int)(j);
					ptr += adc;
					//std::cout << "*ptr = " << *ptr << std::endl;
					++(*ptr);
					//if (*ptr > 2) {
					//	std::cout << "Bigger than it should be" << std::endl;
					//}
					ptr += (HISTOGRAMRANGE - adc);		
					h->convertFromBuffer(ps, HISTOGRAMRANGE);
					h->addHeader(TrHistogramHeader(i,j,k,0));
					spill.addHistogram(i,j,k,*h);
					delete h;	
					free(p);
				}
			}
		}
	}
	return spill;
}
