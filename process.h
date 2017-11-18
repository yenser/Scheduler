// process.h
#ifndef PROCESS_H
#define PROCESS_H

class Process {
	int ProcessId, Burst, Arrival, Pri, Dline, IO;
	public:
		Process(int, int, int, int, int, int);
		Process();
		int getProcessId();
		int getBurst();
		int getArrival();
		int getPri();
		int getDline();
		int getIO();

		void setAll(int, int, int, int, int, int);
		void setProcessId(int);
		void setBurst(int);
		void setArrival(int);
		void setPri(int);
		void setDline(int);
		void setIO(int);

		void print();

};

#endif