//methods.cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "process.h"
#include "methods.h"

using namespace std;

struct sortProcess {
  bool operator() (Process i,Process j) { return (i.getArrival()<j.getArrival());}
} sortProcess;

vector<Process> readFileOfProcesses(string fileName) {

	const char *cstr = fileName.c_str();

	ifstream infile(cstr);
	//int processes[500000][6];
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
	cout << "Pid	Bst	Arr	Pri	Dline	I/O\n";
	cout << "+_________________________________________+\n";

	for(unsigned int i = 0; i < list.size(); i++) {
		if(i < 5) {
			list.at(i).print();	
		}
	}
	cout << "\n";
}