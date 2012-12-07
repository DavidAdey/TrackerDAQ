########################################################################
#                                                                      
#              --- CAEN SpA - Computing Division ---                   
#                                                                      
#   CAENVMElib Software Project                                        
#                                                                      
#   Created  :  March 2004      (Rel. 1.0)                                             
#                                                                      
#   Auth: S. Coluccini                                                 
#                                                                      
########################################################################

EXE	=	TrDAQ

CC	=	g++

COPTS	=	-fPIC -DLINUX -Wall -I
#COPTS	=	-g -fPIC -DLINUX -Wall 

FLAGS	=	-Wall -s -v $(shell $(ROOTSYS)/bin/root-config --glibs --libs) 
#FLAGS	=	-Wall

DEPLIBS	=       -l CAENVME -l curses -l mysqlclient -L ${ROOTSYS}/lib/ -lCore

LIBS	=
 
INCLUDEDIR =	$(ROOTSYS)/include/

OBJS	=	TrDAQ.o TrHistogram.o TrSpillData.o TrRunData.o	TrVMEModeChanger.o \
		TrReadout.o TrGenerator.o TrHeaders.o TrDAQManager.o TrElectronics.o \
		TrMySQLConnect.o TrVMEDevice.o TrVLSBController.o TrVLSBMasterController.o \
		TrSocket.o TrSocketServer.o TrSocketClient.o TrDAQSeniorManager.o

INCLUDES =	CAENVMElib.h CAENVMEtypes.h CAENVMEoslib.h TrDAQ.hh TrHistogram.hh \
		TrSpillData.hh TrRunData.hh TrVMEModeChanger.hh TrGenerator.hh \
		TrHeaders.hh TrDAQManager.hh TrElectronics.hh TrMySQLConnect.hh \
		TrReadout.hh TrVMEDevice.hh TrVLSBController.hh TrVLSBMasterController.hh \
		TrSocket.hh TrSocketServer.hh TrSocketClient.hh TrDAQSeniorManager.hh

#########################################################################

all	:	$(EXE)

clean	:
		/bin/rm -f $(OBJS) $(EXE)

$(EXE)	:	$(OBJS)
		/bin/rm -f $(EXE)
		$(CC) $(FLAGS) -o $(EXE) $(OBJS) $(DEPLIBS)

$(OBJS)	:	$(INCLUDES) Makefile

%.o	:	%.cc
		$(CC) $(COPTS) $(INCLUDEDIR) -c -o $@ $<

