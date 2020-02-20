#include "simple_loop.h"
#include "functions.h"

typedef std::vector<double> d_vec;

typedef std::chrono::steady_clock Clock;
typedef std::chrono::microseconds microsec;

int interferenceLoop(int functionType, int interfereMicrosec, int calcScale){
	Clock::time_point t0 = Clock::now();
	microsec activeTime = microsec(interfereMicrosec);

	int tmp = interference_function(functionType, calcScale, t0, activeTime);
	int r = timeInterv(t0).count();
	return tmp;
}