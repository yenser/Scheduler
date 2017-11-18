//test.cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using namespace std;



int main() {

	ifstream infile("500k_processes");
	//int processes[500000][6];
	string line;
	cout << "starting to read\n";
	int i = 0;
	int size = 500000;
	vector<Process> processes[size];

	std::getline(infile, line);
	cout << "Pid	Bst	Arr	Pri	Dline	I/O\n";
	cout << "+_________________________________________+\n";
	while (std::getline(infile, line)) {
		
	    std::istringstream iss(line);
	    int a, b, c, d, e, f;
	    if (!(iss >> a >> b >> c >> d >> e >> f)) { 
	    	cout << "error\n";
	    	break; 
	    } // error

	    if(a < 0 || b < 0 || c < 0 || d < 0 || e < 0 || f < 0)
	    	continue;
	    processes[i].setAll(a,b,c,d,e,f);
	    i++;
	}

	cout << "\nlength without negatives: " << i << "\n";

	for (i = 1501; i < 1528; i++)
	    	processes[size-i].print();

	return 0;
}