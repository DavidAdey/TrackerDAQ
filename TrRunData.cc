#include "TrRunData.hh"
#include "TrSpillData.hh"

TrRunData::TrRunData() {

}

void TrRunData::addSpill(TrSpillData spill, int asBinary=0) {

	if (asBinary) {
		std::cout << "Adding data blocks" << std::endl;
	}
	else {
		for (unsigned int board=0; board<BOARDS; board++) {
			for (unsigned int bank=0; bank<BANKS; bank++) {
				for (unsigned int channel=0; channel<CHANNELS; channel++) {
					//std::cout << "adding histogram " << board << " " << bank << " " << channel << std::endl;
					//print();
					data[board][bank][channel].add(spill.getHistogram(board,bank,channel));
				}
			}
		}
	}	
}

void TrRunData::print() {

	for (unsigned int board=0; board<BOARDS; board++) {
		for (unsigned int bank=0; bank<BANKS; bank++) {
			for (unsigned int channel=0; channel<CHANNELS; channel++) {
				for (unsigned int bin=0; bin<256; bin++) {
					//std::cout << "getting bin value" << std::endl;
					std::cout << data[board][bank][channel].getBinValue(bin) << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

TrHistogram* TrRunData::getHistogram(int board, int bank, int channel) {
	return &data[board][bank][channel];
}

int *TrRunData::getData() {
	int *dataPointer = (int*)calloc(BOARDS*BANKS*CHANNELS*BINS, sizeof(int));
	int *pointerCopy = dataPointer;	
	for (unsigned int board=0; board<BOARDS; board++) {
		for (unsigned int bank=0; bank<BANKS; bank++) {
			for (unsigned int channel=0; channel<CHANNELS; channel++) {
				for (unsigned int bin=0; bin<BINS; bin++) {
					//std::cout << "getting bin value" << std::endl;
					*pointerCopy = data[board][bank][channel].getBinValue(bin);
					++pointerCopy;
				}
			}
		}
	}
	return dataPointer;
}
