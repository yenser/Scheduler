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

	vector<Process> processes, queue, throwOuts;
	string fileName = "5_processes";

	processes = readFileOfProcesses(fileName);

	cout << "\n";

	//clock cycle
	int clock = 0;
	while(1) {

		//get arrivals and set priority
		while(processes.size() > 0 && processes.at(0).getArrival() == clock) {
			cout << "hello\n";
			//set priority
			processes.at(0).setPriority(processes.at(0).getDeadline() - processes.at(0).getArrival());
			//check where to put in array
			int j = 0;
			while((queue.size() > 0) && (processes.at(0).getPriority() >= queue.at(j).getPriority())) {
				j++;
			}
			//insert
			queue.insert(queue.begin()+j,processes.at(0));
			processes.erase(processes.begin());
			
		}
		// end get and set

		//run process
			//check for throwOuts
		while (queue.size() > 0 && (queue.at(0).getDeadline() - queue.at(0).getBurst()) < clock-1) {
			throwOuts.push_back(queue.at(0));
			queue.erase(queue.begin());
		}

		if(queue.size() > 0) {
			int burst = queue.at(0).getBurst();
			burst--;
			if(burst == 0) {
				queue.erase(queue.begin());
			}
			else {
				queue.at(0).setBurst(burst);
			}	
		}
		else {
			break;
		}
		//end run

		//print
		printAll(queue, clock);


		//clock tick
		clock++;
	}

	//printAll(throwOuts, -1);
	return 0;
}