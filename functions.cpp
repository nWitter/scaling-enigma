#include "functions.h"

const int vector_scale = 10;

int interference_function(int func, int scale, Clock::time_point tZero, nanosec activeT){
	const int size = 1 << vector_scale;
	int vector[size];
	int cnt = 0;
	for (int i = 0; i < size; i++)
		vector[i] = 1.0;
	#pragma omp parallel for default(none) shared(vector, sc, tZero, activeT, size, scale)
	for (int a = 0; a < size; a++){
		while (timeInterv(tZero) < (activeT)) {
			for (int b = 0; b < sc; b++) {
				if(func == 1){
					functionCalc(vector, size, scale);
				} else if(func == 2){
					functionMemory(vector, size, scale);
				} else {
					functionMixed(vector, size, scale);
				}
			}
			cnt++;
		}
	}
	
	return cnt;
}

// 0 default
void functionMixed(int* v, int s, int sc){
	int t = (a + s/2) % s;
	v[a] = (v[a] + a) * v[t];
}

// 1
void functionCalc(int* v, int s, int sc){
	vector[a] = vector[a] + s) * 1.1;
}

// 2
void functionMemory(int* v, int s, int sc){
	int t = (a + s/2) % s;
	v[a] = v[t];
}

nanosec timeInterv(Clock::time_point tZero){
	nanosec d = Clock::now() - tZero;
	return d;
}

void functionCalcSingle(int sc){
	double x = 1;
	for (int a = 0; a < sc; a++){
		for (int b = 0; b < sc; b++) {
			x = (x + 1.1) * 1.1;
		}
	}
}