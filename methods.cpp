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

priority_queue<Process> readFileArrivalRTS(string fileName) {
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

	    if(a < 0 || b < 0 || c < 0 || e < 0)
	    	continue;
	    processes.push(Process(a,b,c,d,e,f));
	}


	return processes;
}

priority_queue<Process> readFileArrivalMFQS(string fileName) {
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

	    if(a < 0 || b < 0 || c < 0 || d < 0 || f < 0)
	    	continue;
	    processes.push(Process(a,b,c,d,e,f));
	}


	return processes;
}

priority_queue<Process> readFileArrivalWHS(string fileName) {
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

	    if(a < 0 || b < 0 || c < 0 || e < 0 || f < 0)
	    	continue;
	    processes.push(Process(a,b,c,d,e,f));
	}


	return processes;
}

void printAll(priority_queue<Process, vector<Process>, dline> list, int clock, priority_queue<Process> completed, priority_queue<Process> throwOuts) {
	cout << "Clock: " << clock << "         " << "Processes: " << list.size() << "         " << "Completed: " << completed.size() << "         " << "Throw Outs: " << throwOuts.size() << '\r' << flush;

}

void printMFQS(int list4, int list3, int list2, int list1, int list0, int clock) {
	cout << "Clock: " << clock  << " " << "NP: " << list4+list3+list2+list1+list0 << " Queue4: " << list4 << "        " << "Queue3: " << list3 << "        " << "Queue2: " << list2 << "        " << "Queue1: " << list1 << "        " << "FCFS: " << list0 <<  "        " << '\r' << flush;
}

void RTS(priority_queue<Process> processes) {

	priority_queue<Process, vector<Process>, dline> dlineQueue, tempQueue; 
	priority_queue<Process> throwOuts, completed;
	Process p;
	int np = 0;
	np = processes.size();
	clock_t t1,t2;
    t1=clock();

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
				p = dlineQueue.top();
				int waitTime = tick - p.getArrival() - p.getOriginalBurst();
				p.setWaitTime(waitTime);
				p.setTurnaroundTime(tick-p.getArrival());
				completed.push(p);
				dlineQueue.pop();
			}
			else {
				p = dlineQueue.top();
				p.setBurst(burst);
				dlineQueue.pop();
				dlineQueue.push(p);
			}	
		}
		else {
			break;
		}
		//end run

		
		// cout << endl << endl << "clock: " << tick << endl << "PID\tBRST\tARV\tPR\tDL\tIO"<<endl;
		// cout << "_________________________________________" << endl;
		// int size = dlineQueue.size();
		// for(int i = 0; i < size; i++) {
		// 	p = dlineQueue.top();
		// 	p.print();
		// 	dlineQueue.pop();
		// 	tempQueue.push(p);
		// }
		// swap(dlineQueue, tempQueue);
	
		if(tick%100 == 0)
			printAll(dlineQueue, tick, completed, throwOuts);	
		
		


		//clock tick
		tick++;
	}


	t2=clock();
    float diff ((float)t2-(float)t1);
    int awt, att, completeSize;
    awt = att = completeSize = 0;
    completeSize = completed.size();
    for(int i = 0; i < completeSize; i++) {
    	p = completed.top();
    	completed.pop();
    	awt += p.getWaitTime();
    	att += p.getTurnaroundTime();
    }

    awt = awt/completeSize;
    att = att/completeSize;

    cout << "\n\n\tTotal Processes: " << np << endl;
    cout << "\tNumber completed: " << completeSize << endl;
    cout << "\tNumber failed: " << throwOuts.size() << endl;
    cout << "\tAverage Turn Around Time: " << att << endl;
    cout << "\tAverage Wait Time: " << awt << endl;
    float seconds = diff / CLOCKS_PER_SEC;
    cout << "\tSeconds: " << seconds << endl;
    cout << "_________________________________________\n";
}

