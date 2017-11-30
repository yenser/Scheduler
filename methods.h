//methods.h
#include <string>

#ifndef METHODS_H
#define METHODS_H

class priority {
	public:
	bool operator()(const Process&, const Process&);
};

bool operator<(const Process&, const Process&);

std::priority_queue<Process> readFileArrivalRTS(std::string);
std::priority_queue<Process> readFileArrivalMFQS(std::string);
std::priority_queue<Process> readFileArrivalWHS(std::string);

void printAll(std::priority_queue<Process>, int, std::priority_queue<Process>, std::priority_queue<Process>);

void printMFQS(int, int, int, int, int, int);

void RTS(std::priority_queue<Process>);

void MFQS(std::priority_queue<Process>, int, int, int);

void WHS(std::priority_queue<Process>, int, int);

void printWHS(std::vector<std::queue<Process> >, int);
#endif