/*
Marcus Casey
CS 446
Sim 04
Collaborators: None - Stack Overflow and cplusplus.com. 
*/

// include guards
#ifndef CONFIGURATION_API
#define CONFIGURATION_API

// includes
#include <string>
#include <fstream>
#include <vector>
#include <iostream>


using namespace std;

class ConfigurationAPI {

public:
	ConfigurationAPI(); // Configuration constructor		
	~ConfigurationAPI(); // Configuration destructor
		
	string returnFileLocation(); // Return file location
	string returnLogLocation(); // Return log file location


	float returnVersion(); //log version

	bool loadConfigurationTime(string, string, int, int&); 

	int returnConfigurationTime(char, string); // Use meta memoryInput to determine correct time
	
	void assignLogValue(int); // Log type = valueToAssign	
	void assignFileLocation(string); // Meta memoryInput file location = valueToAssign
	void assignMemoryTime(int); // Memory time = valueToAssign
	void assignVersion(float); // Meta file location = valueToAssign
	void assignLogLocation(string); // Log location = valueToAssign
	void assignMonitorTime(int); // Monitor time = valueToAssign
	void assignScannerTime(int); // Scanner time = valueToAssign
	void assignHDTime(int); // Hard drive time = valueToAssign
	void assignProcessorTime(int); // Processor time = valueToAssign
	void assignKeyboardTime(int); // Keyboard time = valueToAssign
	void assignProjectorTime(int); // Projector time = valueToAssign
	void loadConfigData(ifstream&); // File check & parse
	void assignSysMemory(int);
	void assignHdAmount(int);
	void assignProjAmount(int);
	
	int transformMemoryType(int, char);
	int returnSysMemory();
	int detConfigmatrix(string); // SeapThreadCreateMainh in config matrix for indexof
	int returnProcessorTime(); // Return processor time
	int returnMemoryTime(); // Return memory time
	int returnKeyboardTime(); // Return projector time
	int detKeyExport(); // Return keyboard time
	int returnMonitorTime(); // Return monitor time
	int returnScannerTime(); // Return scanner time
	int returnHDTime(); // Return hard drive time
	int returnLogValue(); // Find log type from file and return
	int returnMemBlockAmt(); 
	int returnHdAmt();
	int returnProjAmount();


// new
		int getProcessorQuantumNumber();		
		int getCpuScheduleCode();

		void setProcessorQuantumNumber(int);		
		void setCpuScheduleCode(int);

private:
	string logLocation; // log loc
	string fileLocation; // file loc
	float configVersion; // descriptionInterpreter type
	int logValue; // log type
	string configurationMatrix[7] = {"Monitor", "Processor", "Scanner", "Hard", "Keyboard", "Memory", "Projector"}; // config types in order from example file
	
	// memory amount time variables	
	int timeMemory;
	int timeMonitor;
	int timeProcessor;
	int timeKeyboard;
	int timeProjector;
	int timeHD;
	int timeScanner;
	int hdAmount =2;
	int projAmt = 4;
	int systemMemory, memBlockAmt;

// new
 int processorQuantumNumber, cpuScheduleCode;


};

#endif
