#!/bin/bash
#########################
#

if [ $1 != -1 ]; then
	echo "launch interf"
	mpiexec -n $SLURM_NTASKS ./MPI_Manager $3 $4
else
	echo "PROGRAM only"
fi
exit