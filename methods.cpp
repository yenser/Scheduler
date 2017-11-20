//methods.cpp
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

struct sortProcess {
  bool operator() (Process i,Process j) { return (i.getArrival()>j.getArrival());}
} sortProcess;

vector<Process> readFileOfProcesses(string fileName) {

	const char *cstr = fileName.c_str();

	ifstream infile(cstr);
	string line;
	vector<Process> processes;

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
	    processes.push_back(Process(a,b,c,d,e,f));
	}


	sort(processes.begin(), processes.end(),sortProcess);

	return processes;
}

void printAll(vector<Process> list, int clock) {
	cout << "Clock: " << clock << "\n";
	cout << "Number of Processes: " << list.size() << "\n";
	cout << "Pid	Bst	Arr	Pri	Dline	I/O\n";
	cout << "+_________________________________________+\n";

	for(unsigned int i = list.size(); i > list.size()-5; i--) {
		list.at(i-1).print();
	}
	cout << "\n";

}

void printMFQS(vector<Process> list, string name, int clock) {
	cout << "Queue: " << name << endl;
	cout << "Clock: " << clock << endl;
	cout << "Number of Processes: " << list.size() << endl;
	cout << endl;

}

void RTS(vector<Process> processes) {

	vector<Process> queue, throwOuts, completed;
	clock_t t1,t2;
    t1=clock();


	//clock cycle
	int tick = 0;
	while(1) {

		//get arrivals and set priority
		while(processes.size() > 0 && processes.back().getArrival() == tick) {

			//check where to put in array
			unsigned int j = queue.size();
			while((j > 0) && (processes.back().getDeadline() > queue.at(j-1).getDeadline())) {
				j--;
			}
			//insert
			queue.insert(queue.begin()+j,processes.back());
			processes.pop_back();
		}
		// end get and set

		//run process
			//check for throwOuts

		while (queue.size() > 0 && (queue.back().getDeadline() - queue.back().getBurst()) < tick-1) {
			throwOuts.push_back(queue.back());
			queue.pop_back();
		}

		if(queue.size() > 0) {
			int burst = queue.back().getBurst();
			burst--;
			if(burst == 0) {
				completed.push_back(queue.back());
				queue.pop_back();
			}
			else {
				queue.back().setBurst(burst);
			}	
		}
		else {
			break;
		}
		//end run

		//print
		//if(tick%10 == 0) {
			printAll(queue, tick);	
		//}
		


		//clock tick
		tick++;
	}


	t2=clock();
    float diff ((float)t2-(float)t1);

    cout << "Number completed: " << completed.size() << endl;
    cout << "Number failed: " << throwOuts.size() << endl;
    float seconds = diff / CLOCKS_PER_SEC;
    cout << "Seconds: " << seconds << endl;
}