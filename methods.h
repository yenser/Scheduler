//methods.h
#include <string>

#ifndef METHODS_H
#define METHODS_H

std::vector<Process> readFileOfProcesses(std::string);

void printAll(std::vector<Process>, int);

void printMFQS(std::vector<Process>, std::string, int);

void RTS(std::vector<Process>);

#endif