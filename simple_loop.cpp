#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <thread>
#include <chrono>
#include <ratio>
#include <vector>
#include <functional>

#include "functions.h"

typedef std::vector<double> d_vec;

typedef std::chrono::steady_clock Clock;
typedef std::chrono::milliseconds Millisec;

int tNow(Clock::time_point tZero){
	std::chrono::duration<double> d = Clock::now() - tZero;
	Millisec m = std::chrono::duration_cast<Millisec>(d);
	return m.count();
}

float rndNum(){
	return static_cast <float> (rand() % 10000) / 10000;
}

void calculationMixed(int scale){
	d_vec vector(scale);
	for (int i = 0; i < scale; i++)
		vector[i] = 1.0;
	#pragma omp parallel for default(none) shared(vector, scale)
	for (int i = 0; i < scale; i++){
		for (int a = 0; a < scale; a++) {
			vector[i] = (i + 1.1) * a;
		}
	}
}


void pureCalculation(int scale){
	double x = 1;	
	#pragma omp parallel for default(none) shared(x, scale)
	for (int a = 0; a < scale; a++){
		for (int b = 0; b < scale; b++) {
			x = (x + 1.1) * 1.1;
		}
	}
}

void pureCalculationSingle(int scale){
	double x = 1;
	for (int a = 0; a < scale; a++){
		for (int b = 0; b < scale; b++) {
			x = (x + 1.1) * 1.1;
		}
	}
}



int main(int argc, char **argv)
{
	printf("Initiating Interference.\n");
	
	float time_fraction = 1;
	float step_length = 1.0;
	
	if(argc>10)
		argv[10]++;
		//nonsense
	
	printf("\n--Starting Interference:\nSteplength: %f, Slow %f\n\n", step_length, time_fraction);
	for (int x = 0; x < 20; x++) {
		Clock::time_point t0 = Clock::now();
		time_fraction = step_length * time_fraction;
		//printf("starting step, slow:%f\n", time_fraction);

		const int calcScale = 1 << 12;	
		int tmp = 0;
		while (tNow(t0) < (time_fraction * 1000)) {
			//choose function
			calculationMixed(calcScale);
			interference_function(0);
			tmp++;
		}		
		printf(" -step done, \ttime:%d\tcalcs: %d\n", tNow(t0), tmp);
    	
		if(false){//time_fraction < 1){
			int num_milliseconds = tNow(t0);
			std::this_thread::sleep_for(Millisec((int)(step_length * 1000 - num_milliseconds)));
			printf("ending step \ttotal time: %d \ttime waited %d\n", tNow(t0), num_milliseconds);
		}
    }
	return 0;
}
