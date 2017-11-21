// process.h
#ifndef PROCESS_H
#define PROCESS_H

class Process {
	
	public:
		int ProcessId, Burst, Arrival, Priority, Deadline, IO;
		Process(int, int, int, int, int, int);
		Process();
		int getProcessId() const;
		int getBurst() const;
		int getArrival() const;
		int getPriority() const;
		int getDeadline() const;
		int getIO() const;

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