// process.h
#ifndef PROCESS_H
#define PROCESS_H

class Process {
	
	public:
		int ProcessId, Burst, Arrival, Priority, Deadline, IO, Aging, OriginalPriority;
		Process(int, int, int, int, int, int);
		Process(int, int, int, int, int, int, int);
		Process();
		int getProcessId() const;
		int getBurst() const;
		int getArrival() const;
		int getPriority() const;
		int getDeadline() const;
		int getIO() const;
		int getAging() const;
		int getOriginalPriority() const;

		void setAll(int, int, int, int, int, int);
		void setProcessId(int);
		void setBurst(int);
		void setArrival(int);
		void setPriority(int);
		void setDeadline(int);
		void setIO(int);
		void setAging(int);
		void decreaseAging(int);

		void print();

};

#endif