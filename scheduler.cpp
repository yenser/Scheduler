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

	string input = "";
	priority_queue<Process> processes;
	int TQ, Q, A;
	bool exit = false;

	cout << "Please enter the file you want to read: " << endl;
	getline(cin, input);
	string filename = input;

	while(!exit) {
		cout << "\n\n\nPlease Enter the Number you want:" << endl << "1. RTS\t\t2. MFQS\t\t3. WHS\t\t4. EXIT" << endl;
		getline(cin, input);

		if(input == "1") {
			processes = readFileArrivalRTS(filename);
			RTS(processes);

		} else if(input == "2") {

			cout << "MFQS:\tNumber of Queues: " << endl;
			getline(cin, input);
			Q = atoi(input.c_str());
			cout << "MFQS:\tTime Quantum: " << endl;
			getline(cin, input);
			TQ = atoi(input.c_str());
			cout << "MFQS:\tAge Limit: " << endl;
			getline(cin,input);
			A = atoi(input.c_str());

			processes = readFileArrivalMFQS(filename);
			MFQS(processes, TQ, Q, A);

		} else if(input == "3") {

			cout << "WHS:\tTime Quantum: " << endl;
			getline(cin, input);
			TQ = atoi(input.c_str());
			cout << "WHS:\tAge Limit: " << endl;
			getline(cin,input);
			A = atoi(input.c_str());

			processes = readFileArrivalWHS(filename);
			WHS(processes, TQ, A);
		} 
		else if(input == "4") {
			exit = true;
		} else {
			cout << "Wrong Input" << endl;
		}
	}

	

	return 0;
}