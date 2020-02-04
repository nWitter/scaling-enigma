#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <ratio>
#include <functional>

#include "mpi.h"
#include "simple_loop.h"
#include "functions.h"

typedef std::chrono::steady_clock Clock;
typedef std::chrono::microseconds microsec;

const int ENI_SLEEP = -1;
const int ENI_INTERFERE = 1;
const int ENI_NULL = 0;












// rnd {0,1} 5-digits
float rndNum(){
	return static_cast <float> (rand() % 10000) / 10000;
}


/*

args:
 1 interfNodePercentage 
 2 interferenceSlow

-assigning policy:
0 random
1 round-robin

*/

int main(int argc, char **argv)
{
	const int intervalBase = 1000000;
	const int calc_scale = 1 << 14;
	
	const int duration = 30;
	float step_length = 2.0;
	
	float interferingNodes = 0.5;
	float time_fraction = 0.5;
	int function_type = 1;
	
	
	for (int a = 1; a <= argc; a++){
		if(a == 1){
			int x = atoi(argv[a]);
			if(x == 0){
				interferingNodes = 0;
			} else if(x == 1){
				interferingNodes = 1;
			}
			printf("arg: %d\n", x);
		} else if(a == 2){
			float x = atof(argv[a]);
			if(0 <= x && x <= 1){
				time_fraction = x;
			}
		} else if(a == 3){
			int x = atoi(argv[a]);
			if(0 < x){
				duration = x;
			} else {
				duration = 1 << 12;
			}
		}
	}
	
	int step_time = intervalBase * step_length;
	int interfere_time = step_time * time_fraction;
	
	//mpi
	int numtasks, rank, dest, source, rc, count, tag = 1;
	char inmsg, outmsg = 'x';
	MPI_Status Stat;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("Starting: rank %d, tasks %d\n", rank, numtasks);

	const int bufferSize = 2;
	int* scatterBuffer = (int*)malloc(bufferSize * numtasks * sizeof(int));
	int inbuffer[bufferSize];
	
	
	for (int x = 0; x < duration; x++) {
		Clock::time_point t0 = Clock::now();
		
		// communication between ranks
		// assigning ranks
		if (rank == 0) {
			
			//TODO
			
			int interf_number = (int)(numtasks * interferingNodes);
			int interf_assigned = 0;
			
			std::vector<char> msg(numtasks);
			for(int a = 0; a < numtasks * bufferSize; a++)
				scatterBuffer[a] = ENI_NULL;
			
			// designate interfering ranks
			if(numtasks > 1 && interferingNodes > 0){
				for(int a = 0; a < interf_number; a++){
					if(interferingNodes < 0 || interferingNodes > 1){
						printf("#error invalid number of affected nodes");
						break;
					}					
					int rnd = (int) (rndNum() * (numtasks+1)) * bufferSize;
					int b = 0;
					//test
					rnd = 1;
					while(scatterBuffer[rnd * bufferSize] != ENI_NULL && b < a){						
						rnd = (rnd + 1) % numtasks;
						b++;
					}
					scatterBuffer[rnd * bufferSize] = ENI_INTERFERE;
				}
			}else if(interferingNodes >= 0.5){
				scatterBuffer[0] = ENI_INTERFERE;
			} else {
				scatterBuffer[0] = ENI_SLEEP;
			}
			for(int a = 0; a < numtasks * bufferSize; a += bufferSize){
				if(scatterBuffer[a] == ENI_NULL){
					scatterBuffer[a] = ENI_SLEEP;
				}
			}
			
			MPI_Scatter(scatterBuffer, bufferSize, MPI_INT, inbuffer, bufferSize, MPI_INT, 0, MPI_COMM_WORLD);
			
		} else if (rank != 0) {
			MPI_Scatter(scatterBuffer, bufferSize, MPI_INT, inbuffer, bufferSize, MPI_INT, 0, MPI_COMM_WORLD);
		}
		
		Clock::time_point t1 = Clock::now();
		
		//printf("--%d state: %d ; %d \n", rank, inbuffer[0], inbuffer[1]);
		// interference
		// initially run on all nodes to start OMP
		if(inbuffer[0] == ENI_INTERFERE || x == 0){
			//time_fraction = 1.0;
			//step_length = 1.0;
			//function_type = 1;
			
			int f = interferenceLoop(function_type, interfere_time, calc_scale);	
			printf("\t--%d \t interf\t cnt: %d\n", rank, f);		
		}

		// fill intervall
		microsec ns = timeInterv(t0);
		int remainingInterv = step_time - ns.count();
		if(remainingInterv > 1){
			printf("\t--%d \t sleep\n", rank);
			std::this_thread::sleep_for(microsec(remainingInterv));
		}
		
		
		int nsTotal = timeInterv(t0).count();
		microsec ns2 = std::chrono::duration_cast<microsec>(t1 - t0);
		int nsWait = ns2.count();
		
		printf("--%d\t n: %d,\t time %d,\t sleept %d,\t waited %d\n", rank, x, nsTotal, remainingInterv, nsWait);
	}

	printf("%d done .\n", rank);
	//MPI_Get_count(&Stat, MPI_CHAR, &count);
	//printf("Task %d: Received %d char(s) from task %d with tag %d \n", rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);

	free(scatterBuffer);
	MPI_Finalize();
}


