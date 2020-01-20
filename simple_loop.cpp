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
	const int calc_scale = 1 << 8;	
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

	int tmp = interference_function(functionType, calcScale, t0, activeTime);
	
	printf("\t activeTime %f\t target %d %f\t cnt %d\t\n", static_cast<double>(timeInterv(t0).count()), l, static_cast<double>(activeTime.count()), tmp);
}