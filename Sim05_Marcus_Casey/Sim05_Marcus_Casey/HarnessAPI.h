/*
Marcus Casey
CS 446
Sim 05
Collaborators: None - Stack Overflow and cplusplus.com. 
*/

#ifndef HARNESSAPI
#define HARNESSAPI


#include <iostream>
#include <fstream>
#include <string>
#include <deque>

#include "ConfigurationAPI.h"
#include "MetaDataAPI.h"

using namespace std;

class HarnessAPI {

public:
	bool returnCommandInfoFile(ifstream&, ConfigurationAPI, deque<MetaDataAPI>&);
	void determineOutput(ConfigurationAPI, deque<MetaDataAPI>);
	void returnOutputMonitor(ConfigurationAPI, deque<MetaDataAPI>);
	void fileLine(ConfigurationAPI, deque<MetaDataAPI>);
};
#endif
