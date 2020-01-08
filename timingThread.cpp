#include <thread>
#include <chrono>
#include <atomic>
#include <vector>
#include <csignal>

typedef std::chrono::steady_clock Clock;
typedef std::chrono::milliseconds milliseconds;

volatile std::atomic<bool> processing_interrupted;


int tNow(Clock::time_point tZero){
	std::chrono::duration<double> d = Clock::now() - tZero;
	milliseconds m = std::chrono::duration_cast<milliseconds>(d);
	return m.count();
}

void calculationMixed(int scale){
	std::vector<double> vector(scale);
	for (int i = 0; i < scale; i++)
		vector[i] = 1.0;
	for (int i = 0; i < scale; i++){
		for (int a = 0; a < scale; a++) {
			vector[a] = (vector[a] + 1) * 3;
		}
	}
}

int main(int argc, char **argv) {


	if(argc>10)
		argv[10]++;
		//nonsense

    // Do something for a long time.
	printf("gogo");
	for(int a = 10;a<200;a+=10){
		//theory: maximize sceduled time-working????
		std::this_thread::sleep_for(milliseconds(1));
	printf("zzz done");
		
		
		Clock::time_point t0 = Clock::now();
    processing_interrupted = false;
	
    std::signal(SIGSTOP, &processing_interrupted);
	calculationMixed(a);
    std::signal(SIGSTOP, SIG_DFL);
	
	printf("-%d time: %d: ", a, tNow(t0));
	if(processing_interrupted)
		printf("INTERR");
	
	
	
	
	
	}

    return 0;
}


