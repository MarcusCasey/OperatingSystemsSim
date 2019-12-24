/*
Marcus Casey
CS 446
Sim 03
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
// used hex and setw
#include <iomanip>

using namespace std;

// ok to continue


/* I have these functions in here because I can't figure out how to add them to my harness API
/* Likely this is due to the fact that they're pointing member functions and if I try to put them in there it breaks.
/* I ran out of time to place these in my header file but will for the next assignment. I don't want my main to be this long
*/


bool handleProcess(ConfigurationAPI, MetaDataAPI, PCB&);
bool systemHandler(PCB&, string);
bool finHandler(PCB&, string, int);
bool outputHandler(PCB&, string, int);
bool executeMain(ConfigurationAPI, deque<MetaDataAPI>, int);
bool memHandler(PCB&, ConfigurationAPI, string, int);
bool mainHandler(PCB&, string);
bool processorHandler(PCB&, int);
int allocMem(PCB&, ConfigurationAPI);

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
int detToOutput;
int newProcess=0;


pthread_mutex_t hardDriveMx;
pthread_mutex_t keyboardMx;
pthread_mutex_t mutexScanner;
pthread_mutex_t mutexMonitor;
pthread_mutex_t projectorMx;


// main
int main(int argc, char *argv[]) {
	// if there is an issue at any point in the file, flag this bool as false to end
	bool ifNotFalse;  	
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
			cout << "ERR: configuration not found.";
	return -1;
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
		ifNotFalse = harness.returnCommandInfoFile(fin, configurationData[j], metaDataCommandData[j]);
	
	fin.close();
// if true
	if (ifNotFalse == true) {
	harness.determineOutput(configurationData[j], metaDataCommandData[j]);
	}else{
	return -1;		
}

if (ifNotFalse== true) {
	detToOutput = configurationData[j].returnLogValue();
	ifNotFalse = executeMain(configurationData[j], metaDataCommandData[j], j);
}
fout.close();
		pthread_mutex_destroy(&keyboardMx);
		pthread_mutex_destroy(&mutexScanner);
		pthread_mutex_destroy(&mutexMonitor);
		pthread_mutex_destroy(&projectorMx);
j++;


}
return 1;
}

// execute main simulation runtime
bool executeMain(ConfigurationAPI configurationInputData, deque<MetaDataAPI> programInputDataMain, int pInputMainNum) {
	
	double length;
	clock_t start;
	bool ifNotFalse = 1;
	PCB programInputDataMainData;

	programInputDataMainData.assignPCBStartTime(0);
	programInputDataMainData.assignLengthProcess(0);
	programInputDataMainData.assignPID(pInputMainNum+1);
	programInputDataMainData.assignHardDriveAmtPCB(configurationInputData.returnHdAmt());
	programInputDataMainData.assignProjAmtPCB(configurationInputData.returnProjAmount());

	pthread_mutex_init(&hardDriveMx, NULL);
	pthread_mutex_init(&keyboardMx, NULL);
	pthread_mutex_init(&mutexScanner, NULL);
	pthread_mutex_init(&mutexMonitor, NULL);
	pthread_mutex_init(&projectorMx, NULL);


	start = clock();
	length = clock()-start;
	length = length / (double) CLOCKS_PER_SEC;
	
	//cout << "here is the clock time";

	if (detToOutput == 0) {
		cout << fixed << length << " - Simulator program starting" << endl;
	} else if (detToOutput == 1) {
		fout << fixed << length << " - Simulator program starting" << endl;
	} else if (detToOutput == 2) {
			cout << fixed << length << " - Simulator program starting" << endl;
			fout << fixed << length << " - Simulator program starting" << endl;
	} else {
			return 0;
	}
	int j=0;
	while (j < programInputDataMain.size()) {
		if (ifNotFalse == true) {
			length = ((clock() - start) / (double) CLOCKS_PER_SEC);
			programInputDataMainData.assignLengthProcess(length);
			ifNotFalse = handleProcess(configurationInputData, programInputDataMain[j], programInputDataMainData);
		} else {
			return 0;
		}
		length = clock()-start;
		length = length / (double) CLOCKS_PER_SEC;
		j++;
	}
	if (detToOutput == 0) {
		cout << fixed << length << " - Simulator program ending" << endl;
	} else if (detToOutput == 1) {
		fout << fixed << length << " - Simulator program ending" << endl;
	} else if (detToOutput == 2) {
			cout << fixed << length << " - Simulator program ending" << endl;
			fout << fixed << length << " - Simulator program ending" << endl;
	} else {
			return 0;
	}
	return 1;
}


