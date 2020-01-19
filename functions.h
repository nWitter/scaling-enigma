#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdlib.h>
#include <omp.h>
#include <vector>
#include <chrono>

void interference_function(int func, int scale);

void calculationMixed(int sc);
void pureCalculation(int sc);
void pureCalculationSingle(int sc);

double tNow(Clock::time_point tZero);


#endif