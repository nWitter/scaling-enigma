CXX      := -c++
MPICXX   := mpiCC
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -fopenmp -std=gnu++11
LDFLAGS  := -L/usr/lib -lstdc++ -lm

all: functions.o simple_loop.o simple_loop MPI_Manager.o MPI_Manager timingThread.o timingThread 

functions.o: functions.h
	$(CXX) $(CXXFLAGS) -c functions.cpp
	
simple_loop.o: functions.h
	$(CXX) $(CXXFLAGS) -c simple_loop.cpp
	
simple_loop: simple_loop.o functions.o
	$(CXX) $(CXXFLAGS) -o simple_loop simple_loop.o functions.o

MPI_Manager.o:
	$(MPICXX) $(CXXFLAGS) -c MPI_Manager.cpp

MPI_Manager: MPI_Manager.o
	$(MPICXX) $(CXXFLAGS) -o MPI_Manager MPI_Manager.o
	
timingThread.o:
	$(CXX) $(CXXFLAGS) -c timingThread.cpp

timingThread: timingThread.o
	$(CXX) $(CXXFLAGS) -o timingThread timingThread.o

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -fr simple_loop.o
	-@rm -fr simple_loop
	-@rm -fr MPI_Manager.o
	-@rm -fr MPI_Manager
	-@rm -fr timingThread.o
	-@rm -fr timingThread
	
clearOUT:
	-@rm eni*.out
	-@rm mpi.out
	-@rm tmdt.out
	-@rm enix.out