#include "TrDAQManager.hh"

TrDAQManager::TrDAQManager(std::string file) {

	goCommands.insert(std::pair<std::string, int> ("getData",0x0));
        goCommands.insert(std::pair<std::string, int> ("getDataSize",0x1));
        goCommands.insert(std::pair<std::string, int> ("trigger",0x2));
        goCommands.insert(std::pair<std::string, int> ("dataMode",0x3));
	goCommands.insert(std::pair<std::string, int> ("readoutMode",0x4));
	dataBuffer = new TrRunData();
	fileName = file;
}

int TrDAQManager::setTriggerMode() {
	readoutController.setDataMode();
	return 0;
}

int TrDAQManager::setReadoutMode() {
	readoutController.setReadoutMode();
	return 0;
}

int TrDAQManager::trigger(double bias) {
	generator.setBias(bias);
	//std::cout << "Triggering" << std::endl;
	return 0;
}

int TrDAQManager::trigger() {
	readoutController.enableTrigger();
	return 0;
}

int TrDAQManager::stopTrigger() {
	readoutController.disableTrigger();
	return 0;
}

int TrDAQManager::waitForSpill() {return 0;}

int TrDAQManager::readout() {
	
	for (unsigned int s=0; s<1; s++) {
		//std::cout << "Reading spill " << s << std::endl;
		TrSpillData *newSpill = readoutController.readout(generator);
		currentSpills.push_back(*newSpill);
	}
	return 0;
}

int TrDAQManager::build() {
	//std::cout << "manager building" << std::endl;
	status = 3; 
	try {
		for (unsigned int spill=0; spill<currentSpills.size(); spill++) {
			//std::cout << "adding spill " << spill << std::endl;
			dataBuffer->addSpill(currentSpills[spill],0);
			
		}
		currentSpills.clear();
	}
	catch (...) {
		std::cout << "Failed to build" << std::endl;
		return -1;
	}
	//std::cout << "manager built" << std::endl;
	return 0;
}

int TrDAQManager::write() {

	std::ofstream stream;
	stream.open (fileName.c_str(), std::ios::out | std::ios::binary);
	for (unsigned int board=0; board <BOARDS; board++) {
		for (unsigned int bank=0; bank<BANKS; bank++) {
			for (unsigned int channel=0; channel<CHANNELS; channel++){
				
				int *histPointer = dataBuffer->getHistogram(board,bank,channel)->convertToBuffer();
				//TrHistogram* hist = dataBuffer->getHistogram(board,bank,channel);
				//TrHistogramHeader* header = hist->getHeader();
				//int info = header->getChannelInfo();
				//std::cout << info << std::endl;
				//stream.write((char*)&headerIndicator,sizeof(int));
				//stream.write((char*)&info,sizeof(int));
				stream.write((char*)histPointer,sizeof(int)*HISTOGRAMRANGE);
			}
		}
	}
	stream.close();
	return 0;
}

TrRunData* TrDAQManager::getRunData() {
	return dataBuffer;
}

int TrDAQManager::getCommands() {
	int command = socket.receiveData();
	switch(command) {
		case 0: //get the data
			go();
			transmit();
	//	case 1: //get the datasize
	//	case 2: //trigger
	}
	return 0;	
}	

int TrDAQManager::transmit() {
	int *dataPointer = dataBuffer->getData();
	int dataSize = BOARDS*BANKS*CHANNELS*BINS;
	socket.sendData(dataPointer, dataSize);
	return 0;
}

void TrDAQManager::go() {
	for (int spill=0; spill<5; spill++) {
		if ((spill % 10) == 0) {
			std::cout << "Generated " << spill << " spills" << std::endl;
		}
		setTriggerMode();
		trigger();
		waitForSpill();
		stopTrigger();	
		setReadoutMode();
		readout();
		build();
	}
	write();
}
