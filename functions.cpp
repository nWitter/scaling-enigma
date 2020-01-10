#include "functions.h"


void interference_function(int func, int scale){
	if(func == 1){
		pureCalculation(scale);
	} else {
		calculationMixed(scale);
	}
	
	
	
	return;
}

void calculationMixed(int s){
	d_vec vector(s);
	for (int i = 0; i < s; i++)
		vector[i] = 1.0;
	#pragma omp parallel for default(none) shared(vector, s)
	for (int i = 0; i < s; i++){
		for (int a = 0; a < s; a++) {
			vector[i] = (i + 1.1) * a;
		}
	}
}


void pureCalculation(int s{
	const int size = 1 << 10;
	int vector[size];
	for (int i = 0; i < size; i++)
		vector[i] = 1.0;
	#pragma omp parallel for default(none) shared(x, s)
	for (int a = 0; a < size; a++){
		for (int b = 0; b < s; b++) {
			vector[a] = (vector[a] + 1.1) * 1.1;
		}
	}
}

void pureCalculationSingle(int scale){
	double x = 1;
	for (int a = 0; a < scale; a++){
		for (int b = 0; b < scale; b++) {
			x = (x + 1.1) * 1.1;
		}
	}
}