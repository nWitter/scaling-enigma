

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <thread>
#include <ctime>
#include <chrono>

time_t getTime() {
    /*struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return (double) time.tv_sec + ((double)time.tv_nsec)/1E9;
	 */
	return time(NULL);
}

int main(int argc, char **argv)
{
	float time_fraction = .5;//atof(argv[1]);


	float targetFractionMin = .5;//atof(argv[1]);
	if (targetFractionMin > 1) targetFractionMin = 1 / targetFractionMin;
	float targetFractionMax = .5;//atof(argv[1]);
	if (targetFractionMax > 1) targetFractionMax = 1 / targetFractionMax;

	int runtime = 10; //in seconds




	/*
	bool all_cores = true;
	if(time_fraction > 1.0) {
		all_cores = false;
		time_fraction -= 1.0;
	}
	if(all_cores)
		printf("all cores, time_fraction=%f\n, ", time_fraction);
	else
		printf("one core, time_fraction=%f\n", time_fraction);

		*/
	time_t initTime = getTime();
	int step = 0;


	double aNumber = 2;


    while(difftime(getTime(), initTime) < runtime) {
		printf("step%d\n", step++);


    	#pragma omp parallel
    	{
    		time_t startTime = time(NULL);
    		//if(omp_get_thread_num() == 0)
			//	printf("start time = %lf\n", start_time);
    		//if(all_cores || omp_get_thread_num() == 0) {
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

		printf("test %f\n", difftime(getTime(), initTime));

		int num_milliseconds = (int)(1000 * (1.0 - time_fraction));
		std::this_thread::sleep_for(std::chrono::milliseconds(num_milliseconds));
    }
    return 0;
}