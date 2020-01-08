#include <thread>
#include <chrono>
#include <atomic>
#include <vector>
#include <csignal>

typedef std::chrono::steady_clock Clock;
typedef std::chrono::milliseconds milliseconds;

volatile std::atomic<bool> processing_interrupted;

extern "C" void interrupt_processing(int) {
    processing_interrupted = true;
}

int tNow(Clock::time_point tZero){
	std::chrono::duration<double> d = Clock::now() - tZero;
	milliseconds m = std::chrono::duration_cast<milliseconds>(d);
	return m.count();
}

void pureCalculationSingle(int scale){
	double x = 1;
	for (int a = 0; a < scale; a++){
		for (int b = 0; b < scale; b++) {
			x = (x + 1.1) * 1.1;
		}
	}
}

int main(int argc, char **argv) {


	if(argc>10)
		argv[10]++;
		//nonsense

    // Do something for a long time.
	printf("gogo");
	for(int a = 2;a<(1<<10);a*=2){
		//theory: maximize sceduled time-working????
		std::this_thread::sleep_for(milliseconds(1));
	printf("zzz done");
		
		
		Clock::time_point t0 = Clock::now();
    processing_interrupted = false;
	
    std::signal(SIGSTOP, &interrupt_processing);
	pureCalculationSingle(a);
    std::signal(SIGSTOP, SIG_DFL);
	
	printf("-%d time: %d: \n", a, tNow(t0));
	if(processing_interrupted){
		printf("INTERR");
		break;
	}		
	
	
	
	
	}

    return 0;
}


