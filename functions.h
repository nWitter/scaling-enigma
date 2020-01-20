#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdlib.h>
#include <omp.h>
#include <vector>
#include <chrono>

typedef std::chrono::steady_clock Clock;
typedef std::chrono::milliseconds milliseconds;
typedef std::chrono::nanoseconds nanoseconds;
typedef std::chrono::duration<float> dur_f;

void interference_function(int func, int scale);

void functionMixed(int sc);
void functionCalc(int sc);
void functionMemory(int sc);

void functionCalcSingle(int sc);

double tNow(Clock::time_point tZero);
dur_f timeInterv(Clock::time_point tZero);


#endif