#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <ratio>
#include <functional>
#include <string>
#include <vector>
#include <iostream>

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
nodes slowed simultaniously

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

-step {n} || --step_length {n}
set length of the timestep in seconds; default: 1; -step 0.5 -> timestep of 0.5s

-t {n} || --time {n}
number of steps executed, default runs without time limit

TODO function
TODO stepl
TODO random seed
TODO run timed version


*/

int main(int argc, char **argv)
{
	// configurable by args
	int designation_policy = 0;
	int policy_round_robin_var = 0;
	
	float affected_num = 1;
	float affected_num_max = 1;
	bool affected_rnd = false;
	
	float intervall_time = 0.5;
	float intervall_time_max = 1;
	bool intervall_time_rnd = false;
	
	float step_length = 1.0;
	int function_type = 1;
	bool use_timed_loop = false;
	
	//
	int interference_duration = -1;
	bool interference_infinite = true;
	
	for (int i = 1; i <= argc; i++) {
        std::string arg = argv[i];
		std::cout << "reading arg " << i << ": ";
		if(i+1 <= argc && (arg == "-a" || arg == "--affected")){
			std::cout << " affected ";
			float x = atof(argv[++i]);
			if(x > 0)
				affected_num = x;
			else
				std::cout << "--- ignored arg: negative" << x;
		} else if(i+2 <= argc && (arg == "-ar" || arg == "--affectedRnd")){
			std::cout << " affectedRnd ";
			float x = atof(argv[++i]);
			float y = atof(argv[++i]);
			if(x > 0 && y > 0) {
				affected_num = x;
				affected_num_max = y;
				affected_rnd = true;
			} else
				std::cout << "--- ignored arg: negative" << x << y;
		} else if(i+1 <= argc && (arg == "-i" || arg == "--intervall")){
			std::cout << " intervall ";
			float x = atof(argv[++i]);
			if(x > 0)
				intervall_time = x;
			else
				std::cout << "--- ignored arg: negative" << x;
		} else if(i+2 <= argc && (arg == "-ir" || arg == "--intervallRnd")){
			std::cout << " intervallRnd ";
			float x = atof(argv[++i]);
			float y = atof(argv[++i]);
			if(x > 0 && y > 0) {
				intervall_time = x;
				intervall_time_max = y;
				intervall_time_rnd = true;
			} else
				std::cout << "--- ignored arg: negative" << x << y;
		} else if(i+1 <= argc && (arg == "-step" || arg == "--step_length")){
			std::cout << " step_length ";
			float x = atof(argv[++i]);
			if(x > 0)
				step_length = x;
			else
				std::cout << "--- ignored arg: negative" << x;
		} else if(arg == "-rr" || arg == "--round_robin"){
			designation_policy = POLICY_ROUNDROBIN;
		} else if(arg == "-f" || arg == "--fixed_nodes"){
			designation_policy = POLICY_FIXED;
		} else if(i+1 <= argc && (arg == "-t" || arg == "--time")){
			std::cout << " time ";
			int x = atoi(argv[++i]);
			if(x > 0){
				interference_duration = x;
				interference_infinite = false;
			} else
				std::cout << "--- ignored arg: negative" << x;
		} else {
			std::cout << "no valid string";
		}
		std::cout << "/n";
    }
	
	//mpi
	int numtasks, rank, dest, source, rc, count, tag = 1;
	char inmsg, outmsg = 'x';
	MPI_Status Stat;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::cout << "Starting: rank" << rank << ", tasks " << numtasks << "/n";

	//mpi buffer
	const int bufferSize = 2;
	int* scatterBuffer = (int*)malloc(bufferSize * numtasks * sizeof(int));
	int inbuffer[bufferSize];
	
	//
	for (int x = 0; interference_infinite || x < interference_duration; x++) {
		Clock::time_point t0 = Clock::now();
		
		// communication between ranks
		// assigning ranks
		if (rank == 0) {
			// affected nodes in time step
			int affected_final;
			if(affected_rnd){
				affected_final = affected_num + (int)((affected_num_max - affected_num) * rndNum());
			} else {
				affected_final = affected_num;
			}
			
			if(affected_final > numtasks)
				affected_final = numtasks;
			
			// interference time: final active time in microseconds
			float intervall_final;
			if(intervall_time_rnd){
				intervall_final = (intervall_time + (intervall_time_max - intervall_time) * rndNum());
			} else {
				intervall_final = intervall_time;
			}
			intervall_final *=  intervalBase * step_length;
			
			for(int a = 0; a < numtasks; a++){
				scatterBuffer[a * bufferSize] = ENI_SLEEP;
				scatterBuffer[a * bufferSize + 1] = 0;
			}
			
			// designate active ranks for the next timestep according to policy
			if(designation_policy == POLICY_FIXED){
				for(int a = 0; a < affected_final; a++){
					scatterBuffer[a] = ENI_INTERFERE;
					scatterBuffer[a + 1] = intervall_final;
				}				
			} else if(designation_policy == POLICY_ROUNDROBIN){
				for(int a = 0; a < affected_final; a++){
					int b = (policy_round_robin_var + a) % numtasks;
					scatterBuffer[b] = ENI_INTERFERE;
					scatterBuffer[b + 1] = intervall_final;
				}
				policy_round_robin_var = (policy_round_robin_var + affected_final) % numtasks;
			} else if(designation_policy == POLICY_RANDOM){
				for(int a = 0; a < affected_final; a++){
					int rnd = (int) (rndNum() * (numtasks+1));
					
					// shift if selected node is already interfering
					for(int b = 0; b < a; a++){
						int c = (rnd + b) * bufferSize;
						if(scatterBuffer[c] != ENI_INTERFERE){						
							scatterBuffer[c] = ENI_INTERFERE;
							scatterBuffer[c + 1] = intervall_final;							
						}
					}
				}
			}else {
				scatterBuffer[0] = ENI_INTERFERE;
			}
			
			//send
			MPI_Scatter(scatterBuffer, bufferSize, MPI_INT, inbuffer, bufferSize, MPI_INT, 0, MPI_COMM_WORLD);
		} else if (rank != 0) {
			MPI_Scatter(scatterBuffer, bufferSize, MPI_INT, inbuffer, bufferSize, MPI_INT, 0, MPI_COMM_WORLD);
		}
		
		Clock::time_point t1 = Clock::now();
		std::cout << "\t--" << rank << " " << x;
		// interference
		// initially run on all nodes to start OMP
		if(inbuffer[0] == ENI_INTERFERE || x == 0){
			if(!use_timed_loop){
				std::thread interf_thread(interferenceLoop, function_type, inbuffer[1], calc_scale);	
				interf_thread.detach();			
				std::cout << "\t interfed";
			} else {
				
			}
		}
		std::cout << "\n";
		
		// wait for rest of the timestep
		microsec ns = timeInterv(t0);
		int remainingInterv = intervalBase * step_length - ns.count();
		if(remainingInterv > 1){
			std::this_thread::sleep_for(microsec(remainingInterv));
		}
		
		if(false){
			int nsTotal = timeInterv(t0).count();
			microsec ns2 = std::chrono::duration_cast<microsec>(t1 - t0);
			int nsWait = ns2.count();
			printf("--%d\t n: %d,\t time %d,\t sleept %d,\t waited %d\n", rank, x, nsTotal, remainingInterv, nsWait);
		}
	}
	
	free(scatterBuffer);
	MPI_Finalize();
}


