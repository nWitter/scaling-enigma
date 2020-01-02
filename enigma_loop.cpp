
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <thread>
#include <time.h>
#include <ctime>
#include <chrono>
#include <ratio>
#include <vector>
#include <functional>

//#include "ScalingEnigmaThread.cpp"



typedef std::vector<double> d_vec;
typedef std::vector<bool> b_vec; 

typedef std::chrono::steady_clock Clock;
typedef std::chrono::milliseconds Millisec;
//typedef std::chrono::duration_cast DurationCast;
//typedef std::chrono::duration Durati;


float rndNum(){
	return static_cast <float> (rand() % 10000) / 10000;
}

void calculationMixed(int scale){
	d_vec vector[scale];
	for (int i = 0; i < scale; i++)
		vector[i] = 1.0;
	for (int i = 0; i < scale; i++){
		for (int a = 0; a < scale; a++) {
			vector[a] = (vector[a] + 1) * 3;
		}
	}
}


int main(int argc, char **argv)
{
	srand (time(NULL));
	printf("Initiating\n");
	
	

	float time_fraction = 1;
	float targetFractionMin = 1;
	float targetFractionMax = targetFractionMin;
	float step_length = 1.0;
	
	for(int a=1;a<argc;a++){
		if(a ==1)
			targetFractionMin = atof(argv[a]);
		if(a==2)
			targetFractionMax = atof(argv[a]);
	}
	
	
	if (targetFractionMin > 1) targetFractionMin = 1 / targetFractionMin;
	if (targetFractionMax > 1) targetFractionMax = 1 / targetFractionMax;
	if(targetFractionMax < targetFractionMin){} //TODO
	
	
	//TODO

	Clock::time_point tStart = Clock::now();
	int step = 0;
	
	printf("Starting Interference:\nStep%f\nSlow Min/Max: %f, %f\n\n", step_length, targetFractionMin, targetFractionMin);

	
	while (true) {
		Clock::time_point t0 = Clock::now();
		time_fraction = 1; //step_length * (targetFractionMin + rndNum() * (targetFractionMax - targetFractionMin));
		printf("starting step %d\tslow:%f\n", step++, time_fraction);

		const int calcScale = 1 << 10;
		int tmp = 0;

		#pragma omp parallel for default(none) shared(tmp)
		while ((std::chrono::duration_cast<std::chrono::duration<double>(Clock::now() - t0)).count()
			< time_fraction * step_length) {
			//scedule(static) 
			calculationMixed(calcScale);
			tmp++;
			
		}
		printf(" -step done \ttime:%d \ttotal calcs:%d\n", std::chrono::duration_cast<std::chrono::duration<double>(Clock::now() - t0)).count(), tmp);
    	
		if(time_fraction != 1){
			int num_milliseconds = std::chrono::duration_cast<std::chrono::duration<double>(Clock::now() - tStart)).count();
			std::this_thread::sleep_for(Millisec(step_length - (num_milliseconds / 1000.0));
			printf("ending step \ttotal time: %d \ttime waited %d\n", std::chrono::duration_cast<std::chrono::duration<double>(Clock::now() - t0)).count(), num_milliseconds);
		}
    }
	

	std::this_thread::sleep_for(Millisec((int)(1000 * step_length * 10)));
   return 0;
}