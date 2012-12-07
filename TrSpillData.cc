#include "TrSpillData.hh"

TrSpillData::TrSpillData() {

}

TrHistogram* TrSpillData::getHistogram(int board, int bank, int channel) {

	return &data[board][bank][channel];

}

void TrSpillData::addHistogram(int board, int bank, int channel, TrHistogram histogram) {

	data[board][bank][channel] = histogram;

}
