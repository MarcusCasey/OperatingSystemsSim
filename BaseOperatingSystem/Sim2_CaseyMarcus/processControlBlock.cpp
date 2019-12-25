/*
Marcus Casey
CS 446
Sim 02
Collaborators: None - Stack Overflow and cplusplus.com + tutorial posted on project - largely modeled after that
*/

#include "processControlBlock.h"

PCB::PCB() {
	processState = 4;
}

PCB::PCB(int assignPIDValue) {
	processState = 2;
	pid = assignPIDValue;
}

PCB::~PCB() {
processState = 1;
}

void PCB::assignPID(int assignPIDValue) {
	pid = assignPIDValue;	
}

double PCB::returnLengthProcess() {
	return lengthProcess;
}
void PCB::replaceLengthProcess(double length) {
	lengthProcess += length;
}
int PCB::getpid() {
	return pid;	
}

double PCB::returnPCBStartTime() {
	return startingTime;
}

void PCB::assignLengthProcess(double processSourceLength) {
	lengthProcess = processSourceLength;
}

void PCB::assignPCBStartTime(double processSourceLength) {
	startingTime = processSourceLength;
}
