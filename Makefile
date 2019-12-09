CXX      := -c++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -fopenmp
LDFLAGS  := -L/usr/lib -lstdc++ -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := interference
INCLUDE  := -Iinclude/
SRC      :=                      \
   $(wildcard src/module1/*.cpp) \
   $(wildcard src/module2/*.cpp) \
   $(wildcard src/module3/*.cpp) \
   $(wildcard src/*.cpp)         \

OBJECTS := $(SRC:%.cpp=$%.o)

all: interference.o

interference.o: interference_main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -std=gnu++11 -o $@ -c $<



debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -fr main.o