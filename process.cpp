//Pid - Burst - Arrival - Pri - Dline - I/O
#include <iostream>
#include "process.h"

int ProcessId, Burst, Arrival, Pri, Dline, IO;

Process::Process(int ProcessId, int Burst, int Arrival, int Pri, int Dline, int IO) {
	this->ProcessId = ProcessId;
	this->Burst = Burst;
	this->Arrival = Arrival;
	this->Pri = Pri;
	this->Dline = Dline;
	this->IO = IO;
}

Process::Process() {
	this->ProcessId = -1;
	this->Burst = -1;
	this->Arrival = -1;
	this->Pri = -1;
	this->Dline = -1;
	this->IO = -1;
}


int Process::getProcessId() {
	return ProcessId;
}
int Process::getBurst() {
	return Burst;
}
int Process::getArrival() {
	return Arrival;
}
int Process::getPri() {
	return Pri;
}
int Process::getDline() {
	return Dline;
}
int Process::getIO() {
	return IO;
}


void Process::setAll(int ProcessId, int Burst, int Arrival, int Pri, int Dline, int IO) {
	this->ProcessId = ProcessId;
	this->Burst = Burst;
	this->Arrival = Arrival;
	this->Pri = Pri;
	this->Dline = Dline;
	this->IO = IO;
}

void Process::setProcessId(int newPID) {
	ProcessId = newPID;
}

void Process::setBurst(int newBurst) {
	Burst = newBurst;
}

void Process::setArrival(int newArrival) {
	Arrival = newArrival;
}

void Process::setPri(int newPri) {
	Pri = newPri;
}

void Process::setDline(int newDline) {
	Dline = newDline;
}

void Process::setIO(int newIO) {
	IO = newIO;
}

void Process::print() {
	std::cout << ProcessId << "	" << Burst << "	" << Arrival
	 << "	" << Pri << "	" << Dline << "	" << IO << "\n";
}