bool handleProcess(ConfigurationAPI configInfo, MetaDataAPI process, PCB& processInfo) {

	if ((int) process.returnCommand() == 'S') {
			return systemHandler(processInfo, process.returnDescription());	
	} else if ((int) process.returnCommand() == 'A'){
		return mainHandler(processInfo, process.returnDescription());
	} else if ((int) process.returnCommand() == 'P'){
		return processorHandler(processInfo, process.returnTimeElapsed());
	} else if ((int) process.returnCommand() == 'M') {
		return memHandler(processInfo, configInfo, process.returnDescription(), process.returnTimeElapsed());
	} else if ((int) process.returnCommand() == 'I') {
		return finHandler(processInfo, process.returnDescription(), process.returnTimeElapsed());
	} else if ((int) process.returnCommand() == 'O') {
		return outputHandler(processInfo, process.returnDescription(), process.returnTimeElapsed());
	} else {
			return 0;
	}
}

// sys handler... 
bool systemHandler(PCB& processInfo, string descriptionInterpreter) {
	clock_t start;
	double length;
	start = clock();
	int pid = processInfo.getPID();
	

	if (descriptionInterpreter == "begin") {

		length = clock()-start;
		length = length / (double) CLOCKS_PER_SEC;

		processInfo.replaceLengthProcess(length);
		processInfo.currentProcesstype = 1;

		  if (detToOutput == 0) {
		} else if (detToOutput == 1) {
			fout << processInfo.returnLengthProcess() << " - OS: preparing process " << newProcess << endl;
		} else if (detToOutput == 2) {
			fout << processInfo.returnLengthProcess() << " - OS: preparing process " << newProcess << endl;
		} else {
			return 0;
		}
	} else if (descriptionInterpreter == "finish") {
			 if (detToOutput == 0) {
		} else if (detToOutput == 1) {
				fout << processInfo.returnLengthProcess() << " - OS: removing process " << newProcess << endl;
		} else if (detToOutput == 2) {
				cout << processInfo.returnLengthProcess() << " - OS: removing process " << newProcess << endl;
				fout << processInfo.returnLengthProcess() << " - OS: removing process " << newProcess << endl;
		} else {
				return 0;
		}
		processInfo.currentProcesstype = 4;
	} 
	return 1;
}

bool mainHandler(PCB& processInfo, string descriptionInterpreter) {
	clock_t start;
	double length;
	start = clock();
	int pid = processInfo.getPID();
	if (descriptionInterpreter == "begin") {
// second process
	newProcess +=1;	
		if (detToOutput == 0) {
			
			cout << processInfo.returnLengthProcess() << " - OS: preparing process " << newProcess << endl;
		
		} else if (detToOutput == 1) {
			
			fout << processInfo.returnLengthProcess() << " - OS: preparing process " << newProcess << endl;
		
		} else if(detToOutput == 2) {

			cout << processInfo.returnLengthProcess() << " - OS: preparing process " << newProcess << endl;
			fout << processInfo.returnLengthProcess() << " - OS: preparing process " << newProcess << endl;
		
		} else {
			
			return 0;
		}
		
		length = clock()-start;
		length = length / (double) CLOCKS_PER_SEC;
		
		processInfo.replaceLengthProcess(length);
		processInfo.currentProcesstype = 2;
		
		if (detToOutput == 0) {
			
			cout << processInfo.returnLengthProcess() << " - OS: starting process " << newProcess << endl;
		
		} else if(detToOutput == 1) {
			
			fout << processInfo.returnLengthProcess() << " - OS: starting process " << newProcess << endl;
		
		} else if(detToOutput == 2) {

			cout << processInfo.returnLengthProcess() << " - OS: starting process " << newProcess << endl;
			fout << processInfo.returnLengthProcess() << " - OS: starting process " << newProcess << endl;

		} else {
		
		return 0;
		
		}
	} else if (descriptionInterpreter == "finish") {
		
		if(detToOutput == 0) {
			
			cout << processInfo.returnLengthProcess() << " - OS: removing process " <<  newProcess << endl;
		
		} else if(detToOutput == 1) {
		
			fout << processInfo.returnLengthProcess() << " - OS: removing process " << newProcess << endl;
		
		} else if(detToOutput == 2) {
			
			fout << processInfo.returnLengthProcess() << " - OS: removing process " << newProcess << endl;
		
		} else {
				return 0;
		}
		
		processInfo.currentProcesstype = 4;
	
	} else {
		return 0;
	}
	return 1;
}


