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
typedef std::chrono::nanoseconds nanosec;

const int ENI_SLEEP = -1;
const int ENI_INTERFERE = 1;
const int ENI_NULL = 0;

// rnd {0,1} 5-digits
float rndNum(){
	return static_cast <float> (rand() % 10000) / 10000;
}

int main(int argc, char **argv)
{
	const int intervalNanosec = 1000000;
	const int duration = 5;
	
	if(argc>10)
		argv[10]++;
		//nonsense
	

	int numtasks, rank, dest, source, rc, count, tag = 1;
	char inmsg, outmsg = 'x';
	MPI_Status Stat;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("Starting: ranks %d, tasks %d\n", rank, numtasks);

	const int bufferSize = 3;
	int* scatterBuffer = (int*)malloc(bufferSize * numtasks * sizeof(int));
	int inbuffer[bufferSize];
	
	
	for (int x=0;x<duration;x++) {
		Clock::time_point t0 = Clock::now();
		
		// communication between ranks
		// assigning ranks
		if (rank == 0) {
			
			//TODO pattern
			
			
			double affected = 0.5;
			int interf_number = (int)(numtasks * affected);
			int interf_assigned = 0;
			
			std::vector<char> msg(numtasks);
			for(int a = 0; a < numtasks * bufferSize; a++)
				scatterBuffer[a] = ENI_NULL;
			
			// designate interfering ranks
			if(numtasks > 1){
				while(interf_assigned < interf_number){
					if(affected < 0|| affected > 1){
						printf("#error invalid number of affected nodes");
						break;
					}
					
					int rnd = (int) (rndNum() * (numtasks+1)) * bufferSize;
					if(scatterBuffer[rnd] == ENI_NULL){
						scatterBuffer[rnd] = ENI_INTERFERE;
						interf_assigned++;
					}
				}
				//printf("#atmpt %d, actual slows %d\n", interf_number, interf_assigned);
			}else if(affected >= 0.5){
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

		
		printf("--%d state: %d ; %d \n", rank, inbuffer[0], inbuffer[1]);
		// interference
		if(inbuffer[0] == ENI_INTERFERE){
			//TODO
			printf("\t--%d \t interf\n", rank);
			float time_fraction = 1.0;
			float step_length = 1.0;
			int function_type = 1;
			int calc_scale = 1 << 10;
			
			
			interferenceLoop(time_fraction, step_length, function_type, calc_scale);			
		}

		// fill intervall
		nanosec ns = timeInterv(t0);
		int remainingInterv = intervalNanosec - ns.count();
		if(remainingInterv > 1){
			printf("\t--%d #time %f, sleeping %d\n", rank, static_cast<double>(ns.count()), remainingInterv);
			std::this_thread::sleep_for(nanosec(remainingInterv));
		}
		printf("\t--%d passed %f\n", rank, (double)ns.count());
	}

	printf("done .\n");
	MPI_Get_count(&Stat, MPI_CHAR, &count);
	printf("Task %d: Received %d char(s) from task %d with tag %d \n", rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);

	free(scatterBuffer);
	MPI_Finalize();
}


