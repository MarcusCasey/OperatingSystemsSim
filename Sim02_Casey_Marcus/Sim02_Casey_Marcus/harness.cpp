/*
Marcus Casey
CS 446
Sim 02
Collaborators: None - Stack Overflow and cplusplus.com. 
*/


#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <pthread.h>
#include <limits.h>
#include <time.h>
#include "ConfigurationAPI.h"
#include "MetaDataAPI.h"
#include "processControlBlock.h"
#include "HarnessAPI.h"

using namespace std;


/* I have these functions in here because I can't figure out how to add them to my harness API
/* Likely this is due to the fact that they're pointing member functions and if I try to put them in there it breaks.
/* I ran out of time to place these in my header file but will for the next assignment. I don't want my main to be this long
*/
bool handleProcess(ConfigurationAPI, MetaDataAPI, PCB&);
bool systemHandler(PCB&, string);
bool finHandler(PCB&, string, int);
bool outputHandler(PCB&, string, int);
bool runProgram(ConfigurationAPI, deque<MetaDataAPI>, int);
bool memoryHandler(PCB&, int, string, int);
bool applicationHandler(PCB&, string);
bool processorHandler(PCB&, int);
bool allocateMemory(unsigned int, int);

unsigned int generateMemoryAddress();

void* timer(void*);
void* scannerHandler(void*);
void* keyboardHandler(void*);
void* hardDriveOutputHandler(void*);
void* monitorHandler(void*);
void* projectorHandler(void*);
void* hardDriveInputHandler(void*);


// global variables
ofstream fout;		
int outputType;
int newProcess=0;


// main
int main(int argc, char *argv[]) {
	// if there is an issue at any point in the file, flag this bool as false to end
	bool okToContinue;  	
	HarnessAPI harness;
	// This will store the data grabbed from the Configuration File
	ConfigurationAPI configurationData[argc - 1]; 
	deque<MetaDataAPI> metaDataCommandData[argc- 1];

	string metaDataFile;

	ifstream fin;
	for (int i = 0; i < argc; i++) {
		fin.open(argv[i]);
	if (fin.is_open() != true) {
	// if the file name is not read correctly and fin closes or doesn't open
			cout << "ERR: Your configuration filename is incorrect or not found.";
		} else if (i > 0) {
// otherwise loop through the data to store into our ConfigurationData ADT
			configurationData[i-1].loadConfigData(fin);
		}
		fin.close();
	}
	int j =0;
	//store metaDatainputFileName
	while (j < argc-1) {
		// metaDataFile to file name in config
		metaDataFile = configurationData[j].returnFileLocation();

		fin.open(metaDataFile);
		// if bool is not false
		okToContinue = harness.returnCommandInfoFile(fin, configurationData[j], metaDataCommandData[j]);
	
	fin.close();
// if true
	if (okToContinue == true) {
	harness.determineOutput(configurationData[j], metaDataCommandData[j]);
	}else{
	return -1;		
}

if (okToContinue== true) {
	outputType = configurationData[j].returnLogValue();
	okToContinue = runProgram(configurationData[j], metaDataCommandData[j], j);
}
fout.close();
j++;
}
return 1;
}

// execue main simulation runtime
bool runProgram(ConfigurationAPI configData, deque<MetaDataAPI> program, int programNum) {
	double length;
	clock_t start;
	bool okToContinue = 1;
	PCB programData;
	programData.assignPCBStartTime(0);
	programData.assignLengthProcess(0);
	programData.assignPID(programNum+1);

	start = clock();
	length = clock()-start;
	length = length / (double) CLOCKS_PER_SEC;
	
	//cout << "here is the clock time";

	if (outputType == 0) {
		cout << fixed << length << " - Simulator program starting" << endl;
	} else if (outputType == 1) {
		fout << fixed << length << " - Simulator program starting" << endl;
	} else if (outputType == 2) {
			cout << fixed << length << " - Simulator program starting" << endl;
			fout << fixed << length << " - Simulator program starting" << endl;
	} else {
			return 0;
	}
	int j=0;
	while (j < program.size()) {
		if (okToContinue == true) {
			length = ((clock() - start) / (double) CLOCKS_PER_SEC);
			programData.assignLengthProcess(length);
			okToContinue = handleProcess(configData, program[j], programData);
		} else {
			return 0;
		}
		length = clock()-start;
		length = length / (double) CLOCKS_PER_SEC;
		j++;
	}
	if (outputType == 0) {
		cout << fixed << length << " - Simulator program ending" << endl;
	} else if (outputType == 1) {
		fout << fixed << length << " - Simulator program ending" << endl;
	} else if (outputType == 2) {
			cout << fixed << length << " - Simulator program ending" << endl;
			fout << fixed << length << " - Simulator program ending" << endl;
	} else {
			return 0;
	}
	return 1;
}


