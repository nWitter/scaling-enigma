#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdlib.h>
#include <omp.h>
#include <vector>
#include <chrono>

typedef std::chrono::steady_clock Clock;
typedef std::chrono::nanoseconds nanosec;

void interference_function(int func, int scale, Clock::time_point tZero, nanosec activeT);

void functionMixed(int* v, int x);
void functionCalc(int* v, int x);
void functionMemory(int* v, int x);

void functionCalcSingle(int sc);

nanosec timeInterv(Clock::time_point tZero);


#endif