/*
Marcus Casey
CS 446
Sim 02
Collaborators: None - Stack Overflow and cplusplus.com. 
*/

#include "MetaDataAPI.h"

// MetaDeque constructor
MetaDataAPI::MetaDataAPI() {
}

// Parameterized constructor for MetaDeque
MetaDataAPI::MetaDataAPI(char metaLocationMain, string descriptionInputLocationMain, int cycleLocationMain) {
	descriptionInput = metaLocationMain;
	metaDataWord = descriptionInputLocationMain;
	amtCyclesTotal = cycleLocationMain;
}

// MetaDeque destructor
MetaDataAPI::~MetaDataAPI() {
}

// Return metaDataWord
string MetaDataAPI::returnDescription() {
	return metaDataWord;
}

// Length of grabbing config memoryInput
void MetaDataAPI::detAmtTime(int returnTimeElapsedTotalLocationM) {
	amtTotalTimeRan = returnTimeElapsedTotalLocationM;
}

// Amount of cycles
void MetaDataAPI::detNumCycle(int cycleLocationMain) {
	amtCyclesTotal = cycleLocationMain;
}

// assign metaType descriptionInputriptor to descriptionInputLocationMain 
void MetaDataAPI::detDesc(string descriptionInputLocationMain) {
	metaDataWord = descriptionInputLocationMain;
}

// Desc Location
void MetaDataAPI::returnCommand(char metaLocationMain) {
	descriptionInput = metaLocationMain;
}

// Time to compute descriptionInput	
void MetaDataAPI::assignTimeElapsed(ConfigurationAPI configurationData) {
	int amtCycleTimeTotal;
	
	amtCycleTimeTotal = configurationData.returnConfigurationTime(descriptionInput, metaDataWord);
	
	amtTotalTimeRan = amtCycleTimeTotal * amtCyclesTotal;
}

// Return the meta descriptionInputriptor  
char MetaDataAPI::returnCommand() {
	return descriptionInput;
}

// Amount of execute time
int MetaDataAPI::returnTimeElapsed() {
	return amtTotalTimeRan;
}

// Look from descriptionInputDatabase, return index
int MetaDataAPI::returnCommandIndex(char metaLocationMain) {
	int j = 0;	
	while (j<6) {
		if (metaLocationMain == descriptionInputDatabase[j]) {
			return j + 1;
		}
	j++;
	}
	return 0;
}

// Return total cycles amount
int MetaDataAPI::returnCycleElapsed() {
	return amtCyclesTotal;
}

// Look from descriptionInputDatabase, return a # based on index
int MetaDataAPI::returnDescriptionIndex(int descriptionInputMetaLocationMain, string descriptionInputLocationMain) {

	// load through meta data descriptions from matrix
	switch (descriptionInputMetaLocationMain) {
		case 1:
			for (int i = 0; i < 2; i++) {
				if (descriptionInputLocationMain == sDesc[i]) {
					return i + 1;
				}
			}
			return 0;
		break;
		case 2:
			for (int i = 0; i < 2; i++) {
				if (descriptionInputLocationMain == aDesc[i]) {
					return i + 1;
				}
			}
			return 0;
		break;
		case 3:
			if (descriptionInputLocationMain == pDesc) {
				return 1;
			}
			return 0;
		break;
		case 4:
			for (int i = 0; i < 3; i++) {
				if (descriptionInputLocationMain == iDesc[i]) {
					return i + 1;
				}
			}
			return 0;
		break;
		case 5:
			for (int i = 0; i < 3; i++) {
				if (descriptionInputLocationMain == oDesc[i]) {
					return i + 1;
				}
			}
			return 0;
		break;
		case 6:
			for (int i = 0; i < 2; i++) {
				if (descriptionInputLocationMain == mDesc[i]) {
					return i + 1;
				}
			}
			return 0;
		break;
		default: 
			cout << "ERR: ocurred when getting metaDataWord index" << endl;
			return 0;
	}
}

// Check for incorrect entries in memoryInput and meta memoryInput and invalid cycles.
bool MetaDataAPI::readThroughMetaData(string command) {

	string cycleCurrentValue;
	string storedDescriptor;
	string aBegin;
	string aDescFinishEnd;
	string newProcess;	
	string endProcess;

	int currentAmountCycles;
	int descriptionInputLocationIndexMainL;
	int descriptionInputMetaLocationMain;
	int descriptionInputAmountTotalL;
	int startOfDescription;
	int totalAmountOfCycles;
	
	descriptionInputMetaLocationMain = returnCommandIndex(command[0]);

	descriptionInput = descriptionInputDatabase[descriptionInputMetaLocationMain - 1];
	
	startOfDescription = 2;

	int i = 2;

	while (command[i] != '}') {
		i++;
	}

	descriptionInputAmountTotalL = i - 2;
	
	aBegin = command;
	aDescFinishEnd = command;
	
	//cout  << "A begin =" << aBegin << endl << "A finish =" << aDescFinishEnd << endl;
//	if(aBegin == "A{begin}0;") {
	newProcess = aBegin;
//cout << "@@@@@@@@@@@new process time!@@@@@@@@2" << newProcess;
//	}
//if(aDescFinishEnd == "A{finish}0;") {
	endProcess = aDescFinishEnd;
//cout << "@@@@@@@@@@@end process time!@@@@@@@@2" << newProcess;
//	}

	storedDescriptor = command.substr(startOfDescription, descriptionInputAmountTotalL);
	
	descriptionInputLocationIndexMainL = returnDescriptionIndex(descriptionInputMetaLocationMain, storedDescriptor);

		if (descriptionInputMetaLocationMain == 1) {
			metaDataWord = sDesc[descriptionInputLocationIndexMainL - 1];
		} else if (descriptionInputMetaLocationMain == 2) {
			metaDataWord = aDesc[descriptionInputLocationIndexMainL - 1];
		} else if (descriptionInputMetaLocationMain == 3) {
			metaDataWord = pDesc;
		} else if (descriptionInputMetaLocationMain == 4) {
			metaDataWord = iDesc[descriptionInputLocationIndexMainL - 1];
		} else if (descriptionInputMetaLocationMain == 5) {
			metaDataWord = oDesc[descriptionInputLocationIndexMainL - 1];
		} else if (descriptionInputMetaLocationMain == 6) {
			metaDataWord = mDesc[descriptionInputLocationIndexMainL - 1];
		} else {
			cout << "metaData not found or missing" << endl;
			return 0;
	}
	startOfDescription = descriptionInputAmountTotalL + 3;

	i = startOfDescription;

	while (command[i] != ';' && command[i] != '.') {
		i++;
	}

	currentAmountCycles = i - startOfDescription;
	cycleCurrentValue = command.substr(startOfDescription, currentAmountCycles);
        totalAmountOfCycles = atoi(cycleCurrentValue.c_str());
	amtCyclesTotal = totalAmountOfCycles;
	// success
	return 1;
}
