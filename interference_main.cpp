
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <thread>
#include <ctime>
#include <chrono>

time_t getTime() {
	return time(NULL);
}

float rndNum(){
	return static_cast <float> (rand() % 10000) / 10000;
}

int main(int argc, char **argv)
{
	srand (time(NULL));
	printf("starting scaling_enigma");
	
	float time_fraction = .1;
	
	
	for(int a=1;a<argc;a++){
		time_fraction = atof(argv[a]); //TODO
	}


	float targetFractionMin = .1;//atof(argv[1]);
	float targetFractionMax = .1;//atof(argv[1]);

	if (targetFractionMin > 1) targetFractionMin = 1 / targetFractionMin;
	if (targetFractionMax > 1) targetFractionMax = 1 / targetFractionMax;
	if(targetFractionMax < targetFractionMin){} //TODO
	
	int runtime = 90; //in seconds
	bool indef = false;
	//int numThreads = 4;
	
	//TODO
	float step_length = 1.0;

	time_t initTime = getTime();
	int step = 0;
	
	
	while (indef || difftime(getTime(), initTime) < runtime) {
		time_t startTime = time(NULL);
		time_fraction = step_length * (targetFractionMin + rndNum() * (targetFractionMax - targetFractionMin));
		printf("starting step %d\tslow:%f\n", step++, time_fraction);

		const int calcScale = 1 << 10;
		double vector[calcScale];
		for (int i = 0; i < calcScale; i++)
			vector[i] = 1.0;
		int tmp = 0;


		while (difftime(getTime(), startTime) < time_fraction * step_length) {
			//scedule(static) 
			//omp_set_num_threads(numThreads);
			#pragma omp parallel for default(none) shared(vector, startTime, time_fraction)
			for (int i = 0; i < calcScale; i++)
			{
				for (int a = 0; a < calcScale; a++) {
					vector[i] = (vector[i] + vector[i]) * 3;
				}
			}
			tmp++;
		}
		printf("step done \ttime:%f \ttotal calcs:%d\n", difftime(getTime(), startTime), tmp);
    	

		int num_milliseconds = (int)(1000 * step_length * (1.0 - time_fraction));
		std::this_thread::sleep_for(std::chrono::milliseconds(num_milliseconds));
		printf("ending step \ttotal time: %f \ttime waited %d\n", difftime(getTime(), startTime), num_milliseconds);
    }
    return 0;
}