bool processorHandler(PCB& processInfo, int processTime) {
	
	int pThreadCreateMain, pid = processInfo.getPID();
	pthread_t threadOfTimer;
	double length;	
	long pTime = (long) processTime;
	clock_t start;
	
	start = clock();

	length = clock()-start;
	length = length / (double) CLOCKS_PER_SEC;
	processInfo.replaceLengthProcess(length);
 // can't use if's, have to use switch	since if I used an if, it would catch it twice, fix this later, don't like switches
	
	switch (detToOutput) {
	case 0:
		cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": start processing action" << endl;
	break;
	case 1:
		fout << processInfo.returnLengthProcess() << " - Process " << newProcess <<  ": start processing action" << endl;
	break;
	case 2:
		cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": start processing action" << endl;
		fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": start processing action" << endl;
	break;
	default:
	return 0;
	}

	processInfo.currentProcesstype = 2;
	// first thread 
	pThreadCreateMain = pthread_create(&threadOfTimer, NULL, &timer, (void*)pTime);
	
	pthread_join(threadOfTimer, NULL);
	
	processInfo.currentProcesstype = 1;
	length = ((clock() - start) / (double) CLOCKS_PER_SEC) - length;
	processInfo.replaceLengthProcess(length);
 // can't use if's, have to use switch	since if I used an if, it would catch it twice, fix this later, don't like switches
	switch (detToOutput) {
	case 0:
		cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": end processing action" << endl;
	break;
	case 1:
		fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": end processing action" << endl;
	break;
	case 2:
		cout << processInfo.returnLengthProcess() << " - Process " << newProcess <<  ": end processing action" << endl;
		fout << processInfo.returnLengthProcess() << " - Process " << newProcess <<  ": end processing action" << endl;
	break;
	default:
		return 0;
	}
	return 1;
}

bool memHandler(PCB& processInfo, ConfigurationAPI configInfo, string descriptionInterpreter, int processTime) {
	clock_t start;
	double length;
	pthread_t threadOfTimer;
	long pTime = (long) processTime;
	int pThreadCreateMain, pid = processInfo.getPID();
	
	start = clock();
	
	if (descriptionInterpreter == "allocate") {
		length = clock()-start;
		length = length / (double) CLOCKS_PER_SEC;
		processInfo.replaceLengthProcess(length);
	 // can't use if's, have to use switch	since if I used an if, it would catch it twice, fix this later, don't like switches
	switch (detToOutput) {
		case 0:
			cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": allocating memory" << endl;
		break;
		case 1:
			fout << processInfo.returnLengthProcess() << " - Process " << pid << ": allocating memory" << endl;
		break;
		case 2:
			cout << processInfo.returnLengthProcess() << " - Process " << pid << ": allocating memory" << endl;
			fout << processInfo.returnLengthProcess() << " - Process " << pid << ": allocating memory" << endl;
		break;
		default:
			// success
			return 0;
		}
		unsigned int addr;
		processInfo.currentProcesstype = 2;
		pThreadCreateMain = pthread_create(&threadOfTimer, NULL, &timer, (void*)pTime);


		addr = allocMem(processInfo, configInfo);
		
		pthread_join(threadOfTimer, NULL);
		processInfo.currentProcesstype = 1;

	unsigned int tempAssign;
		length = clock()-start;
		length = length / (double) CLOCKS_PER_SEC;
		
		processInfo.replaceLengthProcess(length);
	switch (detToOutput) {
		case 0:
	tempAssign = generateMemoryAddress();
			cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": memory allocated at 0x" << hex << setw(8) << setfill('0')<< tempAssign << endl << dec;
		break;
		case 1:
			fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": memory allocated at 0x" << hex << setw(8) << setfill('0')<< tempAssign << endl << dec;
		break;
		case 2:
			cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": memory allocated at 0x" << hex << setw(8) << setfill('0')<< tempAssign << endl << dec;
			fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": memory allocated at 0x" << hex << setw(8) << setfill('0')<< tempAssign << endl << dec;
			break;
			default:
				return 0;
		}
	} else if (descriptionInterpreter == "block") {
	
		length = clock()-start;
		length = length / (double) CLOCKS_PER_SEC;
		processInfo.replaceLengthProcess(length);

		switch (detToOutput) {
		case 0:
			cout << processInfo.returnLengthProcess() << " - Process " << newProcess <<  ": start memory blocking" << endl;
		break;
		case 1:
			fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": start memory blocking" << endl;
		break;
		case 2: cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": start memory blocking" << endl;
			fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": start memory blocking" << endl;
		break;
		default:
		return 0;
		}
	
		processInfo.currentProcesstype = 2;
		
		pThreadCreateMain = pthread_create(&threadOfTimer, NULL, &timer, (void*)pTime);
		
		pthread_join(threadOfTimer, NULL);
	
		processInfo.currentProcesstype = 1;

		length = clock()-start;
		length = length / (double) CLOCKS_PER_SEC;
		
		processInfo.replaceLengthProcess(length);
	switch (detToOutput) {
		case 0:
			cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": end memory blocking" << endl;
		break;
		case 1:
			fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": end memory blocking" << endl;
		break;
		case 2:
			cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": end memory blocking" << endl;
			fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": end memory blocking" << endl;
		break;
		default:
		return 0;
		}
	} else {
		return 0;
	}
}

