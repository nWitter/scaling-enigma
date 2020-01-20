#include "functions.h"

const int vector_size = 1 << vector_scale;

int interference_function(int func, int scale, Clock::time_point tZero, nanosec activeT){
	int vector[vector_size];
	int cnt = 0;
	for (int i = 0; i < vector_size; i++)
		vector[i] = 1.0;
	#pragma omp parallel for default(none) shared(vector, tZero, activeT, func, scale)
	for (int a = 0; a < size; a++){
		while (timeInterv(tZero) < (activeT)) {
			for (int b = 0; b < scale; b++) {
				if(func == 1){
					functionCalc(vector, a);
				} else if(func == 2){
					functionMemory(vector, a);
				} else {
					functionMixed(vector, a);
				}
			}
			cnt++;
		}
	}
	
	return cnt;
}

// 0 default
void functionMixed(int* v, int x){
	int t = (x + vector_size/2) % vector_size;
	v[x] = (v[x] + x) * v[t];
}

// 1
void functionCalc(int* v, int x){
	v[x] = v[x] + 1.1) * 1.1;
}

// 2
void functionMemory(int* v, int x){
	int t = (x + vector_size/2) % vector_size;
	v[x] = v[t];
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