#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdlib.h>
#include <omp.h>
#include <vector>
#include <chrono>

typedef std::chrono::steady_clock Clock;
typedef std::chrono::milliseconds milliseconds;

void interference_function(int func, int scale);

void calculationMixed(int sc);
void pureCalculation(int sc);
void pureCalculationSingle(int sc);

double tNow(Clock::time_point tZero);


#endif