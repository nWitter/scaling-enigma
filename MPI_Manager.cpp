#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <ratio>
#include <chrono>
#include <vector>
#include <functional>

#include "mpi.h"

typedef std::chrono::steady_clock Clock;
typedef std::chrono::milliseconds milliseconds;


// rnd {0,1} 5-digits
float rndNum(){
	return static_cast <float> (rand() % 10000) / 10000;
}

double tNow(Clock::time_point tZero){
	std::chrono::duration<double> d = Clock::now() - tZero;
	milliseconds m = std::chrono::duration_cast<milliseconds>(d);
	return m.count();
}

int main(int argc, char **argv)
{
	int intervalMillisec = 1000;
	
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

	final int bufferSize = 3;
	char* scatterBuffer = (char*)malloc(bufferSize * numtasks * sizeof(char));
	char inbuffer[bufferSize];
	
	
	for (int x=5;x>0;x--) {
		Clock::time_point t0 = Clock::now();
		
		if (rank == 0) {
			double affected = 0.5;
			int slow = (int)(numtasks * affected);
			int assigned = 0;
			
			std::vector<char> msg(numtasks);
			for(int a =0;a<numtasks* bufferSize;a++)
				scatterBuffer[a] = 'x';
			
			//test
			for(int a =numtasks;a<numtasks* bufferSize;a++)
				scatterBuffer[a] = '2';
			
			for(int a =numtasks*2;a<numtasks* bufferSize;a++)
				scatterBuffer[a] = '3';
			
		printf("%d ...\n", rank);
			
			if(numtasks>1){
			while(assigned<slow && false){
				if(affected<0||affected>1){
					printf("#error invalid number of affected nodes");
					break;
				}
				
				int tmp = (int) (rndNum() * (numtasks+1));
				if(scatterBuffer[tmp]=='0'){
					//TODO things
					scatterBuffer[tmp]='s';
					assigned++;
				}
			}
			}else if(affected >= 0.5){
				scatterBuffer[0] = '0';
			}
			
		printf("%d ...\n", rank);
			
			printf("#atmpt %d, actual slows %d\n", slow, assigned);
			
			for(int i = 1;i<numtasks;i++){
				dest = i;
				//MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
				printf("#0 Sending %c to %d\n", outmsg, i);
			}
			
			printf("#SCATTER\n");
			// scatter blocking??
			MPI_Scatter(scatterBuffer,bufferSize,MPI_CHAR,inbuffer,bufferSize,MPI_CHAR,0,MPI_COMM_WORLD);
			
			
			int num_milliseconds = tNow(t0);
			int sleep = intervalMillisec - num_milliseconds;
			printf("#time %d, sleeping %d\n", num_milliseconds, sleep);
			std::this_thread::sleep_for(milliseconds(sleep));

		} else if (rank != 0) {
			//MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
			MPI_Scatter(scatterBuffer,bufferSize,MPI_CHAR,inbuffer,bufferSize,MPI_CHAR,0,MPI_COMM_WORLD);
		}


		
		
			if(inbuffer[0] == '0')
				printf("--%d NOTHING\n", rank);
			else if (inbuffer[0] == '1')
				printf("--%d slow %c\n", rank, inbuffer[0]);
			else
				printf("--%d GOT SOMETHING %c %c\n", rank, inbuffer[0], inbuffer[1], inbuffer[1]);
		//TODO do interference here

	}

	printf("done .\n");
	MPI_Get_count(&Stat, MPI_CHAR, &count);
	printf("Task %d: Received %d char(s) from task %d with tag %d \n", rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);

	free(scatterBuffer);
	MPI_Finalize();
}