bool handleProcess(ConfigurationAPI cData, MetaDataAPI process, PCB& pData) {

	if ((int) process.returnCommand() == 'S') {
			return systemHandler(pData, process.returnDescription());	
	} else if ((int) process.returnCommand() == 'A'){
		return applicationHandler(pData, process.returnDescription());
	} else if ((int) process.returnCommand() == 'P'){
		return processorHandler(pData, process.returnTimeElapsed());
	} else if ((int) process.returnCommand() == 'M') {
		return memoryHandler(pData, cData.returnSysMemory(), process.returnDescription(), process.returnTimeElapsed());
	} else if ((int) process.returnCommand() == 'I') {
		return finHandler(pData, process.returnDescription(), process.returnTimeElapsed());
	} else if ((int) process.returnCommand() == 'O') {
		return outputHandler(pData, process.returnDescription(), process.returnTimeElapsed());
	} else {
			return 0;
	}
}

bool systemHandler(PCB& pData, string descriptionInputriptor) {
	clock_t start;
	double length;
	start = clock();
	int pid = pData.getpid();
	

	if (descriptionInputriptor == "begin") {
		 if (outputType == 0) {
		} else if (outputType == 1) {
				fout << pData.returnLengthProcess() << " - OS: preparing process " << newProcess << endl;
		} else if (outputType == 2) {
				fout << pData.returnLengthProcess() << " - OS: preparing process " << newProcess << endl;
		} else {
				return 0;
		}
		length = clock()-start;
		length = length / (double) CLOCKS_PER_SEC;

		pData.replaceLengthProcess(length);
		pData.processState = 2;

		  if (outputType == 0) {
			cout << pData.returnLengthProcess() << " - OS: preparing process " << newProcess << endl;
		} else if (outputType == 1) {
			fout << pData.returnLengthProcess() << " - OS: preparing process " << newProcess << endl;
		} else if (outputType == 2) {
			fout << pData.returnLengthProcess() << " - OS: preparing process " << newProcess << endl;
		} else {
			return 0;
		}
	} else if (descriptionInputriptor == "finish") {
			 if (outputType == 0) {
				cout << pData.returnLengthProcess() << " - OS: removing process " << newProcess << endl;
		} else if (outputType == 1) {
				fout << pData.returnLengthProcess() << " - OS: removing process " << newProcess << endl;
		} else if (outputType == 2) {
				cout << pData.returnLengthProcess() << " - OS: removing process " << newProcess << endl;
				fout << pData.returnLengthProcess() << " - OS: removing process " << newProcess << endl;
		} else {
				return 0;
		}
		pData.processState = 4;
	} 
	return 1;
}

bool applicationHandler(PCB& pData, string descriptionInputriptor) {
	clock_t start;
	double length;
	start = clock();
	int pid = pData.getpid();
	if (descriptionInputriptor == "begin") {
// second process		
	newProcess +=1;	
		if (outputType == 0) {
			cout << pData.returnLengthProcess() << " - OS: preparing process " << newProcess << endl;
		} else if (outputType == 1) {
			fout << pData.returnLengthProcess() << " - OS: preparing process " << newProcess << endl;
		} else if (outputType == 2) {
			cout << pData.returnLengthProcess() << " - OS: preparing process " << newProcess << endl;
			fout << pData.returnLengthProcess() << " - OS: preparing process " << newProcess << endl;
		} else {
			return 0;
		}
		length = clock()-start;
		length = length / (double) CLOCKS_PER_SEC;
		pData.replaceLengthProcess(length);
		pData.processState = 2;
		if (outputType == 0) {
			cout << pData.returnLengthProcess() << " - OS: starting process " << newProcess << endl;
		} else if (outputType == 1) {
			fout << pData.returnLengthProcess() << " - OS: starting process " << newProcess << endl;
		} else if (outputType == 2) {
			cout << pData.returnLengthProcess() << " - OS: starting process " << newProcess << endl;
			fout << pData.returnLengthProcess() << " - OS: starting process " << newProcess << endl;
		} else {
		return 0;
		}
	}
	else if (descriptionInputriptor == "finish") {
		if (outputType == 0) {
			cout << pData.returnLengthProcess() << " - OS: removing process " <<  newProcess << endl;
		} else if (outputType == 1) {
			fout << pData.returnLengthProcess() << " - OS: removing process " << newProcess << endl;
		} else if (outputType == 2) {
			fout << pData.returnLengthProcess() << " - OS: removing process " << newProcess << endl;
		} else {
				return 0;
		}
		pData.processState = 4;
	} else {
		return 0;
	}
	return 1;
}


