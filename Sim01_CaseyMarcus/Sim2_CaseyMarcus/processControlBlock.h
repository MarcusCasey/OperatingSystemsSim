/*
Marcus Casey
CS 446
Sim 02
Collaborators: None - Stack Overflow and cplusplus.com + tutorial posted on project - largely modeled after that
*/

#ifndef process_Control_Block
#define process_Control_Block

#include <iostream>
#include <deque>
#include <string>
#include <pthread.h>
#include <time.h>
#include "MetaDataAPI.h"

using namespace std;

class PCB {
public:	
	PCB();
	PCB(int);
	~PCB();
		
	int getpid();

	void assignLengthProcess(double);
	
	double returnPCBStartTime();
	double returnLengthProcess();
	void assignPID(int);
	void replaceLengthProcess(double);	
	int processState;
	void assignPCBStartTime(double);
	
private:
	int WAIT =0;
	int START =0;
	int READY =0;
	int BEGIN =0;
	int FINISH =0;
	
	double lengthProcess;
	double startingTime;
	
	int pid;
};
#endif
