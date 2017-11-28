//methods.cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <iterator>
#include <algorithm>
#include <time.h>

#include "process.h"
#include "methods.h"

using namespace std;

bool priority::operator()(const Process& a, const Process& b) {
  if(a.getArrival() > b.getArrival()){
	return a.getPriority() < b.getPriority();
  }
  else {
  	return false;
  }
}

class dline {
	public:
	bool operator()(const Process& a, const Process& b) {
	  return a.getDeadline() > b.getDeadline();
	}
};

bool operator<(const Process& a, const Process& b) {
  return a.getArrival() > b.getArrival();
}

struct sortProcess {
  bool operator() (Process i,Process j) { return (i.getArrival()>j.getArrival());}
} sortProcess;

priority_queue<Process> readFileArrival(string fileName) {
	const char *cstr = fileName.c_str();
	priority_queue<Process> processes, arrivalOrder;
	ifstream infile(cstr);
	string line;

	std::getline(infile, line);

	while (std::getline(infile, line)) {
		
	    std::istringstream iss(line);
	    int a, b, c, d, e, f;
	    if (!(iss >> a >> b >> c >> d >> e >> f)) { 
	    	cout << "error\n";
	    	break; 
	    } // error

	    if(a < 0 || b < 0 || c < 0 || d < 0 || e < 0 || f < 0)
	    	continue;
	    processes.push(Process(a,b,c,d,e,f));
	}


	return processes;
}

void printAll(priority_queue<Process, vector<Process>, dline> list, int clock, priority_queue<Process> completed, priority_queue<Process> throwOuts) {
	cout << "Clock: " << clock << "         " << "Processes: " << list.size() << "         " << "Completed: " << completed.size() << "         " << "Throw Outs: " << throwOuts.size() << '\r' << flush;

}

void printMFQS(priority_queue<Process, vector<Process>, priority> list, string name, int clock) {
	cout << "Queue: " << name << endl;
	cout << "Number of Processes: " << list.size() << endl;
	cout << endl;

}

void printWHS(queue<Process> list, string name) {
	cout << "Queue: " << name << endl;
	cout << "Number of Processes: " << list.size() << endl;
	cout << endl;

}

void RTS(priority_queue<Process> processes) {

	priority_queue<Process, vector<Process>, dline> dlineQueue; 
	priority_queue<Process> throwOuts, completed;
	int att, np;
	Process p;
	clock_t t1,t2;
    t1=clock();
    np = processes.size();

    cout << "\n\tRunning RTS" << endl;
    cout << "_________________________________________\n";

	//clock cycle
	int tick = 0;
	while(1) {

		//get arrivals and set priority
		while(processes.size() > 0 && processes.top().getArrival() == tick) {
			dlineQueue.push(processes.top());
			processes.pop();
		}
		// end get and set

		//run process
			//check for throwOuts
		while (dlineQueue.size() > 0 && (dlineQueue.top().getDeadline() - dlineQueue.top().getBurst()) < tick-1) {
			throwOuts.push(dlineQueue.top());
			dlineQueue.pop();
		}
		

		if(dlineQueue.size() > 0) {
			int burst = dlineQueue.top().getBurst();
			burst--;
			if(burst == 0) {
				completed.push(dlineQueue.top());
				att += (tick - dlineQueue.top().getArrival());
				dlineQueue.pop();
			}
			else {
				p = dlineQueue.top();
				Process pp = Process(p.getProcessId(), burst, p.getArrival(), p.getPriority(), p.getDeadline(), p.getIO());
				dlineQueue.pop();
				dlineQueue.push(pp);
			}	
		}
		else {
			break;
		}
		//end run

		if(tick%100 == 0)
			printAll(dlineQueue, tick, completed, throwOuts);	
		


		//clock tick
		tick++;
	}


	t2=clock();
    float diff ((float)t2-(float)t1);
    att = att/completed.size();

    cout << "\n\tTotal Processes: " << np << endl;
    cout << "\tNumber completed: " << completed.size() << endl;
    cout << "\tNumber failed: " << throwOuts.size() << endl;
    cout << "\tAverage Turn Around Time: " << att << endl;
    float seconds = diff / CLOCKS_PER_SEC;
    cout << "\tSeconds: " << seconds << endl;
    cout << "_________________________________________\n";
}

