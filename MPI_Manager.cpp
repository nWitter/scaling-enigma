#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <ratio>
#include <vector>
#include <functional>

#include "mpi.h"


int main(int argc, char **argv)
{
	printf("Initiating MPI.\n");


	if(argc>10)
		argv[10]++;
		//nonsense
	

	int numtasks, rank, dest, source, rc, count, tag = 1;
	char inmsg, outmsg = 'x';
	MPI_Status Stat;
	char intrfStatus = '0';

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("Starting things.\n");

	//while (true) {
		if (rank == 0) {
			
			for(int i = 1;i<numtasks;i++){
				dest = i;
				outmsg = '1';
				MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
			}

		} else if (rank != 0) {
			source = 0;
			MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
			
			printf("Got: " + inmsg +"\n");
		}



	//}

	printf("done .\n");
   MPI_Get_count(&Stat, MPI_CHAR, &count);
   printf("Task %d: Received %d char(s) from task %d with tag %d \n",
          rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);


	MPI_Finalize();
}


