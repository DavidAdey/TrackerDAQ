#include "TrElectronics.hh"

TrElectronics::TrElectronics() {
	//r = new TRandom();
	parameters.insert( std::pair<std::string,double>("LEDMeanPE",2.0) );
}

int TrElectronics::trigger(int board, int bank, int channel, int mode, double bias) {
	//std::cout << "New trigger" << std::endl;
	int pe = 0;
	int dc = 0;
	double chargeTotal = 0.0;	
	switch (mode) {
		case 1:
			dc = int(0.2 * exp(bias));
			pe = int(parameters["LEDMeanPE"]);
			chargeTotal = chargeFromPE(board, bank, channel, pe);
			break;	
		case 2:
			pe = 0;
		default:
			pe = 0;
	}

	int adc = int(chargeTotal);
	if (adc < 0) {
		adc = 0;
	}
	return adc;
}

double TrElectronics::chargeFromPE(int board, int bank, int channel, int pe) {

	double chargeTotal = 0.0;
	for (int charge = 0; charge < pe; ++charge) {	
		double chargeRaw = gainList[board][bank][channel];
		double chargeReal = chargeRaw;
		chargeTotal += chargeReal;	
	}
	double pedestal = pedestalList[board][bank][channel];
	return (chargeTotal + pedestal);
}

void TrElectronics::setup() {

	generateNoiseRatios();
	generatePedestals();
	generateGains();

}

void TrElectronics::generateNoiseRatios() {

	for (unsigned int board=0; board<BOARDS; board++) {
		for (unsigned int bank=0; bank<BANKS; bank++) {
			for (unsigned int channel=0; channel<CHANNELS; channel++) {
				for (unsigned int peak=0; peak<PEAKS; peak++) {
					noiseRatios[board][bank][channel][peak] = 0.1*(pow(10,-peak));
				}
			}
		}
	}
}


void TrElectronics::generatePedestals() {

	for (unsigned int board=0; board<BOARDS; board++) {
		for (unsigned int bank=0; bank<BANKS; bank++) {
			for (unsigned int channel=0; channel<CHANNELS; channel++) {		
				pedestalList[board][bank][channel] = rand()%10 + 20.0;
			}
		}
	}
}

void TrElectronics::generateGains() {

	for (unsigned int board=0; board<BOARDS; board++) {
		for (unsigned int bank=0; bank<BANKS; bank++) {
			for (unsigned int channel=0; channel<CHANNELS; channel++) {		
				gainList[board][bank][channel] = rand()%10 + 10.0;
			}
		}
	}
}
