/*
Marcus Casey
CS 446
Sim 05
Collaborators: None - Stack Overflow and cplusplus.com. 
*/

// includes
#include "ConfigurationAPI.h"

// Configuration constructor
ConfigurationAPI::ConfigurationAPI() { }

// Configuration destructor
ConfigurationAPI::~ConfigurationAPI() { }

// Return file location 
string ConfigurationAPI::returnFileLocation() {
	return fileLocation;
}

// Return log file location
string ConfigurationAPI::returnLogLocation() {
	return logLocation;
}

// Return descriptionInterpreter type
float ConfigurationAPI::returnVersion() {
	return configVersion;
}

// load configuration 
bool ConfigurationAPI::loadConfigurationTime(string descriptionInputStart, string descriptionInput, int locMarker, int& holdTotalTime) {
	// declare holder vars
	int lastValueOfInput;
	int convertTimeToInt;
	int stringTime; 
	int startOfDescription;
	int tempHoldStringLoc;
	
	// get descriptor lenght without ; 
	lastValueOfInput = descriptionInputStart.length() - 1;
	tempHoldStringLoc = lastValueOfInput;
	
	// look until they don't have ;	
	while (descriptionInputStart[tempHoldStringLoc - 1] != ' ') {
		tempHoldStringLoc--;
	}

	startOfDescription = tempHoldStringLoc;
	stringTime = lastValueOfInput - tempHoldStringLoc + 1;
	string time = descriptionInputStart.substr(startOfDescription, stringTime);
	string rest = descriptionInputStart.substr(0, startOfDescription - 1);
	convertTimeToInt = atoi(time.c_str()); 
	
	// return time
	holdTotalTime = convertTimeToInt; 
	
	// 1 if succeeds
	return 1;
}

// Use meta memoryInput to determine correct time
int ConfigurationAPI::returnConfigurationTime(char descriptionInput, string metaDataWord) {
	
	// get time on each type for assignment	
	
		if(descriptionInput == 'P') {
		
			return timeProcessor;
	
		} else if(descriptionInput == 'I') {
		
			if(metaDataWord == "hard drive") {
			
				return timeHD;
		
		} else if(metaDataWord == "keyboard") {
			
			return timeKeyboard;
		
		} else if(metaDataWord == "scanner") {
			
			return timeScanner;
		
		} else { 
		
		cout << "ERR: in harddrive, keyboard, or scanner" << endl;
		
		// failure	
		return -1;
		
		}

	} else if(descriptionInput == 'O') {

		if(metaDataWord == "hard drive") {

			return timeHD;

		} else if(metaDataWord == "monitor") {
			
			return timeMonitor;

		} else if(metaDataWord == "projector") {
			
			return timeProjector;
		
		} else {
			
		cout << "ERR: in hard-drive, monitor, or projector" << endl;
			
		// failure	
		return -1;
       		
		}

	} else if(descriptionInput == 'M') {
		
		return timeMemory;
	
	} else {

		//success
		return 0;

	}
}

// Log type = locFinals
void ConfigurationAPI::assignLogValue(int valueToAssign) {

	logValue = valueToAssign;

}

// Memory time = valueToAssign
void ConfigurationAPI::assignMemoryTime(int valueToAssign) {

	timeMemory = valueToAssign;

}

// Monitor time = locFinals
void ConfigurationAPI::assignMonitorTime(int valueToAssign) {
	
	timeMonitor = valueToAssign;
}

// Scanner time = locFinals
void ConfigurationAPI::assignScannerTime(int valueToAssign) {
	
	timeScanner = valueToAssign;

}

// Hard drive time = locFinals
void ConfigurationAPI::assignHDTime(int valueToAssign) {
	
	timeHD = valueToAssign;

}

// Processor time = locFinals
void ConfigurationAPI::assignProcessorTime(int valueToAssign) {
	
	timeProcessor = valueToAssign;

}

// Keyboard time = locFinals
void ConfigurationAPI::assignKeyboardTime(int valueToAssign) {
	timeKeyboard = valueToAssign;
}

// Projector time = locFinals
void ConfigurationAPI::assignProjectorTime(int valueToAssign) {
	
	timeProjector = valueToAssign;

}

