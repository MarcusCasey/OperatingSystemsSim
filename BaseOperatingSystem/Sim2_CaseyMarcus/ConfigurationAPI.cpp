/*
Marcus Casey
CS 446
Sim 02
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

// Return descriptionInputriptor type
float ConfigurationAPI::returnVersion() {
	return configVersion;
}

// load
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
	// assign start of description (a) etc. for processing
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
	}
	else if (descriptionInput == 'O') {
		if(metaDataWord == "hard drive") {
			return timeHD;
		}else if(metaDataWord == "monitor") {
			return timeMonitor;
		}else if(metaDataWord == "projector") {
			return timeProjector;
		} else {
			cout << "ERR: in hard-drive, monitor, or projector" << endl;
			// failure			
			return -1;
        }
}
	 else if (descriptionInput == 'M') {
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

// Search in config matrix for indexof
void ConfigurationAPI::loadConfigData(ifstream& fin) {
	// holder vars	
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
	// comparisons for time
	string valuePrintTimeOutput = "display time {msec}:";
	string valuePrintHDOutput = "drive cycle time {msec}:";
	string valuePrintRestOutput = "cycle time {msec}:";
	int j = 0;
	while (j < 7) {
		fin >> descriptionInputStart;
		configurationMatrixInput = detConfigmatrix(descriptionInputStart);
		fin.get(heldC);
		getline(fin, descriptionInputStart);

	switch (configurationMatrixInput) {
	case 1:	if (loadConfigurationTime(descriptionInputStart, valuePrintTimeOutput, j, holdTotalTime)) {
			timeMonitor = holdTotalTime;
			} else return;
		break;
	case 2: if (loadConfigurationTime(descriptionInputStart, valuePrintRestOutput, j, holdTotalTime)) {
				timeProcessor = holdTotalTime;
			} else return;
		break;
	case 3: if (loadConfigurationTime(descriptionInputStart, valuePrintRestOutput, j, holdTotalTime)) {
				timeScanner = holdTotalTime;
			} else return;
		break;
	case 4: if (loadConfigurationTime(descriptionInputStart, valuePrintHDOutput, j, holdTotalTime)) {
				timeHD = holdTotalTime;
			} else return;
		break;
	case 5: if (loadConfigurationTime(descriptionInputStart, valuePrintRestOutput, j, holdTotalTime)) {
				timeKeyboard = holdTotalTime;
			} else return;
		break;		
	case 6: if (loadConfigurationTime(descriptionInputStart, valuePrintRestOutput, j, holdTotalTime)) {
				timeMemory = holdTotalTime;
			} else return;
		break;
	case 7:	if (loadConfigurationTime(descriptionInputStart, valuePrintRestOutput, j, holdTotalTime)) {
				timeProjector = holdTotalTime;
			} else return;
		break;
		default:
	cout << "Error Loading File: cycles";
			return ;
		}
	j++;
	}
	// clear holder for reinput
	descriptionInputStart.clear();
	fin >> descriptionInputStart;
	fin >> descriptionInputStart;
	// assuming memory is K...
	char memoryToTransform = 'k';
	fin >> descriptionInputStart;
	if (descriptionInputStart == "{kbytes}:") {
		memoryToTransform = 'k';
	}
	else if (descriptionInputStart == "{Mbytes}:") {
		memoryToTransform = 'M';
	}
	else if (descriptionInputStart == "{Gbytes}:") {
		memoryToTransform = 'G';
	} else {
		cout << "ERROR: typo on line 11" << endl;
		return;
	}
	descriptionInputStart.clear();
	int sysMemoryTemp;
	fin >> descriptionInputStart;
	sysMemoryTemp = atoi(descriptionInputStart.c_str());

	descriptionInputStart.clear();
	sysMemory = transformMemoryType(sysMemoryTemp, memoryToTransform);
	getline(fin, marker);
	getline(fin, marker);
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
// memory for runningProgram
int ConfigurationAPI::returnSysMemory() {
	return sysMemory;
}

// assigntoSysMemory
void ConfigurationAPI::assignSysMemory(int assignToSysMemory) {
	sysMemory = assignToSysMemory;
}

// Convert memory
int ConfigurationAPI::transformMemoryType(int memoryInput, char memoryInputType) {
	if (memoryInputType == 'M') {
		return memoryInput * 1000;
	} else if (memoryInputType == 'G') {
		return memoryInput * 1000 * 1000;
	} else { return memoryInput;
	}
}

// Search in config matrix for indexof move this 
int ConfigurationAPI::detConfigmatrix(string configurationDescriptionIndex) {
	int j = 0;
	// loop to find correct descriptionIndex	
	while (j < 7) {
	if (configurationMatrix[j] == configurationDescriptionIndex) {
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
