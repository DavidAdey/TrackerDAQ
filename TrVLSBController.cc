#include "TrVMEDevice.hh"
#include "TrVLSBController.hh"


TrVLSBController::TrVLSBController() {}

void TrVLSBController::initialise() {

	TrVMEDevice::initialise();
	vlsbParameters.insert( std::pair<std::string, int> ("numberOfBanks",4) );
	vlsbParameters.insert( std::pair<std::string,int> ("bankAddressOffset",0x100000) );

	addresses.insert( std::pair<std::string, int> ("bank0",0x0) );
	addresses.insert( std::pair<std::string, int> ("bank1",0x4) );	
	addresses.insert( std::pair<std::string, int> ("bank2",0x8) );
	addresses.insert( std::pair<std::string, int> ("bank3",0xC) );
	addresses.insert( std::pair<std::string, int> ("control",0x10) );
	addresses.insert( std::pair<std::string, int> ("spillDuration",0x14) );	
	addresses.insert( std::pair<std::string, int> ("triggerSettings",0x18) );
	addresses.insert( std::pair<std::string, int> ("vetoSettings",0x1C) );	
	addresses.insert( std::pair<std::string, int> ("recordedTriggers",0x20) );
	addresses.insert( std::pair<std::string, int> ("lvdsControl",0x24) );	
	addresses.insert( std::pair<std::string, int> ("firmwareVersion",0x28) );
	addresses.insert( std::pair<std::string, int> ("fifoStatus",0x2C) );
	addresses.insert( std::pair<std::string, int> ("memoryStatus",0x30) );
	addresses.insert( std::pair<std::string, int> ("triggerTDC",0x34) );	
	addresses.insert( std::pair<std::string, int> ("bank0CRC",0x38) );
	addresses.insert( std::pair<std::string, int> ("bank1CRC",0x3C) );
	addresses.insert( std::pair<std::string, int> ("bank2CRC",0x40) );
	addresses.insert( std::pair<std::string, int> ("bank3CRC",0x44) );	
	
	fifoStatus.insert( std::pair<int, std::string> (0xF, "FIFO empty") );
	fifoStatus.insert( std::pair<int, std::string> (0xF0, "FIFO full") );
	fifoStatus.insert( std::pair<int, std::string> (0xF00, "FIFO timeout") );

	triggerSetting.insert( std::pair<std::string, int> ("spillEnable",0x4) );
	triggerSetting.insert( std::pair<std::string, int> ("continuousSpill",0x10) );
	triggerSetting.insert( std::pair<std::string, int> ("external",0x20) );
	triggerSetting.insert( std::pair<std::string, int> ("noZeroSuppression",0x40) );
	triggerSetting.insert( std::pair<std::string, int> ("noVeto",0x80) );

	lvdsSetting.insert( std::pair<std::string, int> ("disableLVDS", 0x0) );
	lvdsSetting.insert( std::pair<std::string, int> ("enableLVDS", 0x40) );
	
	bankLengths.resize(vlsbParameters["numberOfBanks"],0);
}

void TrVLSBController::getBankLengths() {
	
	int address = 0x0;
	int vmeStatus = 0x0;
	int banks = vlsbParameters["numberOfBanks"];
	for (int bank=0; bank < banks; ++bank) {
		address = baseAddress + addresses["banks"] + (bank*vlsbParameters["bankAddressOffset"]);
		try {
			vmeStatus |= CAENVME_ReadCycle( 0,address, &bankLengths[bank], cvA32_U_DATA, cvD32);
		}
		catch(...) {
			//std::cout << "VME Error" << std::endl;
		}
	}
}

void TrVLSBController::setReadoutMode() {
	CAENVME_WriteCycle(0, addresses["lvdsControl"], &lvdsSetting["disableLVDS"], addressModifier, dataWidth);
}

void TrVLSBController::setDataMode() {
	CAENVME_WriteCycle(0, addresses["lvdsControl"], &lvdsSetting["enableLVDS"], addressModifier, dataWidth);
}

int TrVLSBController::getTotalDataVolume() {
	int volume = 0;
	for (int bank=0; bank<4; ++bank) {
		volume += bankLengths[bank];
	}
	return volume;
}

int *TrVLSBController::readAllBanks() {
	int *dataPointer = (int*)calloc(getTotalDataVolume(), sizeof(int) );
	for (int bank = 0; bank < 4; ++bank) {
		readBank(bank, 0, dataPointer);
	}
	return dataPointer;
}

int TrVLSBController::readBank(int bank, int readoutMode, int* dataPointer = NULL) {

	int bytesRead = 0;
	unsigned int address = baseAddress + addresses["banks"] + bank*vlsbParameters["bankAddressOffset"];
	unsigned int addressArray[bankLengths[bank]];
	unsigned int dataBuffer[bankLengths[bank]];
	int nCycles = bankLengths[bank];
	CVErrorCodes errors[bankLengths[bank]];
	CVAddressModifier addressModifiers[bankLengths[bank]];
	CVDataWidth dataWidths[bankLengths[bank]];	
	for (int word=0; word<bankLengths[bank]; ++word) {
		addressArray[word] = address;
		dataBuffer[word] = 0;
		addressModifiers[word] = cvA32_U_DATA;
		dataWidths[word] = cvD32; 	
		address += 4;
	}
	try {	
		CAENVME_MultiRead(0,addressArray, dataBuffer, nCycles, addressModifiers, dataWidths, errors);
   	}
	catch (...) {
		//std::cout << "Failed to multiread VME" << std::endl;
	}
	
	/* Move the data from the buffer to somewher else, as required */
	switch(readoutMode) {
		case 0:
			if (!dataPointer) break;
			for (int j=0; j<bankLengths[bank]; j++){ 
      				*dataPointer = dataBuffer[j];
				dataPointer++;
      				bytesRead += 4;
    			} 
			break;
		default:
			//do nothing
			break;
	}
    	return bytesRead;

}

int TrVLSBController::getID() {return 0;}

