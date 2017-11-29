//scheduler.cpp

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <time.h>

#include "process.h"
#include "methods.h"

using namespace std;

int main() {

	priority_queue<Process> processes;
	string fileName = "500k_processes";
	processes = readFileArrival(fileName);

	//RTS(processes);
	//MFQS(processes, 64, 5, 100);
	WHS(processes);

	

	return 0;
}