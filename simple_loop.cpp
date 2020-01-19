#include "simple_loop.h"

typedef std::vector<double> d_vec;

typedef std::chrono::steady_clock Clock;
typedef std::chrono::milliseconds milliseconds;

int tNow(Clock::time_point tZero){
	std::chrono::duration<double> d = Clock::now() - tZero;
	milliseconds m = std::chrono::duration_cast<milliseconds>(d);
	return m.count();
}

int main(int argc, char **argv)
{
	printf("Initiating Interference.\n");
	
	float time_fraction = 1;
	float step_length = 1.0;
	int function_type = 1;
	const int calc_scale = 1 << 12;	
	int duration = 60;
	
	if(argc>10)
		argv[10]++;
		//it does things
	
	printf("\n--Starting Interference:\nSteplength: %f, Slow %f\n\n", step_length, time_fraction);
	for (int x = 0; x < duration; x++) {
		interferenceLoop(time_fraction, step_length, function_type, calc_scale);
    }
	return 0;
}

void interferenceLoop(float timeFraction, float stepLength, int functionType, int calcScale){
	Clock::time_point t0 = Clock::now();
	int activeTime = stepLength * timeFraction  * 1000;
	printf("starting step,\tslow:%f\tlength:%f\n", timeFraction, stepLength);

	int tmp = 0;
	while (tNow(t0) < (activeTime)) {
		interference_function(functionType, calcScale);
		tmp++;
	}
	
	if(timeFraction < 1){
		int tim = tNow(t0);
		int ms = milliseconds((int)(stepLength * 1000 - tim));
		std::this_thread::sleep_for(ms);
		printf("ending step \ttotal time: %d \ttime waited %d\n", tNow(t0), tim);
	}
}

