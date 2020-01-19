#ifndef SIMPLE_LOOP
#define SIMPLE_LOOP

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <thread>
#include <ratio>
#include <functional>


void interferenceLoop(float timeFraction, float stepLength, int functionType, int calcScale);


#endif