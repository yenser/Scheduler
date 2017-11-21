//test.cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <iterator>
#include <algorithm>

#include "process.h"
#include "methods.h"

using namespace std;


// namespace std
// {
//     template<> struct less<Process>
//     {
//        bool operator() (const Process& lhs, const Process& rhs) const
//        {
//            return lhs.getArrival() < rhs.getArrival();
//        }
//     };
// }
// bool operator<(const Process& a, const Process& b) {
//   return a.getArrival() > b.getArrival();
// }

int main() {

	// vector<Process> processes;
	priority_queue<Process> processes;
	string fileName = "500k_processes";
	Process p;

	//processes = readFileOfProcesses(fileName);
	processes = readFileArrival(fileName);

	cout << "size: " << processes.size() << endl;
	p = processes.top();
	p.print();
	// while(!processes.empty()){
	// 	cout << processes.top() << endl;
	// 	processes.pop();
	// }

	return 0;
}