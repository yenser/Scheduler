//test.cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "process.h"
#include "methods.h"

using namespace std;


// bool sortProcess(const Process & p1, const Process & p2) {
//    if (*p1.getArrival() != *p2.getArrival()) return *p1.getArrival() < *p2.getArrival();
//    return *p1.getArrival() < *p2.getArrival();
// }

int main() {

	vector<Process> processes;
	string fileName = "500k_processes";

	processes = readFileOfProcesses(fileName);


	for(unsigned int j = processes.size(); j > 0; j++) {
		processes.at(j).print();
	}

	return 0;
}