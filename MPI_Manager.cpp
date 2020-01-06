#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <ratio>
#include <vector>
#include <functional>

#include "mpi.h"

// rnd {0,1} 5-digits
float rndNum(){
	return static_cast <float> (rand() % 10000) / 10000;
}

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
	int tst = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("Starting things.\n");
	printf("%d, %d\n", rank, numtasks);

	for (int x=5;x>0;x--) {
		if (rank == 0) {
			tst++;
			
			
			std::vector<char> msg(numtasks);
			for(int a =0;a<numtasks;a++)
				msg[a] = '0';
			
			double affected = 0.5;
			int slow = (int)(numtasks * affected);
			int assigned = 0;
			printf("Assigning %d slows\n", slow);
			while(assigned<slow){
				int tmp = (int) (rndNum() * numtasks);
				if(msg[tmp]!='0'){
					msg[tmp]='s';
					tmp++;
				}
			}
			
			
			
			printf("0 Sending things\n");
			for(int i = 1;i<numtasks;i++){
				dest = i;
				outmsg = msg[i];
				MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
				
			}

		} else if (rank != 0) {			
			source = 0;
			MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
			if(inmsg=='0')
				printf("%d NOTHING\n", rank);
			else
				printf("%d slow %c\n", rank, inmsg);
		}



	}

	printf("done .\n");
	MPI_Get_count(&Stat, MPI_CHAR, &count);
	printf("Task %d: Received %d char(s) from task %d with tag %d \n", rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);


	MPI_Finalize();
}


