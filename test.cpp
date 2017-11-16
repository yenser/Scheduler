//test.cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;



int main() {

	ifstream infile("500k_processes");
	int processes[500000][6];
	string line;
	cout << "starting to read\n";
	int i = 0;
	std::getline(infile, line);
	cout << "Pid	Bst	Arr	Pri	Dline	I/O\n";
	cout << "+_________________________________________+\n";
	while (std::getline(infile, line))
	{
		
	    std::istringstream iss(line);
	    int a, b, c, d, e, f;
	    if (!(iss >> a >> b >> c >> d >> e >> f)) { 
	    	cout << "error\n";
	    	break; 
	    } // error

	    if(a < 0 || b < 0 || c < 0 || d < 0 || e < 0 || f < 0)
	    	continue;
	    cout << i << "\n";
	    processes[i][0] = a;
	    processes[i][1] = b;
	    processes[i][2] = c;
	    processes[i][3] = d;
	    processes[i][4] = e;
	    processes[i][5] = f;
	    if(i < 25)
	    	cout << a << "	" << b << "	" << c << "	" << d << "	" << e << "	" << f << "\n";
	    i++;
	}

	cout << "\nlength of file: " << sizeof processes << "\nlength without negatives: " << i << "\n";

	return 0;
}