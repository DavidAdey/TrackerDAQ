#include "TrReadout.hh"

TrReadout::TrReadout() {}

TrSpillData* TrReadout::readout() {

	for (unsigned int vlsb=0; vlsb<vlsbs.size(); ++vlsb) {
		vlsbs[vlsb].getBankLengths(); 
		TrSpillData boardSpill = compress(vlsbs[vlsb].readAllBanks(), vlsbs[vlsb].getTotalDataVolume(), vlsbs[vlsb].getID());
	}
	return &currentSpill;

}

TrSpillData* TrReadout::readout(TrGenerator generator) {

	currentSpill = generator.generateSimulated();
	return &currentSpill;
}

TrSpillData TrReadout::compress(int *dataPointer, int dataVolume, int id) {
	
	TrSpillData spill = TrSpillData();
	int channel = 0;
	for (int word=0; word < dataVolume; ++word) {
		int adc = ( (*dataPointer) & 0xFF );
		int bank = int(channel / 128);
		int realChannel = channel % 128;
		TrHistogram *histogram = spill.getHistogram(id, bank, realChannel);
		histogram->fill(adc);
		delete histogram;
		++channel;
		if (channel == 512) channel = 0;	
		++dataPointer;
	}
	return spill;
}

void TrReadout::setDataMode() {
	for (unsigned int vlsb=0; vlsb<vlsbs.size(); ++vlsb) {
		vlsbs[vlsb].setDataMode();
	}
}
void TrReadout::setReadoutMode() {	
	for (unsigned int vlsb=0; vlsb<vlsbs.size(); ++vlsb) {
		vlsbs[vlsb].setReadoutMode();
	}
}

void TrReadout::enableTrigger() {
	master.enableTrigger();
}

void TrReadout::disableTrigger() {
	master.disableTrigger();
}

int TrReadout::pollSpillDone() {
	return master.getSpillDone();
}


 
