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
			interference_function(1, calcScale);
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