bool processorHandler(PCB& pData, int processTime) {
	int rc, pid = pData.getpid();
	pthread_t timerThread;
	double length;	
	long pTime = (long) processTime;
	clock_t start;
	
	start = clock();

	length = clock()-start;
	length = length / (double) CLOCKS_PER_SEC;
	pData.replaceLengthProcess(length);
 // can't use if's, have to use switch	since if I used an if, it would catch it twice, fix this later, don't like switches
	switch (outputType) {
	case 0:
		cout << pData.returnLengthProcess() << " - Process " << newProcess << ": start processing action" << endl;
	break;
	case 1:
		fout << pData.returnLengthProcess() << " - Process " << newProcess <<  ": start processing action" << endl;
	break;
	case 2:
		cout << pData.returnLengthProcess() << " - Process " << newProcess << ": start processing action" << endl;
		fout << pData.returnLengthProcess() << " - Process " << newProcess << ": start processing action" << endl;
	break;
	default:
	return 0;
	}

	pData.processState = 4;
	// first thread 
	rc = pthread_create(&timerThread, NULL, &timer, (void*)pTime);
	
	pthread_join(timerThread, NULL);
	
	pData.processState = 3;
	length = ((clock() - start) / (double) CLOCKS_PER_SEC) - length;
	pData.replaceLengthProcess(length);
 // can't use if's, have to use switch	since if I used an if, it would catch it twice, fix this later, don't like switches
	switch (outputType) {
	case 0:
		cout << pData.returnLengthProcess() << " - Process " << newProcess << ": end processing action" << endl;
	break;
	case 1:
		fout << pData.returnLengthProcess() << " - Process " << newProcess << ": end processing action" << endl;
	break;
	case 2:
		cout << pData.returnLengthProcess() << " - Process " << newProcess <<  ": end processing action" << endl;
		fout << pData.returnLengthProcess() << " - Process " << newProcess <<  ": end processing action" << endl;
	break;
	default:
		return 0;
	}
	return 1;
}

