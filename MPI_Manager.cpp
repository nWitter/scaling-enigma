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




const int instance_hard_limit = 10; // avoid errors, no technical reasons
const int intervalBase = 1000000; // one second in microsec
const int calc_scale = 1 << 10;



// rnd {0,1} 5-digits
float rndNum(){
	return static_cast <float> (rand() % 10000) / 10000;
}


/*

-a {n} || --affected {n}
-ar {n} {m} || --affectedRnd {n} {m}
TODO add parcentage values

-i {n} || --intervall {n}
-ir {n} {m} || --intervallRnd {n} {m}
the timefraction per step the interference program is running (inbetween 0 - 1)
e.g. -intervall 0.5 runs interference for 1s in each 2s timestep(default)

TODO multiple instances if greater 1 (max 10)

policy: default random, last assigned policy takes priority
-rr || --round_robin
-f || --fixed_nodes

-function {n}
used function, available 0 processing heavy, 1 memory, 2 mixed TODO condfirm numbers

-step_length {n}
multiplier to length of the timestep, 1s; default 2 -> timestep of 2s

-t {n}
number of steps executed, default runs without time limit

TODO
ir
function
stepl

*/

int main(int argc, char **argv)
{
	// configurable by args
	int designation_policy = 0;
	

	float affected_num = 0.5;
	float affected_max = 1;
	bool affected_rnd = false;
	bool affected_flat = true;
	
	float interferingNodes = 0.5;
	float interferingNodesMax = 1;
	bool intervall_rnd = false;
	
	float time_fraction = 0.5; // TODO
	
	float step_length = 2.0;
	int function_type = 1;
	
	//
	int interference_duration = -1;
	bool interference_infinite = true;
	
	// args	
	for (int a = 0; a < argc; ++a){
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
			if(0 < x && interference_duration < 100){
				//TODO remove limit
				interference_duration = x;
			} else {
				interference_duration = 1 << 12;
			}
		}
	}
	
	for (int i = 0; i < argc; ++i) { 
        std::string arg = argv[i];
		if(i+1 <= argc && (arg == "-a" || arg == "--affected")){
			float x = atof(argv[i++]);
			//TODO viability check
			affected_num = x;
			i++;
		} else if(i+2 <= argc && (arg == "-ar" || arg == "--affectedRnd")){
			float x = atof(argv[i++]);
			float y = atof(argv[i++]);
			//TODO viability check
			affected_num = x;
			affected_max = y;
			affected_rnd = true;
			i+=2;
		} else if(i+1 <= argc && (arg == "-i" || arg == "--intervall")){
			float x = atof(argv[i++]);
			//TODO viability check
			affected_num = x;
			i++;
		} else if(arg == "-rr" || arg == "--round_robin"){
			designation_policy = POLICY_ROUNDROBIN;
		} else if(arg == "-f" || arg == "--fixed_nodes"){
			designation_policy = POLICY_FIXED;
		} else if(i+1 <= argc && (arg == "-t" || arg == "--time")){
			int x = atoi(argv[i++]);
			if(x > 0){
				interference_duration = x;
				interference_infinite = false;
			}
			i++;
		}
    }
	
	
	
	
	int step_time = intervalBase * step_length;
	int interfere_time = step_time * time_fraction;
	
	//mpi
	int numtasks, rank, dest, source, rc, count, tag = 1;
	char inmsg, outmsg = 'x';
	MPI_Status Stat;

	//mpi buffer
	const int bufferSize = 2;
	int* scatterBuffer = (int*)malloc(bufferSize * numtasks * sizeof(int));
	int inbuffer[bufferSize];
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("Starting: rank %d, tasks %d\n", rank, numtasks);
	
	//
	for (int x = 0; interference_infinite || x < interference_duration; x++) {
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


