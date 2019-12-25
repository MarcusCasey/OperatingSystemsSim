/*
Marcus Casey
CS 446
Sim 05
Collaborators: None - Stack Overflow and cplusplus.com + tutorial posted on project - largely modeled after that
*/

#ifndef process_Control_Block
#define process_Control_Block

#include <string>
#include <iostream>
#include <pthread.h>
#include <time.h>
#include <deque>

#include "MetaDataAPI.h"

using namespace std;

class PCB {
public:	
	PCB();
	PCB(int);
	~PCB();
	
	int currentProcesstype;
	
	int getPID();

	int returnBlockAmt();
	int returnPrevMemAdd();
	int returnHardDriveAmtPCB();
	int returnHardDriveAmtUtil();
	int returnProjAmtUtil();
	int getProjectorsUsed();


	double returnPCBStartTime();
	double returnLengthProcess();
	
	void assignPID(int);
	void assignLengthProcess(double);
	void replaceLengthProcess(double);	
	void assignPCBStartTime(double);
	
	void setHardDrivesUsed(int);
	void assignProjAmtPCB(int);
	void addProjAmt();
	void assignBlockAmtPCB(int);
	void addHardDriveAmt();
	void assignPrevAddr(int);
	void assignHardDriveAmtPCB(int);
	void assignProjAmtUtilPCB(int);
	void addBlockAmt();

// new fncs

	bool isInterrupted();
	bool hasBeenInterrupted();
	int returnQueueIndex();
	double returnEstimatedProcessTime();
	double returnEstimatedTimeRemaining();
	void interrupt();
	void assignInterrupt(bool);
	void assignInterruptOccurred(bool);
	void assignQueueIndex(int);
	void assignEstimatedProcessTime(double);
	void assignEstimatedTimeRemaining(double);
	void saveState(double);
	double loadState();


private:
	int WAIT =0;
	int START =0;
	int READY =0;
	int BEGIN =0;
	int FINISH =0;
	
	double lengthProcess;
	double startingTime;
	
	int blockAmtNumPCB, prevAddr;
	int hardDriveAmtNumPCB, hardDrivesUsed, projAmtNumPCB, projAmtUtilNumPCB;	
	double startTime, processDuration;
	int pid;

// new variables 

	bool interrupted, interruptAction;
	int queueIndex;
	double estimatedProcessTime, estimatedTimeRemaining, processData;

};
#endif
