#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <ratio>
#include <functional>

#include "mpi.h"
#include "simple_loop.h"

typedef std::chrono::steady_clock Clock;
typedef std::chrono::milliseconds milliseconds;

const char ENI_SLEEP = 's';
const char ENI_INTERFERE = 'i';
const char ENI_NULL = ' ';


// rnd {0,1} 5-digits
float rndNum(){
	return static_cast <float> (rand() % 10000) / 10000;
}


int main(int argc, char **argv)
{
	const int intervalMillisec = 1000;
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
	char* scatterBuffer = (char*)malloc(bufferSize * numtasks * sizeof(char));
	char inbuffer[bufferSize];
	
	
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
					
					int tmp = (int) (rndNum() * (numtasks+1));
					if(scatterBuffer[tmp] == ENI_NULL){
						scatterBuffer[tmp] = ENI_INTERFERE;
						interf_assigned++;
					}
				}
			}else if(affected >= 0.5){
				scatterBuffer[0] = ENI_INTERFERE;
			} else {
				scatterBuffer[0] = ENI_SLEEP;
			}			
			printf("#atmpt %d, actual slows %d\n", interf_number, interf_assigned);
			
			
			MPI_Scatter(scatterBuffer, bufferSize, MPI_CHAR, inbuffer, bufferSize, MPI_CHAR, 0, MPI_COMM_WORLD);
			
		} else if (rank != 0) {
			//MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
			MPI_Scatter(scatterBuffer, bufferSize, MPI_CHAR, inbuffer, bufferSize, MPI_CHAR, 0, MPI_COMM_WORLD);
		}

		
		printf("--%d msg %c %c %c\n", rank, inbuffer[0], inbuffer[1], inbuffer[2]);
		

		
		// interference
		if(inbuffer[0] == ENI_INTERFERE){
			//TODO
			float time_fraction = 1.0;
			float step_length = 1.0;
			int function_type = 1;
			int calc_scale = 1 << 12;
			
			
			interferenceLoop(time_fraction, step_length, function_type, calc_scale);
			
		} else{
			int tim = tNow(t0);
			int ms = intervalMillisec - tim;
			printf("#time %d, sleeping %d\n", tim, ms);
			std::this_thread::sleep_for(milliseconds(ms));
		}
	}

	printf("done .\n");
	MPI_Get_count(&Stat, MPI_CHAR, &count);
	printf("Task %d: Received %d char(s) from task %d with tag %d \n", rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);

	free(scatterBuffer);
	MPI_Finalize();
}


