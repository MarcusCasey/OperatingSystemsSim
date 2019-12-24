/*
Marcus Casey
CS 446
Sim 02
Collaborators: None - Stack Overflow and cplusplus.com. 
*/



#include "HarnessAPI.h"

using namespace std;

// output specified template from project assignment to monitor
void HarnessAPI::returnOutputMonitor(ConfigurationAPI configurationData, deque<MetaDataAPI> MetaDataAPI) {
	cout << "Configuration File Data" << endl;
	cout << "Monitor = " << configurationData.returnMonitorTime() << " ms/cycle" << endl;
	cout << "Processor = " << configurationData.returnProcessorTime() << " ms/cycle" << endl;
	cout << "Scanner = " << configurationData.returnScannerTime() << " ms/cycle" << endl;
	cout << "Hard Drive = " << configurationData.returnHDTime() << " ms/cycle" << endl;
	cout << "Keyboard = " << configurationData.detKeyExport() << " ms/cycle" << endl;
	cout << "Memory = " << configurationData.returnMemoryTime() << " ms/cycle" << endl;
	cout << "Projector = " << configurationData.returnKeyboardTime() << " ms/cycle" << endl;
	cout << "Logged to: ";
	if (configurationData.returnLogValue() == 0) {
		cout << "monitor" << endl;
	} else if (configurationData.returnLogValue() == 2) {
		cout << "monitor and " << configurationData.returnLogLocation() << endl;
	} else {
		return;
	}
	cout << endl;
	cout << "Meta-Data Metrics" << endl;
	for (int i = 0; i < MetaDataAPI.size(); i++) {
		if (MetaDataAPI[i].returnCommand() != 'A' && MetaDataAPI[i].returnCommand() != 'S') {
			cout << MetaDataAPI[i].returnCommand();
			cout << '{';
			cout << MetaDataAPI[i].returnDescription();
			cout << '}';
			cout << MetaDataAPI[i].returnCycleElapsed();
			cout << " - ";
			cout << MetaDataAPI[i].returnTimeElapsed();
			cout << " ms" << endl;
		}
	}
}

// output for file and also potentially monitor
void HarnessAPI::fileLine(ConfigurationAPI configurationData, deque<MetaDataAPI> MetaDataAPI) {
	
	ofstream fout;
	
	fout.open(configurationData.returnLogLocation());
	
	fout << "Configuration File Data" << endl;
	fout << "Monitor = " << configurationData.returnMonitorTime() << " ms/cycle" << endl;
	fout << "Processor = " << configurationData.returnProcessorTime() << " ms/cycle" << endl;
	fout << "Scanner = " << configurationData.returnScannerTime() << " ms/cycle" << endl;
	fout << "Hard Drive = " << configurationData.returnHDTime() << " ms/cycle" << endl;
	fout << "Keyboard = " << configurationData.detKeyExport() << " ms/cycle" << endl;
	fout << "Memory = " << configurationData.returnMemoryTime() << " ms/cycle" << endl;
	fout << "Projector = " << configurationData.returnKeyboardTime() << " ms/cycle" << endl;
	fout << "Logged to: ";
	
	if (configurationData.returnLogValue() == 1) {
		fout << configurationData.returnLogLocation() << endl;
	}
	else if (configurationData.returnLogValue() == 2) {
		fout << "monitor and " << configurationData.returnLogLocation() << endl;
	} else {
		return;
	}
	fout << endl;
	fout << "Meta-Data Metrics" << endl;
	int j =0;	
	while(j < MetaDataAPI.size()) {
	if (MetaDataAPI[j].returnCommand() != 'S' && MetaDataAPI[j].returnCommand() != 'A') {
		fout << MetaDataAPI[j].returnCommand();
		fout << '{';
		fout << MetaDataAPI[j].returnDescription();
		fout << '}';
		fout << MetaDataAPI[j].returnCycleElapsed();
		fout << " - ";
		fout << MetaDataAPI[j].returnTimeElapsed();
		fout << " ms" << endl;
		}
	j++;
	}
	fout.close();
}

bool HarnessAPI::returnCommandInfoFile(ifstream& fin, ConfigurationAPI configurationData, deque<MetaDataAPI>& metaDataCommandData) {
	
	MetaDataAPI tempMetaData;
	string marker;
	string command;

	getline(fin, marker);
	marker.clear();

	fin >> command;
	// loop through metaData to load into deque
	while (command[command.length() - 1] == ';') {
		tempMetaData.readThroughMetaData(command);
		tempMetaData.assignTimeElapsed(configurationData);
		metaDataCommandData.push_back(tempMetaData);

		command.clear();
		fin >> command;
		// check for hard drive
		if(command.substr(2, 4) == "hard") {
			string continueLoad;
			fin >> continueLoad;
			command.append(" ");
			command.append(continueLoad);
		}
	}
	if (command[command.length() - 1] == '.') {
		MetaDataAPI tempMetaData;
		if (tempMetaData.readThroughMetaData(command) == false) {
			cout << "ERR: There is an error in metaData" << endl;
			// failure
			return 0;
		}
	tempMetaData.assignTimeElapsed(configurationData);
	// load into deque
	metaDataCommandData.push_back(tempMetaData);
	command.clear();
	} 
	getline(fin, marker);
	getline(fin, marker);
	marker.clear();
	// success
	return 1;
}
// change metamemoryInputapi to loaded metamemoryInput
void HarnessAPI::determineOutput(ConfigurationAPI configurationData, deque<MetaDataAPI> MetaDataAPI) {

	if (configurationData.returnLogValue() + 1 == 1) {
		returnOutputMonitor(configurationData, MetaDataAPI);
	} else if(configurationData.returnLogValue() + 1 == 2) {
		fileLine(configurationData, MetaDataAPI);
	} else if(configurationData.returnLogValue() + 1 == 3) {
		returnOutputMonitor(configurationData, MetaDataAPI);
	} else {
		return;
	}
}
