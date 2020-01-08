#include <thread>
#include <pthread.h>
#include <iostream>
#include <cstring>
#include <signal.h>
#include <chrono>

typedef std::chrono::steady_clock Clock;
typedef std::chrono::milliseconds milliseconds;

int tNow(Clock::time_point tZero){
	std::chrono::duration<double> d = Clock::now() - tZero;
	Millisec m = std::chrono::duration_cast<Millisec>(d);
	return m.count();
}


volatile std::sig_atomic_t processing_interrupted = false;

int main(int argc, char **argv) {


	if(argc>10)
		argv[10]++;
		//nonsense

    // Do something for a long time.
	printf("gogo");
	for(int a = 10;a<200;a+=10){
		//theory: maximize sceduled time-working????
		std::this_thread::sleep_for(Millisec(1));
	printf("zzz done");
		
		
		Clock::time_point t0 = Clock::now();
    processing_interrupted = false;
	
    std::signal( SIGINT, & interrupt_processing );
	calculationMixed(a);
    std::signal( SIGINT, SIG_DFL );
	
	printf("-%d time: %d: ", a, tNow(t0));
	if(processing_interrupted)
		printf("INTERR");
	
	
	
	
	
	}

    return 0;
}

void calculationMixed(int scale){
	d_vec vector(scale);
	for (int i = 0; i < scale; i++)
		vector[i] = 1.0;
	for (int i = 0; i < scale; i++){
		for (int a = 0; a < scale; a++) {
			vector[a] = (vector[a] + 1) * 3;
		}
	}
}

