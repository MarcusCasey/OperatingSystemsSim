/*
Marcus Casey
CS 446
Sim 05
Collaborators: None - Stack Overflow and cplusplus.com + tutorial posted on project - largely modeled after that
*/

#include "processControlBlock.h"

PCB::PCB() {
//new
	currentProcesstype = 0;
	blockAmtNumPCB = 0;
	prevAddr = 0;
	hardDriveAmtNumPCB = 0;
	hardDrivesUsed = 0;
	projAmtNumPCB = 0;
	projAmtUtilNumPCB = 0;
}

PCB::PCB(int assignPIDValue) {
	currentProcesstype = 0;
	pid = assignPIDValue;
}

PCB::~PCB() {
currentProcesstype = 4;
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
int PCB::getPID() {
	return pid;	
}

double PCB::returnPCBStartTime() {
	return startingTime;
}

void PCB::assignLengthProcess(double processSoupThreadCreateMaineLength) {
	lengthProcess = processSoupThreadCreateMaineLength;
}

void PCB::assignPCBStartTime(double processSoupThreadCreateMaineLength) {
	startingTime = processSoupThreadCreateMaineLength;
}

void PCB::assignHardDriveAmtPCB(int inputAmt) {

	hardDriveAmtNumPCB = inputAmt;
	
}

int PCB::returnBlockAmt() {
	return blockAmtNumPCB;
	
}
int PCB::returnPrevMemAdd() {

	return prevAddr;
	
}

int PCB::returnHardDriveAmtPCB() {

	return hardDriveAmtNumPCB;
	
}

int PCB::returnHardDriveAmtUtil() {

	return hardDrivesUsed;
	
}

int PCB::returnProjAmtUtil() {

	return projAmtNumPCB;
	
}

void PCB::setHardDrivesUsed(int inputAmt) {

	hardDrivesUsed = inputAmt;
	
}

void PCB::assignProjAmtPCB(int inputAmt) {

	projAmtNumPCB = inputAmt;
	
}

void PCB::assignProjAmtUtilPCB(int inputAmt) {

	projAmtUtilNumPCB = inputAmt;
	
}

void PCB::addBlockAmt() {

	blockAmtNumPCB++;

}

int PCB::getProjectorsUsed() {

	return projAmtUtilNumPCB;
	
}

void PCB::assignBlockAmtPCB(int inputAmt) {

	blockAmtNumPCB = inputAmt;
	
}

void PCB::assignPrevAddr(int inputAmt) {

	prevAddr = inputAmt;
	
}

void PCB::addHardDriveAmt() {

	hardDrivesUsed++;

}

void PCB::addProjAmt() {

	projAmtUtilNumPCB++;

}

// new interrupt and queue functions
bool PCB::isInterrupted() {
	return interrupted;
}

bool PCB::hasBeenInterrupted() {
	return interruptAction;
}

int PCB::returnQueueIndex() {
	return queueIndex;
}

double PCB::returnEstimatedProcessTime() {
	return estimatedProcessTime;
}

double PCB::returnEstimatedTimeRemaining() {
	return estimatedTimeRemaining;
}

void PCB::interrupt() {
	interrupted = true;
	interruptAction = true;
}

void PCB::assignInterrupt(bool source){
	interrupted = source;
	if (source == true) {
		interruptAction = true;
	}
}

void PCB::assignInterruptOccurred (bool source){
interruptAction = source;
}

void PCB::assignQueueIndex(int source){
	queueIndex = source;
}

void PCB::assignEstimatedProcessTime (double source) {
	estimatedProcessTime = source;
}

void PCB::assignEstimatedTimeRemaining (double source) {
	estimatedTimeRemaining = source;
}

void PCB::saveState (double state) {
	processData = state;
}

double PCB::loadState() {
return processData;
}