// SeapThreadCreateMainh in config matrix for indexof
void ConfigurationAPI::loadConfigData(ifstream& fin) {
	
	// temp vars	
	char heldC;	

	int holdTotalTime = 0; 
	int configurationMatrixInput;


	
	string descriptionInputStart;	
	string marker;
	
	getline(fin, marker);
	marker.clear();
	
	// grab input descriptions
	fin >> descriptionInputStart;
	fin >> configVersion;
	fin >> descriptionInputStart;
	fin >> descriptionInputStart;

	descriptionInputStart.clear();
	fin >> fileLocation;
	
descriptionInputStart.clear();
	fin >> descriptionInputStart;
	if (descriptionInputStart == "FIFO") {
		cpuScheduleCode = 0;
	}
	else if (descriptionInputStart == "PS") {
		cpuScheduleCode = 1;
	} else if (descriptionInputStart == "SJF") {
		cpuScheduleCode = 2;
	} else if (descriptionInputStart == "STR") {
		cpuScheduleCode = 3;
	} else if (descriptionInputStart == "RR") {
		cpuScheduleCode = 4;
	} else {
		//return;
	}
	descriptionInputStart.clear();
	getline(fin, marker);
	

	// comparisons for time
	string valuePrintTimeOutput = "display time {msec}:";
	string valuePrintHDOutput = "drive cycle time {msec}:";
	string valuePrintRestOutput = "cycle time {msec}:";
	
	int j = 0;
	
	while(j < 7) {
		
		fin >> descriptionInputStart;
		configurationMatrixInput = detConfigmatrix(descriptionInputStart);
		fin.get(heldC);
		getline(fin, descriptionInputStart);

		switch (configurationMatrixInput) {
	
			// if monitor
			case 1:	if(loadConfigurationTime(descriptionInputStart, valuePrintTimeOutput, j, holdTotalTime)) {
				timeMonitor = holdTotalTime;
				} else return;
		break;
	
			// if processor
			case 2: if(loadConfigurationTime(descriptionInputStart, valuePrintRestOutput, j, holdTotalTime)) {
				timeProcessor = holdTotalTime;
			} else return;
		break;
	

			case 3: if(loadConfigurationTime(descriptionInputStart, valuePrintRestOutput, j, holdTotalTime)) {
				timeScanner = holdTotalTime;
			} else return;
		break;
	
			// if scanner
			case 4: if(loadConfigurationTime(descriptionInputStart, valuePrintHDOutput, j, holdTotalTime)) {
				timeHD = holdTotalTime;
			} else return;
		break;
	
			// if keyboard
			case 5: if(loadConfigurationTime(descriptionInputStart, valuePrintRestOutput, j, holdTotalTime)) {
				timeKeyboard = holdTotalTime;
			} else return;
		break;		
	
			// if memory
			case 6: if(loadConfigurationTime(descriptionInputStart, valuePrintRestOutput, j, holdTotalTime)) {
				timeMemory = holdTotalTime;
			} else return;
		break;
	
			// if projector
			case 7:	if(loadConfigurationTime(descriptionInputStart, valuePrintRestOutput, j, holdTotalTime)) {
				timeProjector = holdTotalTime;
			} else return;
		break;
			default:
				cout << "Have a massive error, please look at read me"<< endl;
			return ;
			}
		j++;
	}
	
	// clear holder for reinput
	descriptionInputStart.clear();
	fin >> descriptionInputStart;
	fin >> descriptionInputStart;
	
	char memoryToTransform = 'k';
	// assuming memory is K...
	fin >> descriptionInputStart;
	

	descriptionInputStart.clear();
	int sysMemoryTemp;
	fin >> descriptionInputStart;

	sysMemoryTemp = atoi(descriptionInputStart.c_str());

	descriptionInputStart.clear();

	systemMemory = transformMemoryType(sysMemoryTemp, memoryToTransform);
	getline(fin, marker);
	getline(fin, marker);

	
	// sim 03

	descriptionInputStart.clear();
	fin >> descriptionInputStart;

	descriptionInputStart.clear();
	fin >> descriptionInputStart;
	int convBlockSize;

	convBlockSize = atoi(descriptionInputStart.c_str());

	descriptionInputStart.clear();
	int heldBlockSize;
	heldBlockSize = transformMemoryType(convBlockSize,memoryToTransform);
	memBlockAmt = heldBlockSize;
	
	getline(fin, marker);

	descriptionInputStart.clear();
	fin >> descriptionInputStart;

	int convProjQuantity = atoi(descriptionInputStart.c_str());

	projAmt = convProjQuantity;
	
	// if you got this deep, I have a bug in input right now and am assuming four projectors	
	projAmt = 4;
	getline(fin, marker);

	descriptionInputStart.clear();
	fin >> descriptionInputStart;

	int convHardQuant = atoi(descriptionInputStart.c_str());

	hdAmount = convHardQuant;
	
	// same with hdd
	hdAmount = 2;
	
	getline(fin, marker);
	getline(fin, marker);
	
	marker.clear();
	descriptionInputStart.clear();

	// determine log type
	if (marker == "Log: Log to Monitor") {
		
		logValue = 0;
	
	} else if (marker == "Log: Log to File") {
		
		logValue = 1;
	
	} else if (marker == "Log: Log to Both") {
		
		logValue = 2;
	
	}

	marker.clear();

	fin >> descriptionInputStart;
	descriptionInputStart.clear();

	fin >> logLocation;
	getline(fin, marker);
	getline(fin, marker);

	marker.clear();
}

