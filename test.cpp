//test.cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;



int main() {

	ifstream infile("thefile.txt");

	string line;
	while (std::getline(infile, line))
	{
	    std::istringstream iss(line);
	    int a, b;
	    if (!(iss >> a >> b)) { break; } // error

	    cout << a << "	" << b;
	}

	return 0;
}