bool memoryHandler(PCB& pData, int sysMemory, string descriptionInputriptor, int processTime) {
	clock_t start;
	double length;
	pthread_t timerThread;
	long pTime = (long) processTime;
	int rc, pid = pData.getpid();
	
	start = clock();
	
	if (descriptionInputriptor == "allocate") {
		length = clock()-start;
		length = length / (double) CLOCKS_PER_SEC;
		pData.replaceLengthProcess(length);
	 // can't use if's, have to use switch	since if I used an if, it would catch it twice, fix this later, don't like switches
	switch (outputType) {
		case 0:
			cout << pData.returnLengthProcess() << " - Process " << pid << ": allocating memory" << endl;
		break;
		case 1:
			fout << pData.returnLengthProcess() << " - Process " << pid << ": allocating memory" << endl;
		break;
		case 2:
			cout << pData.returnLengthProcess() << " - Process " << pid << ": allocating memory" << endl;
			fout << pData.returnLengthProcess() << " - Process " << pid << ": allocating memory" << endl;
		break;
		default:
			// success
			return 0;
		}
		unsigned int addr;
		pData.processState = 4;
		rc = pthread_create(&timerThread, NULL, &timer, (void*)pTime);

		addr = generateMemoryAddress();
		
		pthread_join(timerThread, NULL);
		length = clock()-start;
		length = length / (double) CLOCKS_PER_SEC;
		
		pData.replaceLengthProcess(length);
	switch (outputType) {
		case 0:
			cout << pData.returnLengthProcess() << " - Process " << pid << ": memory allocated at 0x" << hex << addr << endl << dec;
		break;
		case 1:
			fout << pData.returnLengthProcess() << " - Process " << pid << ": memory allocated at 0x" << hex << addr << endl << dec;
		break;
		case 2:
			cout << pData.returnLengthProcess() << " - Process " << pid << ": memory allocated at 0x" << hex << addr << endl << dec;
			fout << pData.returnLengthProcess() << " - Process " << pid << ": memory allocated at 0x" << hex << addr << endl << dec;
			break;
			default:
				return 0;
		}
	} else if (descriptionInputriptor == "block") {
	
		length = clock()-start;
		length = length / (double) CLOCKS_PER_SEC;
		pData.replaceLengthProcess(length);

		switch (outputType) {
		case 0:
			cout << pData.returnLengthProcess() << " - Process " << pid <<  ": start memory blocking" << endl;
		break;
		case 1:
			fout << pData.returnLengthProcess() << " - Process " << pid << ": start memory blocking" << endl;
		break;
		case 2: cout << pData.returnLengthProcess() << " - Process " << pid << ": start memory blocking" << endl;
			fout << pData.returnLengthProcess() << " - Process " << pid << ": start memory blocking" << endl;
		break;
		default:
		return 0;
		}
	
		pData.processState = 3;
		
		rc = pthread_create(&timerThread, NULL, &timer, (void*)pTime);
		
		pthread_join(timerThread, NULL);
	
		pData.processState = 4;

		length = clock()-start;
		length = length / (double) CLOCKS_PER_SEC;
		
		pData.replaceLengthProcess(length);
	switch (outputType) {
		case 0:
			cout << pData.returnLengthProcess() << " - Process " << pid << ": end memory blocking" << endl;
		break;
		case 1:
			fout << pData.returnLengthProcess() << " - Process " << pid << ": end memory blocking" << endl;
		break;
		case 2:
			cout << pData.returnLengthProcess() << " - Process " << pid << ": end memory blocking" << endl;
			fout << pData.returnLengthProcess() << " - Process " << pid << ": end memory blocking" << endl;
		break;
		default:
		return 0;
		}
	} else {
		return 0;
	}
}

bool finHandler(PCB& pData, string descriptionInputriptor, int processTime) {
	pthread_t finThread;
	clock_t start;
	int rc, pid = pData.getpid();
	long pTime = (long) processTime;
	double length;

	start = clock();
	
	length = clock()-start;
	length = length / (double) CLOCKS_PER_SEC;
	pData.replaceLengthProcess(length);
	
	switch (outputType) {
	case 0:
		cout << pData.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInputriptor << " input" << endl;
		break;
	case 1:
		fout << pData.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInputriptor << " input" << endl;
		break;
	case 2:	cout << pData.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInputriptor << " input" << endl;
		fout << pData.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInputriptor << " input" << endl;
		break;
		default:
		return 0;
	}
	if (descriptionInputriptor == "hard drive") {
		pData.processState = 2;
		rc = pthread_create(&finThread, NULL, &hardDriveInputHandler, (void*)pTime);
	} else if (descriptionInputriptor == "keyboard") {
	
		pData.processState = 2;
		rc = pthread_create(&finThread, NULL, &keyboardHandler, (void*)pTime);
	} else if (descriptionInputriptor == "scanner") {
		pData.processState = 2;
		rc = pthread_create(&finThread, NULL, &scannerHandler, (void*)pTime);
	} else {
		return 0;
	}
	pData.processState = 4;
	pthread_join(finThread, NULL);

	pData.processState = 1;

	length = clock()-start;
	length = length / (double) CLOCKS_PER_SEC;
	pData.replaceLengthProcess(length);
	switch (outputType) {
	case 0:
		cout << pData.returnLengthProcess() << " - Process " << pid << ": end " << descriptionInputriptor << " fin" << endl;
	break;
	case 1:
		fout << pData.returnLengthProcess() << " - Process " << pid << ": end " << descriptionInputriptor << " fin" << endl;
	break;
	case 2: cout << pData.returnLengthProcess() << " - Process " << pid << ": end " << descriptionInputriptor << " fin" << endl;
		fout << pData.returnLengthProcess() << " - Process " << pid << ": end " << descriptionInputriptor << " fin" << endl;
	break;
	default:
		return 0;
	}
return 1;
}

