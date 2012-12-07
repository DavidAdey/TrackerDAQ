

#ifndef TRHEADERS_HH
#define TRHEADERS_HH

class TrHistogramHeader {

	private:
		int channelInfo;
	public:
		TrHistogramHeader();
		TrHistogramHeader(int,int,int,int);
		int getChannelInfo();
		int getBoard();
		int getBank();
		int getChannel();
		int getType();
		void copy(TrHistogramHeader*);

};

class TrSpillHeader {

	private:
		int timeStamp;
		int detector;
		int numTriggers;
		int errorFlags;
		int bankFlags;

	public:
		int getTimeStamp() {return timeStamp;}
		int getDetector() {return detector;}
		int getNumTriggers() {return numTriggers;}
		int getErrorFlags() {return errorFlags;}
};

class TrDataHeader {

	private:

		int timeStampBegin;
		int timeStampEnd;
		int numSpills;
		int errorFlags;

	public:

};

#endif
