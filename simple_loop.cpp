#include "simple_loop.h"
#include "functions.h"

typedef std::vector<double> d_vec;

typedef std::chrono::steady_clock Clock;
typedef std::chrono::nanoseconds nanosec;

int oldmain(int argc, char **argv)
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
	int l = stepLength * timeFraction * 1000000;
	nanosec activeTime = nanosec(l);
	printf("starting step\t%f \t%f \t%f\n", timeFraction, stepLength, activeTime.count());

	int tmp = 0;
	while (timeInterv(t0) < (activeTime)) {
		interference_function(functionType, calcScale);
		tmp++;
	}
}