bool finHandler(PCB& processInfo, string descriptionInterpreter, int processTime) {
	pthread_t inputThread;
	clock_t start;
	int pThreadCreateMain, pid = processInfo.getPID();
	long pTime = (long) processTime;
	double length;

	start = clock();
	
	length = clock()-start;
	length = length / (double) CLOCKS_PER_SEC;
	processInfo.replaceLengthProcess(length);
	if (descriptionInterpreter != "hard drive") {
	switch (detToOutput) {
	case 0:
		cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInterpreter << " input" << endl;
		break;
	case 1:
		fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInterpreter << " input" << endl;
		break;
	case 2:	cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInterpreter << " input" << endl;
		fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInterpreter << " input" << endl;
		break;
		default:
		return 0;
	}
// mainnew
} else {
	int hardDriveInfoMatrix = processInfo.returnHardDriveAmtUtil() % processInfo.returnHardDriveAmtPCB();
		switch(detToOutput) {
		case 0:
				cout << processInfo.returnLengthProcess() << " - Process " << newProcess <<
				": start " << descriptionInterpreter << " input on HDD " << hardDriveInfoMatrix << endl;
			break;
		case 1:
				fout << processInfo.returnLengthProcess() << " - Process " << newProcess <<
				": start " << descriptionInterpreter << " input on HDD " << hardDriveInfoMatrix << endl;
			break;
		case 2:
				cout << processInfo.returnLengthProcess() << " - Process " << newProcess <<
				": start " << descriptionInterpreter << " input on HDD " << hardDriveInfoMatrix << endl;
				fout << processInfo.returnLengthProcess() << " - Process " << newProcess <<
				": start " << descriptionInterpreter << " input on HDD " << hardDriveInfoMatrix << endl;
			break;
		default:
			cout << "err: config file missing new info";
			return 0;
		}
		processInfo.addHardDriveAmt();
}

	if(descriptionInterpreter == "hard drive") {
		
		processInfo.currentProcesstype = 2;
		pThreadCreateMain = pthread_create(&inputThread, NULL, &hardDriveInputHandler, (void*)pTime);
	
	} else if (descriptionInterpreter == "keyboard") {

		processInfo.currentProcesstype = 2;
		pThreadCreateMain = pthread_create(&inputThread, NULL, &keyboardHandler, (void*)pTime);
	
	} else if (descriptionInterpreter == "scanner") {
		
		processInfo.currentProcesstype = 2;
		pThreadCreateMain = pthread_create(&inputThread, NULL, &scannerHandler, (void*)pTime);
	
	} else {
		return 0;
	}
	processInfo.currentProcesstype = 3;
	pthread_join(inputThread, NULL);

	processInfo.currentProcesstype = 1;

	length = clock()-start;
	length = length / (double) CLOCKS_PER_SEC;
	processInfo.replaceLengthProcess(length);

	switch (detToOutput) {
	case 0:
		cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": end " << descriptionInterpreter << " output" << endl;
	break;
	case 1:
		fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": end " << descriptionInterpreter << " output" << endl;
	break;
	case 2: cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": end " << descriptionInterpreter << " output" << endl;
		fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": end " << descriptionInterpreter << " output" << endl;
	break;
	default:
		return 0;
	}
return 1;
}



