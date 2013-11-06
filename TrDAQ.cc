#include "TrDAQ.hh"
#include "TrHistogram.hh"
#include "TrVMEModeChanger.hh"
#include "TrSpillData.hh"
#include "TrRunData.hh"
#include "TrGenerator.hh"
#include "TrReadout.hh"
#include "TrDAQManager.hh"
#include <iostream>
#include <fstream>
#include "TrMySQLConnect.hh"
#include "TROOT.h"
#include "TH1F.h"
#include <mysql/mysql.h>
#include <sys/socket.h>

#define SERVER "localhost"
#define USER "daq"
#define PASSWORD "daq"
#define DATABASE "Calibrations"

void writeRunToFile(TrRunData*);

int main( int argc, char *argv[]) {
/*
	printf("works\n");
	std::cout << "in c++" << std::endl;
	
	TrReadout readout = TrReadout();
	TrGenerator generator = TrGenerator();
	TrRunData run = TrRunData();

	for (int r=0; r<5; r++) {	
		run.addSpill(*readout.readout(generator),0);
	}

	//run.print();
	writeRunToFile(&run);
	TrVMEModeChanger mChange = TrVMEModeChanger();
	mChange.setVMEAccess();
	mChange.setDataAccess();
*/
	double bias = atof(argv[2]);
	std::string file = argv[1];
	//TH1F h1 = TH1F("a","a",10,0,10);
	TrDAQManager manager = TrDAQManager(argv[1]);
	manager.setNumberOfSpills(10);
	manager.go();
	/*for (int spill=0; spill<5; spill++) {
		if ((spill % 1) == 0) {
			std::cout << "Generated " << spill << " spills" << std::endl;
		}
		manager.setTriggerMode();
		manager.trigger(bias);
		manager.setReadoutMode();
		manager.readout();
		manager.build();
	}*/
	manager.write();
	//writeRunToFile(manager.getRunData());
}

int mysqlfunction(){
/******************************************/
	MYSQL *connect; // Create a pointer to the MySQL instance
    connect=mysql_init(NULL); // Initialise the instance
    /* This If is irrelevant and you don't need to show it. I kept it in for Fault Testing.*/
    if(!connect)    /* If instance didn't initialize say so and exit with fault.*/
    {
        fprintf(stderr,"MySQL Initialization Failed");
        return 1;
    }
    /* Now we will actually connect to the specific database.*/
 
    connect=mysql_real_connect(connect,SERVER,USER,PASSWORD,DATABASE,0,NULL,0);
    /* Following if statements are unneeded too, but it's worth it to show on your
    first app, so that if your database is empty or the query didn't return anything it
    will at least let you know that the connection to the mysql server was established. */
 
    if(connect){
        printf("Connection Succeeded\n");
    }
    else{
        printf("Connection Failed!\n");
    }


	MYSQL_RES *res_set; /* Create a pointer to recieve the return value.*/
    MYSQL_ROW row;  /* Assign variable for rows. */
    mysql_query(connect,"SELECT bias FROM Bias");
    /* Send a query to the database. */
    //unsigned int i = 0; /* Create a counter for the rows */
 
    res_set = mysql_store_result(connect); /* Receive the result and store it in res_set */
 
    unsigned int numrows = mysql_num_rows(res_set); /* Create the count to print all rows */
    std::cout << numrows << " rows total" << std::endl;
    unsigned int numfields = mysql_num_fields(res_set);
    for (unsigned int r=0; r<numrows; r++) {
    //while
    row = mysql_fetch_row(res_set);
    std::cout << r << std::endl;
    //{
    	for(unsigned int i = 0; i < numfields; i++)
    	{
		try {
			std::cout << r << " " << i << std::endl;
			std::cout <<  row[1] << std::endl;
			//std::cout << *val << std::endl;
		//	delete val;
		}
		catch (...) {
			std::cout << "Failed" << std::endl;
		}
    	}
	std::cout << std::endl;
    }
    mysql_close(connect);
	return 0;
/****************************************/		
}

void writeRunToFile(TrRunData *run) {
	std::cout << " writing to file " << std::endl;
	int headerIndicator = 0xC0FFEE;
	std::ofstream stream;
	stream.open ("data2.bin", std::ios::out | std::ios::binary);
	for (unsigned int board=0; board <BOARDS; board++) {
		for (unsigned int bank=0; bank<BANKS; bank++) {
			for (unsigned int channel=0; channel<CHANNELS; channel++){
				
				int *histPointer = run->getHistogram(board,bank,channel)->convertToBuffer();
				TrHistogram* hist = run->getHistogram(board,bank,channel);
				TrHistogramHeader* header = hist->getHeader();
				int info = header->getChannelInfo();
				//std::cout << info << std::endl;
				stream.write((char*)&headerIndicator,sizeof(int));
				stream.write((char*)&info,sizeof(int));
				stream.write((char*)histPointer,sizeof(int)*HISTOGRAMRANGE);
			}
		}
	}
	stream.close();
}

