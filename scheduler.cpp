//scheduler.cpp

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>

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
	//RTS(processes);


	int TQ1, TQ2, TQ3, TQ4, queueSize, currentTQ, index, timeQuantum;

	timeQuantum = 10;
	queueSize = 5;



	TQ4 = timeQuantum;
	TQ3 = TQ4*2;
	TQ2	= TQ3*2;
	TQ1 = TQ2*2;
	vector<Process> queue1, queue2, queue3, queue4, fcfs, *currentQueue;

	currentTQ = 0;

	clock_t t1,t2;
    t1=clock();


	//clock cycle
	int tick = 0;
	while(1) {

		//get arrivals and put in first queue
		while(processes.size() > 0 && processes.back().getArrival() == tick) {
			if(queueSize == 1) {
				fcfs.push_back(processes.back());
				processes.pop_back();
			} else if(queueSize == 2) {
				queue1.push_back(processes.back());
				processes.pop_back();
			} else if(queueSize == 3) {
				queue2.push_back(processes.back());
				processes.pop_back();
			} else if(queueSize == 4) {
				queue3.push_back(processes.back());
				processes.pop_back();
			} else {
				queue4.push_back(processes.back());
				processes.pop_back();
			}
		}
		// end get and set



		//Check which queue to run
		if(currentTQ == 0) {
			if(queueSize >= 5 && queue4.size() > 0) {
				//Queue1
				currentTQ = TQ4;
				currentQueue = &queue4;
				index = 4;
			} else if(queueSize >= 4 && queue3.size() > 0) {
				//Queue2
				currentTQ = TQ3;
				currentQueue = &queue3;
				index = 3;
			} else if(queueSize >= 3 && queue2.size() > 0) {
				//Queue3
				currentTQ = TQ2;
				currentQueue = &queue2;
				index = 2;
			} else if(queueSize >= 2 && queue1.size() > 0) {
				//Queue4
				currentTQ = TQ1;
				currentQueue = &queue1;
				index = 1;
			} else {
				//FCFS
				currentTQ = fcfs.front().getBurst();
				currentQueue = &fcfs;
				index = 0;
			}
		} 
		//end check




		//run process
		if(currentQueue->size() == 0) { 
			tick++;
			continue;
		}

		int burst = currentQueue->front().getBurst();
		burst--;
		currentTQ--;
		if(burst == 0) {
			currentQueue->erase(currentQueue->begin());
			currentTQ = 0;
		} else {
			currentQueue->front().setBurst(burst);	

			//check if TQ finishes
			if(currentTQ == 0) {
				if(index == 4) {
					queue3.push_back(currentQueue->front());
					currentQueue->erase(currentQueue->begin());
				} else if(index == 3) {
					queue2.push_back(currentQueue->front());
					currentQueue->erase(currentQueue->begin());
				} else if(index == 2) {
					queue1.push_back(currentQueue->front());
					currentQueue->erase(currentQueue->begin());
				} else if(index == 1) {
					fcfs.push_back(currentQueue->front());
					currentQueue->erase(currentQueue->begin());
				}
			}
		}
		
		//end run

		if(processes.size() == 0 && fcfs.size() == 0 && queue1.size() == 0 && queue2.size() == 0 && queue3.size() == 0 && queue4.size() == 0)
			break;


		//print
		if(tick%1000 == 0) {
			printMFQS(queue4, "queue4", tick);
			printMFQS(queue3, "queue3", tick);
			printMFQS(queue2, "queue2", tick);
			printMFQS(queue1, "queue1", tick);	
			printMFQS(fcfs, "fcfs", tick);	
			cout << "____________________________________________________" << endl;
		}

		//clock tick
		tick++;
	}


	t2=clock();
    float diff ((float)t2-(float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
    cout << "Seconds: " << seconds << endl;

	return 0;
}