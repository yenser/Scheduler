CFLAGS = -Wall
main: clean scheduler.o methods.o
	g++ scheduler.o methods.o -o scheduler

test: clean test.o methods.o process.o
	g++ test.o methods.o process.o -o test

scheduler.o: scheduler.cpp
	g++ -c scheduler.cpp $(CFLAGS)

methods.o: methods.cpp methods.h
	g++ -c methods.cpp $(CFLAGS)

process.o: process.cpp process.h
	g++ -c process.cpp $(CFLAGS)

test.o: test.cpp
	g++ -c test.cpp $(CFLAGS)

clean:
	rm -f *.o scheduler test
