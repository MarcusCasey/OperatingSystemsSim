/*
Marcus Casey
CS 446
Sim 05
Collaborators: None - Stack Overflow and cplusplus.com. 
*/

// Include guards
#ifndef METADATAPI
#define METADATAPI

// Includes
#include <iostream>
#include <fstream>
#include <string>
#include "ConfigurationAPI.h"

using namespace std;

class MetaDataAPI {
public:
	MetaDataAPI(); // MetaDeque constructor
	MetaDataAPI(char, string, int); // Parameterized constructor for MetaDeque 
	~MetaDataAPI(); // MetaDeque destructor
		
	string returnDescription(); // Return metaDataWord

	void detAmtTime(int); // Time to compute descriptionInput	
	void detNumCycle(int); // Amount of cycles
	void detDesc(string); // Desc Location
	void returnCommand(char); // Desc To metaLoc
	void assignTimeElapsed(ConfigurationAPI); // Length of grabbing config memoryInput

	char returnCommand(); // Return the meta descriptionInterpreter  
	
	int returnTimeElapsed(); // Amount of execute time
	int returnCommandIndex(char); // Look from descriptionInputDatabase, return index
	int returnCycleElapsed(); // Return total cycles amount		
	int returnDescriptionIndex(int, string); // Look from descriptionInputDatabase, return a # based on index	
	bool readThroughMetaData(string); 


// new
		void setData(char, string, int, int);

	void print();
private:
	// all possible meta memoryInput and phrases in arr format; as recommended in class
	char descriptionInput;

	string oDesc[3] = {"hard drive", "monitor", "projector"};
	string aDesc[2] = {"begin", "finish"};
	string mDesc[2] = {"block", "allocate"};
	string sDesc[2] = {"begin", "finish"};
	string iDesc[3] = {"hard drive", "keyboard", "scanner"};
	string metaDataWord;
	string pDesc = "run";
	// descriptions from sample input file in order
	char descriptionInputDatabase[6] = {'S', 'A', 'P', 'I', 'O', 'M'}; 

	int amtCyclesTotal;
	int amtTotalTimeRan;
};
#endif
