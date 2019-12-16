#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <thread>
#include <ctime>
#include <chrono>

#include <stdio>

#include <pthread.h>
#include <sched.h>

//http://www.yonch.com/tech/82-linux-thread-priority
void set_realtime_priority() {
     int ret;
     // We'll operate on the currently running thread.
     pthread_t this_thread = pthread_self();

     // struct sched_param is used to store the scheduling priority
     struct sched_param params;

     // We'll set the priority to the maximum.
     params.sched_priority = sched_get_priority_max(SCHED_FIFO);
     std::cout << "Trying to set thread realtime prio = " << params.sched_priority << std::endl;
 
     // Attempt to set thread real-time priority to the SCHED_FIFO policy
     ret = pthread_setschedparam(this_thread, SCHED_FIFO, &params);
     if (ret != 0) {
         // Print the error
         std::cout << "Unsuccessful in setting thread realtime prio" << std::endl;
         return;     
     }
     // Now verify the change in thread priority
     int policy = 0;
     ret = pthread_getschedparam(this_thread, &policy, &params);
     if (ret != 0) {
         std::cout << "Couldn't retrieve real-time scheduling paramers" << std::endl;
         return;
     }
 
     // Check the correct policy was applied
     if(policy != SCHED_FIFO) {
         std::cout << "Scheduling is NOT SCHED_FIFO!" << std::endl;
     } else {
         std::cout << "SCHED_FIFO OK" << std::endl;
     }
 
     // Print thread scheduling priority
     std::cout << "Thread priority is " << params.sched_priority << std::endl; 
}





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
	
	

	float time_fraction = .5;
	float targetFractionMin = 5;//atof(argv[1]);
	float targetFractionMax = targetFractionMin;//atof(argv[1]);

	int runtime = 60; //in seconds
	bool indef = false;
	int numThreads = 28;
	
	for(int a=1;a<argc;a++){
		if(a ==1)
			targetFractionMin = atof(argv[a]);
		if(a==2)
			runtime = atoi(argv[a]);
	}
	
	
	if (targetFractionMin > 1) targetFractionMin = 1 / targetFractionMin;
	if (targetFractionMax > 1) targetFractionMax = 1 / targetFractionMax;
	if(targetFractionMax < targetFractionMin){} //TODO
	
	
	//TODO
	float step_length = 1.0;

	time_t initTime = getTime();
	int step = 0;
	
	
	while (indef || difftime(getTime(), initTime) < runtime) {
		time_t startTime = time(NULL);
		set_realtime_priority();
		time_fraction = step_length * (targetFractionMin + rndNum() * (targetFractionMax - targetFractionMin));
		printf("starting step %d\tslow:%f\n", step++, time_fraction);

		const int calcScale = 1 << 10;
		double vector[calcScale];
		for (int i = 0; i < calcScale; i++)
			vector[i] = 1.0;
		int tmp = 0;


		while (difftime(getTime(), startTime) < time_fraction * step_length) {
			//scedule(static) 
			#pragma omp parallel for default(none) shared(vector, startTime, time_fraction, numThreads) num_threads(numThreads)
			for (int i = 0; i < calcScale; i++)
			{
				for (int a = 0; a < calcScale; a++) {
					vector[a] = (vector[a] + vector[a]) * 3;
				}
			}
			tmp++;
		}
		printf("step done \ttime:%f \ttotal calcs:%d\n", difftime(getTime(), startTime), tmp);
    	
		if(time_fraction != 1){
			int num_milliseconds = (int)(1000 * step_length * (1.0 - time_fraction));
			std::this_thread::sleep_for(std::chrono::milliseconds(num_milliseconds));
			printf("ending step \ttotal time: %f \ttime waited %d\n", difftime(getTime(), startTime), num_milliseconds);
		}
    }
    return 0;
}