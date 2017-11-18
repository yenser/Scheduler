// process.h
#ifndef PROCESS_H
#define PROCESS_H

class Process {
	int ProcessId, Burst, Arrival, Priority, Deadline, IO;
	public:
		Process(int, int, int, int, int, int);
		Process();
		int getProcessId();
		int getBurst();
		int getArrival();
		int getPriority();
		int getDeadline();
		int getIO();

		void setAll(int, int, int, int, int, int);
		void setProcessId(int);
		void setBurst(int);
		void setArrival(int);
		void setPriority(int);
		void setDeadline(int);
		void setIO(int);

		void print();

};

#endif