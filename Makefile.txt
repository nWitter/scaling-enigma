CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

SRCS=interference_main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: interference_main

interference_main: $(OBJS)
    $(CXX) $(LDFLAGS) -o interference_main $(OBJS) $(LDLIBS)

	
clean:
    $(RM) $(OBJS)