void MFQS (priority_queue<Process> processes, int timeQuantum, int queueSize, int age) {
	int TQ1, TQ2, TQ3, TQ4, currentTQ, index, fcfsSize, np;
	np = processes.size();

	TQ1 = TQ2 = TQ3 = TQ4 = currentTQ = 0;

	index = 0;

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


	priority_queue<Process, vector<Process>, priority> queue1, queue2, queue3, queue4, *currentQueue;
	queue<Process> fcfs, queueIO, completed;

	currentTQ = 0;

	Process p;
	clock_t t1,t2;
    t1=clock();

    p = processes.top();

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
				currentTQ = fcfs.front().getBurst();
				index = 0;
			}
		} 
		//end check


		//run process
		if(queue4.size() == 0 && queue3.size() == 0 && queue2.size() == 0 && queue1.size() == 0 && fcfs.size() == 0 && queueIO.size() == 0) { 
			tick++;
			continue;
		}


		if(index != 0) {

			int burst = currentQueue->top().getBurst();
			burst--;
			currentTQ--;
			if(burst == 0) {
				p = currentQueue->top();
				int waitTime = tick - p.getArrival() - p.getOriginalBurst() - p.getOriginalIO();
				p.setWaitTime(waitTime);
				p.setTurnaroundTime(tick - p.getArrival());
				completed.push(p);
				currentQueue->pop();
				currentTQ = 0;
			} else {
				p = currentQueue->top();
				p.setBurst(burst);
				currentQueue->pop();
				


				//check if TQ finishes
				if(currentTQ == 0) {
					if(index == 4) {
						queue3.push(p);
					} else if(index == 3) {
						queue2.push(p);
					} else if(index == 2) {
						queue1.push(p);
					} else if(index == 1) {
						p.setAging(age);
						fcfs.push(p);
					}
				} else if(currentTQ == 1 && p.getIO() > 0) {
					//put in IO
					queueIO.push(p);
					currentTQ = 0;
				} else {
					currentQueue->push(p);
				}
			}
		} else {


			int burst = fcfs.front().getBurst();
			burst--;
			currentTQ--;
			if(burst == 0) {
				p = fcfs.front();
				p.setWaitTime(tick - p.getArrival() - p.getOriginalBurst() - p.getOriginalIO());
				p.setTurnaroundTime(tick - p.getArrival());
				completed.push(p);
				fcfs.pop();
				currentTQ = 0;
			} else {
				fcfs.front().setBurst(burst);
			}
		}
		//end run

		//run IO
		if(queueIO.size() > 0) {
			int size = 0;
			size = queueIO.size();
			for(int i = 0; i < size; i++) {
				p = queueIO.front();
				queueIO.pop();
				p.setIO(p.getIO()-1);
				if(p.getIO() == 0) {
					if(queueSize == 1) {
						fcfs.push(p);
					} else if(queueSize == 2) {
						queue1.push(p);
					} else if(queueSize == 3) {
						queue2.push(p);
					} else if(queueSize == 4) {
						queue3.push(p);
					} else {
						queue4.push(p);
					}
				} else {
					queueIO.push(p);
				}
			}
		}
		//end IO

		//aging
		if(fcfs.size() > 0 && queueSize > 1) {
			if(index == 0) {
				p = fcfs.front();
				fcfs.pop();
				fcfsSize = fcfs.size();
				fcfs.push(p);
			}
			else {
				fcfsSize = fcfs.size();
			}

			Process pp;
			
			
			for(int i = 0; i < fcfsSize; i++) {
				pp = fcfs.front();
				fcfs.pop();
				pp.decreaseAging(1);

				if(pp.getAging() == 0) {
					queue1.push(pp);
				} else {
					fcfs.push(pp);
				}
			}
		}
		//end aging
		



		if(processes.size() == 0 && fcfs.size() == 0 && queue1.size() == 0 && queue2.size() == 0 && queue3.size() == 0 && queue4.size() == 0 && queueIO.size() == 0)
			break;

		//print

		// printMFQS(queue4.size(), queue3.size(), queue2.size(), queue1.size(), fcfs.size(), tick);
		// cout << endl;

		if(tick%100 == 0)
			printMFQS(queue4.size(), queue3.size(), queue2.size(), queue1.size(), fcfs.size(), tick);
		

		//clock tick
		tick++;
	}

	t2=clock();
    float diff ((float)t2-(float)t1);
    long awt, att, completeSize;
    awt = att = completeSize = 0;
    completeSize = completed.size();
    for(int i = 0; i < completeSize; i++) {
    	p = completed.front();
    	completed.pop();
    	awt += p.getWaitTime();
    	att += p.getTurnaroundTime();
    }

    awt = awt/completeSize;
    att = att/completeSize;
    float seconds = diff / CLOCKS_PER_SEC;

    cout << "\n\n\tTotal Processes: " << np << endl;
    cout << "\tSeconds: " << seconds << endl;
    cout << "\tAverage Turn Around Time: " << att << endl;
    cout << "\tAverage Wait Time: " << awt << endl;
    cout << "_________________________________________\n";
}

