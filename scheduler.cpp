//scheduler.cpp

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

	vector<Process> processes, queue;
	string fileName = "5_processes";

	processes = readFileOfProcesses(fileName);

	cout << "Pid	Bst	Arr	Pri	Dline	I/O\n";
	cout << "+_________________________________________+\n";

	for(unsigned int i=0; i < processes.size(); i++) {
		processes.at(i).print();
	}

	cout << "\n";
int j = 0;
	//clock cycle
	int clock = 0;
	while(1) {


		//get arrivals
		while(processes.size() > 0 && processes.at(0).getArrival() == clock) {
			queue.push_back(processes.at(0));
			processes.erase(processes.begin());
			queue.at(j).print();
			j++;
		}


		//clock tick
		clock++;

		if(processes.size() == 0) {
			break;
		}
	}


	return 0;
}