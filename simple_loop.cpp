#include "simple_loop.h"
#include "functions.h"

typedef std::vector<double> d_vec;

typedef std::chrono::steady_clock Clock;
typedef std::chrono::microseconds microsec;

int oldmain(int argc, char **argv)
{
	printf("Initiating Interference.\n");
	
	float time_fraction = 1;
	float step_length = 1.0;
	int function_type = 1;
	const int calc_scale = 1 << 8;	
	int duration = 60;
	
	//needs update
	int old = 0;
	
	if(argc>10)
		argv[10]++;
		//it does things
	
	printf("\n--Starting Interference:\nSteplength: %f, Slow %f\n\n", step_length, time_fraction);
	for (int x = 0; x < duration; x++) {
		interferenceLoop(function_type, old, calc_scale);
    }
	return 0;
}

void interferenceLoop(int functionType, int interfereMicrosec, int calcScale){
	Clock::time_point t0 = Clock::now();
	microsec activeTime = microsec(interfereMicrosec);

	int tmp = interference_function(functionType, calcScale, t0, activeTime);
	int r = timeInterv(t0).count();
	printf("\t active time %d\t rate %f\t cnt %d\t\n", r, (float)activeTime.count(), tmp);
}