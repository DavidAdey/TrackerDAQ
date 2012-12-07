#include <iostream>
#include "TrHeaders.hh"

TrHistogramHeader::TrHistogramHeader() {}

TrHistogramHeader::TrHistogramHeader(int board, int bank, int channel, int type) {

	channelInfo = 0x0;
	channelInfo |= ((char)(board & 0xFF) << 16);
	//std::cout << "Board " << board << std::endl;
	//std::cout << std::hex << channelInfo << std::endl;
	channelInfo |= ((char)(bank & 0xFF) << 8);
	channelInfo |= ((char)(channel & 0xFF));
	channelInfo |= ((char)(type & 0xFF) << 24);
	//std::cout << std::hex << channelInfo << std::endl;

}

int TrHistogramHeader::getChannelInfo() {
	return channelInfo;
}

int TrHistogramHeader::getBoard() {
	return (channelInfo & 0xFF0000) >> 16;
}


int TrHistogramHeader::getBank() {
	return (channelInfo & 0xFF00) >> 8;
}

int TrHistogramHeader::getChannel() {
	return (channelInfo & 0xFF);
}

int TrHistogramHeader::getType() {
	return (channelInfo & 0xFF000000) >> 24;
}

void TrHistogramHeader::copy(TrHistogramHeader* other) {
	channelInfo = other->getChannelInfo();
}


//TrSpillHeader::TrSpillHeader() {}

//TrDataHeader::TrDataHeader() {}


