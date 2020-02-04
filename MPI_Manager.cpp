#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <ratio>
#include <functional>
#include <string>
#include <vector>

#include "mpi.h"
#include "simple_loop.h"
#include "functions.h"

typedef std::chrono::steady_clock Clock;
typedef std::chrono::microseconds microsec;

const int ENI_SLEEP = -1;
const int ENI_INTERFERE = 1;
const int ENI_NULL = 0;

const int POLICY_RANDOM = 10;
const int POLICY_ROUNDROBIN = 11;
const int POLICY_FIXED = 12;




const int instance_hard_limit = 10; // purely to avoid errors
const int intervalBase = 1000000; // one second in microsec
const int calc_scale = 1 << 14;



// rnd {0,1} 5-digits
float rndNum(){
	return static_cast <float> (rand() % 10000) / 10000;
}


/*

-affected {n}
-affectedRnd {n} {m}
TODO add flat values

-intervall {n}
-intervallRnd {n} {m}
the timefraction per step the interference program is running (inbetween 0 - 1) TODO multiple instances if greater 1 (max 10)
e.g. -intervall 0.5 runs interference for 1s in each 2s timestep(default)

policy: default random, last assigned policy takes priority
-round_robin
-fixed_nodes

-function {n}
used function, available 0 processing heavy, 1 memory, 2 mixed TODO condfirm numbers

-step_length {n}
multiplier to length of the timestep, 1s; default 2 -> timestep of 2s

*/

int main(int argc, char **argv)
{
	
	// configurable by args
	int designation_policy = 0;
	
	bool intervall_rnd = false;
	float interferingNodes = 0.5;

	bool affected_rnd = false;
	bool affected_flat = false;
	float time_fraction = 0.5; // TODO
	float affected_num = 0.5;
	float affected_max = 1;
	
	float step_length = 2.0;
	int function_type = 1;
	

	//
	int duration = 30;
	
	
	
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
			if(0 < x && duration < 100){
				//TODO remove limit
				duration = x;
			} else {
				duration = 1 << 12;
			}
		}
	}
	
	
	for (int i = 1; i =< argc; i++) { 
        std::string arg = argv[i];
		if(arg == "-affected"){
			float x = atof(argv[i++]);
			//TODO viability check
			affected_num = x;
		} else if (false){
		
		
		//TODO
	designation_policy = 0;
	
	intervall_rnd = false;
	interferingNodes = 0.5;

	affected_rnd = false;
	affected_flat = false;
	affected_num = 0.5;
	affected_max = 1;
	
	step_length = 2.0;
	function_type = 1;
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

	//mpi buffer
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
		// interference
		// initially run on all nodes to start OMP
		if(inbuffer[0] == ENI_INTERFERE || x == 0){			
			std::thread interf_thread(interferenceLoop, function_type, interfere_time, calc_scale);	
			interf_thread.detach();			
			printf("\t--%d \t interf\n", rank);		
		}

		// fill intervall
		microsec ns = timeInterv(t0);
		int remainingInterv = step_time - ns.count();
		if(remainingInterv > 1){
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


