#include "functions.h"


void interference_function(int func, int scale){
	if(func == 1){
		pureCalculation(scale);
	} else {
		calculationMixed(scale);
	}
	
	
	return;
}

void calculationMixed(int sc){
	std::vector<double> vector(sc);
	for (int i = 0; i < sc; i++)
		vector[i] = 1.0;
	#pragma omp parallel for default(none) shared(vector, sc)
	for (int i = 0; i < sc; i++){
		for (int a = 0; a < sc; a++) {
			vector[i] = (i + 1.1) * a;
		}
	}
}


void pureCalculation(int sc){
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

void pureCalculationSingle(int sc){
	double x = 1;
	for (int a = 0; a < sc; a++){
		for (int b = 0; b < sc; b++) {
			x = (x + 1.1) * 1.1;
		}
	}
}