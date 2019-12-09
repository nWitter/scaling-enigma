

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
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

int main(int argc, char **argv)
{
	srand (time(NULL));
	printf("starting scaling_enigma");
	
	float time_fraction = .5;//atof(argv[1]);
	
	for(int a=0;a<argc;a++){
		time_fraction = atof(argv[a]); //TODO
	}
	


	float targetFractionMin = .5;//atof(argv[1]);
	if (targetFractionMin > 1) targetFractionMin = 1 / targetFractionMin;
	float targetFractionMax = .5;//atof(argv[1]);
	if (targetFractionMax > 1) targetFractionMax = 1 / targetFractionMax;

	if(targetFractionMax < targetFractionMin) //TODO
	
	int runtime = 10; //in seconds
	bool indef = false;
	
	//TODO
	//float time_step = 1.0;

	time_t initTime = getTime();
	int step = 0;

	


	
    while(indef || difftime(getTime(), initTime) < runtime) {
    	time_t startTime = time(NULL);
		targetFractionMin = targetFractionMin + rndNum() * (targetFractionMax - targetFractionMin);
		

		printf("step%d with slow %f\n", step++, time_fraction);
    	#pragma omp parallel
    	{
	    	while(difftime(getTime(), startTime) < time_fraction) {
		    		const int vecLen = 1 << 10;
		    		int iteration_count = 1 << 10;
					double vector[vecLen];
					for(int i = 0; i < vecLen; i++)
						vector[i] = 1.0;
					for(int j = 0; j < iteration_count; j++)
						for(int i = 0; i < vecLen; i++)
							vector[i] = (vector[i]+ vector[i])*3;
								
		    }
	    	
	    	//#pragma omp barrier
    		//if(omp_get_thread_num() == 0)
			//	printf("wait start time = %lf\n", getTime()-start_time);
	    	
    		//if(omp_get_thread_num() == 0)
			//	printf("wait end time = %lf\n", getTime()-start_time);
    	}

		//printf("test %f\n", difftime(getTime(), initTime));

		int num_milliseconds = (int)(1000 * (1.0 - time_fraction));
		std::this_thread::sleep_for(std::chrono::milliseconds(num_milliseconds));
    }
    return 0;
}