void WHS (priority_queue<Process> processes, int TQ, int age) {

	int currentTQ = 0;
	int index = 99;
	int burst;
	int np = processes.size();
	int priorityDecrease;
	queue<Process> completed, queueIO;
	vector<queue<Process> > QueueArray;
	QueueArray.resize(100);

	Process p;
	Process* running;


	clock_t t1,t2;
    t1=clock();

    cout << "\n\n\n\tRunning Windows Hybrid System" << endl;
    cout << "_________________________________________\n";


	//clock cycle
	int tick = 0;
	while(1) {

		//get arrivals and put in first queue
		while(processes.size() > 0 && processes.top().getArrival() == tick) {
			
			p = processes.top();
			processes.pop();
			p.setAging(age);
			if(p.getPriority() >= 100) {
				QueueArray.at(99).push(p);
			} else {
				QueueArray.at(p.getPriority()).push(p);
			}
			np++;
		}
		// end get and set

		//Check which queue to run
		if(currentTQ == 0) {
			index = 99;
			while(index >= 0 && QueueArray.at(index).size() == 0) {
				index--;
			}
			currentTQ = TQ;
		} 
		//end check

		//print
		if(tick%100 == 0 || np == 0)
			cout << "clock: " << tick << " np: " << np << " index: " << index << "                          " << '\r' << flush;

		// printWHS(QueueArray, tick);
		//end print

		//check for end or empty processes
		if(processes.size() == 0 && index < 0)
			break;

		if(index < 0) {
			tick++;
			continue;
		}
		//end check

		//run
		running = &QueueArray[index].front();
		burst = running->getBurst();

		burst--;
		currentTQ--;

		if(burst == 0) {
			p = QueueArray[index].front();
			p.setWaitTime(tick - p.getArrival() - p.getOriginalBurst() - p.getOriginalIO());
			p.setTurnaroundTime(tick - p.getArrival());
			completed.push(p);
			QueueArray[index].pop();
			currentTQ = 0;
			np--;
		} else {
			running->setBurst(burst);

			//check for IO
			if(currentTQ == 1) {
				if(running->getIO() > 0) {
					queueIO.push(QueueArray[index].front());
					QueueArray[index].pop();
					currentTQ = 0;
				}
			}
			
			//check if TQ ends
			else if(currentTQ == 0) {
				p = QueueArray[index].front();
				QueueArray[index].pop();

				priorityDecrease = p.getPriority() - TQ;

				//setting priority
				if(priorityDecrease < p.getOriginalPriority()) {
					p.setPriority(p.getOriginalPriority());
				} else {
					p.setPriority(priorityDecrease);
				}
				QueueArray[p.getPriority()].push(p);

			}
		}
		// cout << "\tendRunning" << endl;
		//end run



		//run IO
		if(queueIO.size() > 0) {
			int size = 0;
			size = queueIO.size();
			for(int i = 0; i < size; i++) {
				p = queueIO.front();
				queueIO.pop();
				p.setIO(p.getIO()-1);
				if(p.getIO() == 0) {
					if(p.getOriginalPriority() < 49) {
						p.adjustPriorityBy(p.getOriginalIO());
						if(p.getPriority() > 49) {
							QueueArray[49].push(p);
						} else {
							QueueArray[p.getPriority()].push(p);
						}
					} else {
						p.adjustPriorityBy(p.getOriginalIO());
						if(p.getPriority() > 99) {
							QueueArray[99].push(p);
						} else {
							QueueArray[p.getPriority()].push(p);
						}
					}
				} else {
					queueIO.push(p);
				}
			}
		}
		//end IO


		//age all
		int size = 0;
			//age 0 - 9
		for(int i = 0; i < 10; i++) {
			if(i == index) {
				p=QueueArray[i].front();
				QueueArray[i].pop();
				size = QueueArray[i].size();
				QueueArray[i].push(p);
			} else {
				size = QueueArray[i].size();	
			}

			for(int j = 0; j < size; j++) {
				p = QueueArray[i].front();
				//age it
				p.decreaseAging(1);
				QueueArray[i].pop();

				//check if age timer ends
				if(p.getAging() == 0) {
					p.setAging(age);
					p.adjustPriorityBy(10);
				}
				
				if(p.getPriority() >= 50) {
					QueueArray[49].push(p);
				}
				else {
					QueueArray[p.getPriority()].push(p);
				}	
			}
		
		}
		//end age



		//clock tick
		tick++;
	}


	t2=clock();
    float diff ((float)t2-(float)t1);
    long awt, att, completeSize;
    awt = att = completeSize = 0;
    completeSize = completed.size();
    for(int i = 0; i < completeSize; i++) {
    	p = completed.front();
    	completed.pop();
    	awt += p.getWaitTime();
    	att += p.getTurnaroundTime();
    }

    awt = awt/completeSize;
    att = att/completeSize;
    float seconds = diff / CLOCKS_PER_SEC;

    cout << "\n\n\tTotal Processes: " << np << endl;
    cout << "\tSeconds: " << seconds << endl;
    cout << "\tAverage Turn Around Time: " << att << endl;
    cout << "\tAverage Wait Time: " << awt << endl;
    cout << "_________________________________________\n";
}