// create address
unsigned int generateMemoryAddress() {
	unsigned int address;
	srand(time(NULL));
	address = rand() % UINT_MAX;
	return address;
}


// timer
void* timer(void* milliseconds) {
	long m = (long) milliseconds;
	clock_t timerEnd = clock() + m * CLOCKS_PER_SEC/1000;
	while(clock() < timerEnd) {
	};
}


bool outputHandler(PCB& pData, string descriptionInputriptor, int processTime) {

	
	double length;
	long pTime;
	int rc, pid = pData.getpid();
	pthread_t outputThread;
	clock_t start;
	
	pTime=(long) processTime;
	start = clock();
	

	length = clock()-start;
	length = length / (double) CLOCKS_PER_SEC;
	
	pData.replaceLengthProcess(length);

switch (outputType) {
	case 0:
		cout << pData.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInputriptor << " output" << endl;
	break;
	case 1:
		fout << pData.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInputriptor << " output" << endl;
	break;
	case 2: cout << pData.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInputriptor << " output" << endl;
		fout << pData.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInputriptor << " output" << endl;
	break;
	default:
		return 0;
	}
	
	if (descriptionInputriptor == "hard drive") {
		pData.processState = 3;
		rc = pthread_create(&outputThread, NULL, &hardDriveOutputHandler, (void*)pTime);
	} else if (descriptionInputriptor == "monitor") {
		pData.processState = 3;
		rc = pthread_create(&outputThread, NULL, &monitorHandler, (void*)pTime);
	} else if (descriptionInputriptor == "projector") {
		pData.processState = 3;
		rc = pthread_create(&outputThread, NULL, &projectorHandler, (void*)pTime);
	} else {
		return 0;
	}
	

	pData.processState = 3;
	
	pthread_join(outputThread, NULL);

	pData.processState = 4;
	length = clock()-start;
	length = length / (double) CLOCKS_PER_SEC;
	pData.replaceLengthProcess(length);
	switch (outputType) {
	case 0:
		cout << pData.returnLengthProcess() << " - Process " << newProcess << ": end " << descriptionInputriptor << " output" << endl;
		fout << pData.returnLengthProcess() << " - Process " << newProcess << ": end " << descriptionInputriptor << " output" << endl;
	break;
	case 1:
		fout << pData.returnLengthProcess() << " - Process " << newProcess << ": end " << descriptionInputriptor << " output" << endl;
	break;
	case 2:
		cout << pData.returnLengthProcess() << " - Process " << newProcess << ": end " << descriptionInputriptor << " output" << endl;
		fout << pData.returnLengthProcess() << " - Process " << newProcess << ": end " << descriptionInputriptor << " output" << endl;
	break;
	default:
	return 0;
	}
	return 1;
}

// join on process wait
void* monitorHandler(void* mTime) {
	int rc;
	pthread_t timerThread;

	rc = pthread_create(&timerThread, NULL, &timer, (void*)mTime);
	pthread_join(timerThread, NULL);

}

//join on process wait
void* keyboardHandler(void* kTime) {
	int rc;
	pthread_t timerThread;

	rc = pthread_create(&timerThread, NULL, &timer, (void*)kTime);
	pthread_join(timerThread, NULL);
}
 
// join on process wait 
void* projectorHandler(void* pTime) {
	int rc;
	pthread_t timerThread;

	rc = pthread_create(&timerThread, NULL, &timer, (void*)pTime);
	pthread_join(timerThread, NULL);
}
// join on process wait
void* hardDriveInputHandler(void* hdTime) {
	int rc;
	pthread_t timerThread;
	
	rc = pthread_create(&timerThread, NULL, &timer, (void*)hdTime);
	pthread_join(timerThread, NULL);

}

// join on process wait
void* scannerHandler(void* sTime) {
	int rc;
	pthread_t timerThread;
	rc = pthread_create(&timerThread, NULL, &timer, (void*)sTime);
	pthread_join(timerThread, NULL);

}

// join on process wait
void* hardDriveOutputHandler(void* hdTime) {
	int rc;
	pthread_t timerThread;
	rc = pthread_create(&timerThread, NULL, &timer, (void*)hdTime);
	pthread_join(timerThread, NULL);
}
