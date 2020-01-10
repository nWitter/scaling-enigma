CXX      := -c++
MPICXX   := mpiCC
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -fopenmp
LDFLAGS  := -L/usr/lib -lstdc++ -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := enigma_loop
INCLUDE  := -Iinclude/
SRC      :=                      \
   $(wildcard src/module1/*.cpp) \
   $(wildcard src/module2/*.cpp) \
   $(wildcard src/module3/*.cpp) \
   $(wildcard src/*.cpp)         \

OBJECTS := $(SRC:%.cpp=$%.o)

all: simple_loop.o simple_loop MPI_Manager.o MPI_Manager timingThread.o timingThread

simple_loop.o: simple_loop.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -std=gnu++11 -o $@ -c $<

functions.o: functions.cpp functions.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -std=gnu++11 -o $@ -c $<
	
simple_loop: simple_loop.o functions.o
	$(CXX) $(CXXFLAGS) $(INCLUDE) -std=gnu++11 -o $@ $<

MPI_Manager.o: MPI_Manager.cpp
	$(MPICXX) $(CXXFLAGS) $(INCLUDE) -std=gnu++11 -o $@ -c $<

MPI_Manager: MPI_Manager.o
	$(MPICXX) $(CXXFLAGS) $(INCLUDE) -std=gnu++11 -o $@ $<
	
timingThread.o: timingThread.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -std=gnu++11 -o $@ -c $<

timingThread: timingThread.o
	$(CXX) $(CXXFLAGS) $(INCLUDE) -std=gnu++11 -o $@ $<

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