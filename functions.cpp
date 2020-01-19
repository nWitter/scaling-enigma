#include "functions.h"


void interference_function(int func, int scale){
	if(func == 1){
		functionCalc(scale);
	} else if(func == 2){
		functionMemory(scale);
	} else {
		functionMixed(scale);
	}
	
	return;
}

void functionMixed(int sc){
	const int size = 1 << 10;
	int vector[size];
	for (int i = 0; i < size; i++)
		vector[i] = 1.0;
	#pragma omp parallel for default(none) shared(vector, sc)
	for (int i = 0; i < sc; i++){
		for (int a = 0; a < sc; a++) {
			vector[i] = (i + 1.1) * a;
		}
	}
}


void functionCalc(int sc){
	const int size = 1 << 10;
	int vector[size];
	for (int i = 0; i < size; i++)
		vector[i] = 1.0;
	#pragma omp parallel for default(none) shared(vector, sc)
	for (int a = 0; a < size; a++){
		for (int b = 0; b < sc; b++) {
			vector[a] = (vector[a] + 1.1) * 1.1;
		}
	}
}

void functionMemory(int sc){
	const int size = 1 << 10;
	int vector[size];
	for (int i = 0; i < size; i++)
		vector[i] = 1.0;
	#pragma omp parallel for default(none) shared(vector, sc)
	for (int a = 0; a < size; a++){
		for (int b = 0; b < sc; b++) {
			int t = (a + size/2) % size;
			vector[a] = vector[t];
		}
	}
}

double tNow(Clock::time_point tZero){
	std::chrono::duration<double> d = Clock::now() - tZero;
	milliseconds m = std::chrono::duration_cast<milliseconds>(d);
	return m.count();
}

void functionCalcSingle(int sc){
	double x = 1;
	for (int a = 0; a < sc; a++){
		for (int b = 0; b < sc; b++) {
			x = (x + 1.1) * 1.1;
		}
	}
}