void MFQS (priority_queue<Process> processes, int timeQuantum, int queueSize) {
	int TQ1, TQ2, TQ3, TQ4, currentTQ, index, ageTime;

	if(queueSize >= 5) {
		TQ4 = timeQuantum;
		TQ3 = TQ4/2;
		TQ2	= TQ3/2;
		TQ1 = TQ2/2;
	} else if(queueSize == 4) {
		TQ3 = timeQuantum;
		TQ2	= TQ3/2;
		TQ1 = TQ2/2;
	} else if(queueSize == 3) {
		TQ2	= timeQuantum;
		TQ1 = TQ2/2;
	} else {
		TQ1	= timeQuantum;
	}


	priority_queue<Process, vector<Process>, priority> queue1, queue2, queue3, queue4, fcfs, tempQueue, *currentQueue;

	currentTQ = 0;

	Process p;
	clock_t t1,t2;
    t1=clock();

    cout << "\n\n\n\tRunning MFQS" << endl;
    cout << "_________________________________________\n";
    cout << "\tQueue Size: "<< queueSize << endl;
    cout << "\tTime Quantum: " <<  timeQuantum <<endl;

	//clock cycle
	int tick = 0;
	while(1) {

		//get arrivals and put in first queue
		while(processes.size() > 0 && processes.top().getArrival() == tick) {
			if(queueSize == 1) {
				fcfs.push(processes.top());
				processes.pop();
			} else if(queueSize == 2) {
				queue1.push(processes.top());
				processes.pop();
			} else if(queueSize == 3) {
				queue2.push(processes.top());
				processes.pop();
			} else if(queueSize == 4) {
				queue3.push(processes.top());
				processes.pop();
			} else {
				queue4.push(processes.top());
				processes.pop();
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
				currentTQ = fcfs.top().getBurst();
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

		int burst = currentQueue->top().getBurst();
		burst--;
		currentTQ--;
		if(burst == 0) {
			currentQueue->pop();
			currentTQ = 0;
		} else {
			p = currentQueue->top();
			Process pp = Process(p.getProcessId(), burst, p.getArrival(), p.getPriority(), p.getDeadline(), p.getIO());
			currentQueue->pop();
			currentQueue->push(pp);	

			//aging
			// if(index == 0) {

			// 	fcfsSize = currentQueue->size();
			// 	for(int i = 0; i < fcfsSize; i++) {
			// 		if(fcfsSize-i <= 10) {
			// 			p = currentQueue->top();
			// 			Process pp = Process(p.getProcessId(), p.getBurst(), p.getArrival(), p.getPriority()-1, p.getDeadline(), p.getIO());
			// 			currentQueue->pop();
			// 			tempQueue.push(pp);	

			// 		}else {
			// 			tempQueue.push(currentQueue->top());
			// 			currentQueue->pop();
			// 		}
			// 	}

			// 	for(int i = 0; i < fcfsSize; i++) {
			// 		currentQueue->push(tempQueue.top());
			// 		tempQueue.pop();
			// 	}

			// }
			//end aging

			//check if TQ finishes
			if(currentTQ == 0) {
				if(index == 4) {
					queue3.push(currentQueue->top());
					currentQueue->pop();
				} else if(index == 3) {
					queue2.push(currentQueue->top());
					currentQueue->pop();
				} else if(index == 2) {
					queue1.push(currentQueue->top());
					currentQueue->pop();
				} else if(index == 1) {
					fcfs.push(currentQueue->top());
					currentQueue->pop();
				}
			}
		}
		
		//end run

		if(processes.size() == 0 && fcfs.size() == 0 && queue1.size() == 0 && queue2.size() == 0 && queue3.size() == 0 && queue4.size() == 0)
			break;


		// //print
		// if(tick%100000 == 0) {
		// 	cout << "clock: " << tick << endl;
		// 	printMFQS(queue4, "queue4", tick);
		// 	printMFQS(queue3, "queue3", tick);
		// 	printMFQS(queue2, "queue2", tick);
		// 	printMFQS(queue1, "queue1", tick);	
		// 	printMFQS(fcfs, "fcfs", tick);	
		// 	cout << "____________________________________________________" << endl;
		// }

		//clock tick
		tick++;
	}


	t2=clock();
    float diff ((float)t2-(float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
    cout << "\tSeconds: " << seconds << endl;
    cout << "_________________________________________\n";
}

void WHS (priority_queue<Process> processes) {

	int TQ = 10;
	int size = processes.size();
	queue<Process> waitQueue0, waitQueue1;
	priority_queue<Process, vector<Process>, priority> queueHigh, queueLow, *currentQueue, tempQueue;

	for (int i = 0; i < size; i++) {
		tempQueue.push(Process(processes.top().getProcessId(), processes.top().getBurst(), processes.top().getArrival(), processes.top().getPriority(), processes.top().getDeadline(), processes.top().getIO(), TQ));
		processes.pop();
	}


	clock_t t1,t2;
    t1=clock();

    cout << "\n\n\n\tRunning Windows Hybrid System" << endl;
    cout << "_________________________________________\n";


	//clock cycle
	int tick = 0;
	while(1) {

		//get arrivals and put in first queue
		while(processes.size() > 0 && processes.top().getArrival() == tick) {
			if(processes.top().getPriority() >= 50) {
				queueHigh.push(processes.top());
			}
			else {
				queueLow.push(processes.top());
			}
			processes.pop();
		}
		// end get and set



		//Check which queue to run
		if(queueHigh.size() > 0)
			currentQueue = &queueHigh;
		else
			currentQueue = &queueLow;
		//end check




		//run process
		if(currentQueue->size() == 0) { 
			tick++;
			continue;
		}

		int burst = currentQueue->top().getBurst();
		burst--;
		if(burst == 0) {
			currentQueue->pop();
		} else {

			//check for I/O
			if(TQ == 1) {
				//do I/O

			}

			//aging
			// if(index == 0) {

			// 	fcfsSize = currentQueue->size();
			// 	for(int i = 0; i < fcfsSize; i++) {
			// 		if(fcfsSize-i <= 10) {
			// 			p = currentQueue->top();
			// 			Process pp = Process(p.getProcessId(), p.getBurst(), p.getArrival(), p.getPriority()-1, p.getDeadline(), p.getIO());
			// 			currentQueue->pop();
			// 			tempQueue.push(pp);	

			// 		}else {
			// 			tempQueue.push(currentQueue->top());
			// 			currentQueue->pop();
			// 		}
			// 	}

			// 	for(int i = 0; i < fcfsSize; i++) {
			// 		currentQueue->push(tempQueue.top());
			// 		tempQueue.pop();
			// 	}

			// }
			//end aging
		}
		//end run

		if(processes.size() == 0 && queueHigh.size() == 0 && queueLow.size() == 0)
			break;


		//print
		if(tick%100 == 0) {
			cout << "clock: " << tick << "         " << "queue 50-99: " << queueHigh.size() << "         " << "queue 0-49: " << queueLow.size() << "         " << '\r' << flush;
			// printWHS(queueHigh, "51-100");
			// printWHS(queueLow, "1-50");
			// cout << "____________________________________________________" << endl;
		}

		//clock tick
		tick++;
	}


	t2=clock();
    float diff ((float)t2-(float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
    cout << "\n\tSeconds: " << seconds << endl;
    cout << "_________________________________________\n";
}