int allocMem(PCB& processInfo, ConfigurationAPI configInfo) {

	int indexOfAddress, assignAddrNew;
	if(processInfo.returnBlockAmt() == 0) {
		indexOfAddress = 0;
	} else {
		indexOfAddress = processInfo.returnPrevMemAdd();
	}
	
	assignAddrNew = (indexOfAddress + configInfo.returnMemBlockAmt()) % configInfo.returnSysMemory();
	processInfo.assignPrevAddr(assignAddrNew);
	processInfo.addBlockAmt();
	
	if (indexOfAddress < 0 || indexOfAddress > configInfo.returnSysMemory()) {
		return -1;
	}
	
	else return indexOfAddress;
}

// create address
unsigned int generateMemoryAddress() {
	unsigned int address;
	srand(time(NULL));
	address = rand() % 1000;
	return address;
}


// timer
void* timer(void* milliseconds) {
	long m = (long) milliseconds;
	clock_t timerEnd = clock() + m * CLOCKS_PER_SEC/1000;
	while(clock() < timerEnd) {
	};
}

// output handler...
bool outputHandler(PCB& processInfo, string descriptionInterpreter, int processTime) {

	
	double length;
	long pTime;
	int pThreadCreateMain, pid = processInfo.getPID();
	pthread_t outputThread;
	clock_t start;
	
	pTime=(long) processTime;
	start = clock();
	

	length = clock()-start;
	length = length / (double) CLOCKS_PER_SEC;
	
	processInfo.replaceLengthProcess(length);


if(descriptionInterpreter != "hard drive" && descriptionInterpreter != "projector") {
	
	switch (detToOutput) {
	case 0:
		cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInterpreter << " output" << endl;
	break;
	case 1:
		fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInterpreter << " output" << endl;
	break;
	case 2: cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInterpreter << " output" << endl;
		fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": start " << descriptionInterpreter << " output" << endl;
	break;
	default:
		return 0;
	}
} else if(descriptionInterpreter == "hard drive") {
		
	int hardDriveInfoMatrix = processInfo.returnHardDriveAmtUtil() % processInfo.returnHardDriveAmtPCB();
		switch (detToOutput) {
		
			case 0:
				cout << processInfo.returnLengthProcess() << " - Process " << newProcess <<
				": start " << descriptionInterpreter << " output on HDD " << hardDriveInfoMatrix << endl;
			break;
			case 1:
				fout << processInfo.returnLengthProcess() << " - Process " << newProcess <<
				": start " << descriptionInterpreter << " output on HDD " << hardDriveInfoMatrix << endl;
			break;
			case 2:
				cout << processInfo.returnLengthProcess() << " - Process " << newProcess <<
				": start " << descriptionInterpreter << " output on HDD " << hardDriveInfoMatrix << endl;
				fout << processInfo.returnLengthProcess() << " - Process " << newProcess <<
				": start " << descriptionInterpreter << " output on HDD " << hardDriveInfoMatrix << endl;
			break;
			default:
				cout << "ERR: bad output type" 
					 << endl;
				return 0;
		}
		
	processInfo.addHardDriveAmt();

	} else if (descriptionInterpreter == "projector") {
		int projIndex = processInfo.getProjectorsUsed() % processInfo.returnProjAmtUtil();
		switch (detToOutput) {
		
			case 0:
				cout << processInfo.returnLengthProcess() << " - Process " << newProcess <<
				": start " << descriptionInterpreter << " output on PROJ " << projIndex << endl;
			break;
			case 1:
				fout << processInfo.returnLengthProcess() << " - Process " << newProcess <<
				": start " << descriptionInterpreter << " output on PROJ " << projIndex << endl;
			break;
			case 2:
				cout << processInfo.returnLengthProcess() << " - Process " << newProcess <<
				": start " << descriptionInterpreter << " output on PROJ " << projIndex << endl;
				fout << processInfo.returnLengthProcess() << " - Process " << newProcess <<
				": start " << descriptionInterpreter << " output on PROJ " << projIndex << endl;
			break;
			default:
				cout << "ERR: bad log type" 
					 << endl;
				return 0;
		}
		processInfo.addProjAmt();
	}  
	if (descriptionInterpreter == "hard drive") {
		processInfo.currentProcesstype = 2;
		pThreadCreateMain = pthread_create(&outputThread, NULL, &hardDriveOutputHandler, (void*)pTime);
		
		} else if  (descriptionInterpreter == "monitor"){
		processInfo.currentProcesstype = 2;
		pThreadCreateMain = pthread_create(&outputThread, NULL, &monitorHandler, (void*)pTime);

	} else if (descriptionInterpreter == "projector") { 
	
	processInfo.currentProcesstype = 2;
		pThreadCreateMain = pthread_create(&outputThread, NULL, &projectorHandler, (void*)pTime);
	
	}

	processInfo.currentProcesstype = 3;
	
	pthread_join(outputThread, NULL);

	processInfo.currentProcesstype = 1;
	length = clock()-start;
	length = length / (double) CLOCKS_PER_SEC;
	processInfo.replaceLengthProcess(length);
	
	switch (detToOutput) {
	case 0:
		cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": end " << descriptionInterpreter << " output" << endl;
		fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": end " << descriptionInterpreter << " output" << endl;
	break;
	case 1:
		fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": end " << descriptionInterpreter << " output" << endl;
	break;
	case 2:
		cout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": end " << descriptionInterpreter << " output" << endl;
		fout << processInfo.returnLengthProcess() << " - Process " << newProcess << ": end " << descriptionInterpreter << " output" << endl;
	break;
	default:
	return 0;
	}
	return 1;
}

