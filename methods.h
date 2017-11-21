//methods.h
#include <string>

#ifndef METHODS_H
#define METHODS_H

class priority {
	public:
	bool operator()(const Process&, const Process&);
};

bool operator<(const Process&, const Process&);

std::priority_queue<Process> readFileArrival(std::string);

void printAll(std::priority_queue<Process>, int);

void printMFQS(std::priority_queue<Process, std::vector<Process>, priority>, std::string, int);

void RTS(std::priority_queue<Process>);

void MFQS(std::priority_queue<Process>, int, int);

#endif