void printWHS(vector<queue<Process> > QueueArray, int clock) {
	cout << "Clock: " << clock << " | ";

	int size = 0;
	int shift = 0;
	for(int i = 0; i < 10; i++) {
			size += QueueArray[i+shift].size();
	}

	cout << "0-9: " << size << " |";

	size=0;
	shift+=10;
	for(int i = 0; i < 10; i++) {
			size += QueueArray[i+shift].size();
	}

	cout << " 10-19: " << size << " |";
	size=0;
	shift+=10;
	for(int i = 0; i < 10; i++) {
			size += QueueArray[i+shift].size();
	}

	cout << " 20-29: " << size << " |";
	size=0;
	shift+=10;
	for(int i = 0; i < 10; i++) {
			size += QueueArray[i+shift].size();
	}

	cout << " 30-39: " << size << " |";
	size=0;
	shift+=10;
	for(int i = 0; i < 10; i++) {
			size += QueueArray[i+shift].size();
	}

	cout << " 40-49: " << size << " |";
	size=0;
	shift+=10;
	for(int i = 0; i < 10; i++) {
			size += QueueArray[i+shift].size();
	}


	cout << " 50-59: " << size << " |";
	size=0;
	shift+=10;
	for(int i = 0; i < 10; i++) {
			size += QueueArray[i+shift].size();
	}


	cout << " 60-69: " << size << " |";
	size=0;
	shift+=10;
	for(int i = 0; i < 10; i++) {
			size += QueueArray[i+shift].size();
	}

	cout << " 70-79: " << size << " |";
	size=0;
	shift+=10;
	for(int i = 0; i < 10; i++) {
			size += QueueArray[i+shift].size();
	}

	cout << " 80-89: " << size << " |";
	size=0;
	shift+=10;
	for(int i = 0; i < 10; i++) {
			size += QueueArray[i+shift].size();
	}

	cout << " 90-99: " << size <<"               " << endl << endl;
}