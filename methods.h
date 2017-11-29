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

void printAll(std::priority_queue<Process>, int, std::priority_queue<Process>, std::priority_queue<Process>);

void printMFQS(int, int, int, int, int, int);

void printWHS(std::queue<Process>, std::string);

void RTS(std::priority_queue<Process>);

void MFQS(std::priority_queue<Process>, int, int, int);

void WHS(std::priority_queue<Process>);

#endif