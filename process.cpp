//Pid - Burst - Arrival - Priority - Deadline - I/O
#include <iostream>
#include "process.h"

int ProcessId, Burst, Arrival, Priority, Deadline, IO;

Process::Process(int ProcessId, int Burst, int Arrival, int Priority, int Deadline, int IO) {
	this->ProcessId = ProcessId;
	this->Burst = Burst;
	this->Arrival = Arrival;
	this->Priority = Priority;
	this->Deadline = Deadline;
	this->IO = IO;
}

Process::Process() {
	this->ProcessId = -1;
	this->Burst = -1;
	this->Arrival = -1;
	this->Priority = -1;
	this->Deadline = -1;
	this->IO = -1;
}


int Process::getProcessId() const {
	return ProcessId;
}
int Process::getBurst() const {
	return Burst;
}
int Process::getArrival() const {
	return Arrival;
}
int Process::getPriority() const {
	return Priority;
}
int Process::getDeadline() const {
	return Deadline;
}
int Process::getIO() const {
	return IO;
}


void Process::setAll(int ProcessId, int Burst, int Arrival, int Priority, int Deadline, int IO) {
	this->ProcessId = ProcessId;
	this->Burst = Burst;
	this->Arrival = Arrival;
	this->Priority = Priority;
	this->Deadline = Deadline;
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

void Process::setPriority(int newPriority) {
	Priority = newPriority;
}

void Process::setDeadline(int newDeadline) {
	Deadline = newDeadline;
}

void Process::setIO(int newIO) {
	IO = newIO;
}

void Process::print() {
	std::cout << ProcessId << "	" << Burst << "	" << Arrival
	 << "	" << Priority << "	" << Deadline << "	" << IO << "\n";
}