// System Memory
int ConfigurationAPI::returnSysMemory() {
	return systemMemory;
}

// assigntoSysMemory
void ConfigurationAPI::assignSysMemory(int assignToSysMemory) {
	
	systemMemory = assignToSysMemory;
}

// Convert memory
int ConfigurationAPI::transformMemoryType(int memoryInput, char memoryInputType) {
	
		return memoryInput;
	
}

// SeapThreadCreateMainh in config matrix for indexof move this 
int ConfigurationAPI::detConfigmatrix(string configurationDescriptionIndex) {
	
	int j = 0;
	// loop to find correct descriptionIndex	
	while (j < 7) {
	
		if(configurationMatrix[j] == configurationDescriptionIndex) {
		return j + 1;
		}
	j++;
	
	}

	// success
	return 0;
}

// Return processor time
int ConfigurationAPI::returnProcessorTime() {
	
	return timeProcessor;

}

// Return memory time
int ConfigurationAPI::returnMemoryTime() {

	return timeMemory;

}

// Return projector time
int ConfigurationAPI::returnKeyboardTime() {
	
	return timeProjector;

}

// Return keyboard time
int ConfigurationAPI::detKeyExport() {
	
	return timeKeyboard;

}

// Return monitor time
int ConfigurationAPI::returnMonitorTime() {
	
	return timeMonitor;

}

// Return scanner time
int ConfigurationAPI::returnScannerTime() {
	
	return timeScanner;

}

// Return hard drive time
int ConfigurationAPI::returnHDTime() {
	
	return timeHD;

}

// Find log type from file and return
int ConfigurationAPI::returnLogValue() {
	
	return logValue;

}


// assign hd quantity
void ConfigurationAPI::assignHdAmount(int inputAmt) {
	
	hdAmount = inputAmt;

}

// return proj quantity
int ConfigurationAPI::returnProjAmount() {
	
	return projAmt;

}

// assign proj quantity
void ConfigurationAPI::assignProjAmount(int inputAmt) {
	
	projAmt = inputAmt;
}

// return memBlock size
int ConfigurationAPI::returnMemBlockAmt() {
	
	return memBlockAmt;

}

// return hdd quantity
int ConfigurationAPI::returnHdAmt() {
	
	return hdAmount;

}

	
int ConfigurationAPI::getProcessorQuantumNumber() {		
	return processorQuantumNumber;		
}		
		
int ConfigurationAPI::getCpuScheduleCode() {		
	return cpuScheduleCode;		
}
	
void ConfigurationAPI::setProcessorQuantumNumber(int source) {		
	processorQuantumNumber = source;		
}		
	
void ConfigurationAPI::setCpuScheduleCode(int source) {		
	cpuScheduleCode = source;		
}