// join on process wait
void* hardDriveInputHandler(void* hdTime) {
	pthread_t threadOfTimer;
	int pThreadCreateMain;

	pThreadCreateMain = pthread_create(&threadOfTimer, NULL, &timer, (void*)hdTime);
	
	pthread_mutex_lock(&hardDriveMx);
	
	pthread_mutex_unlock(&hardDriveMx);
	
	pthread_join(threadOfTimer, NULL);

}

// join on process wait
void* monitorHandler(void* monitorTimeAmt) {
	
	pthread_t threadOfTimer;
	
	int pThreadCreateMain;

	pThreadCreateMain = pthread_create(&threadOfTimer, NULL, &timer, (void*)monitorTimeAmt);
	
	pthread_mutex_lock(&mutexMonitor);
	
	pthread_mutex_unlock(&mutexMonitor);
	
	pthread_join(threadOfTimer, NULL);
}

// join on process wait
void* scannerHandler(void* sTime) {
	
	pthread_t threadOfTimer;
	int pThreadCreateMain;

	pThreadCreateMain = pthread_create(&threadOfTimer, NULL, &timer, (void*)sTime);
	
	pthread_mutex_lock(&mutexScanner);
	
	pthread_mutex_unlock(&mutexScanner);
	
	pthread_join(threadOfTimer, NULL);

}

// join on process wait
void* hardDriveOutputHandler(void* hdTime) {
	
	pthread_t threadOfTimer;
	int pThreadCreateMain;

	pThreadCreateMain = pthread_create(&threadOfTimer, NULL, &timer, (void*)hdTime);

	pthread_mutex_lock(&hardDriveMx);	
	pthread_mutex_unlock(&hardDriveMx);
	
	pthread_join(threadOfTimer, NULL);
}

//join on process wait
void* keyboardHandler(void* kTime) {
	
	pthread_t threadOfTimer;
	int pThreadCreateMain;

	pThreadCreateMain = pthread_create(&threadOfTimer, NULL, &timer, (void*)kTime);

	pthread_mutex_lock(&keyboardMx);
	pthread_mutex_unlock(&keyboardMx);
	pthread_join(threadOfTimer, NULL);

}
 
// join on process wait 
void* projectorHandler(void* pTime) {
	pthread_t threadOfTimer;
	int pThreadCreateMain;

	pThreadCreateMain = pthread_create(&threadOfTimer, NULL, &timer, (void*)pTime);
	
	pthread_mutex_lock(&projectorMx);
	
	pthread_mutex_unlock(&projectorMx);
	pthread_join(threadOfTimer, NULL);
}
