#!/bin/bash
#########################
#
MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

./MPI_Manager $@ &

# launch program
if [$SLURM_NTASKS == 2]
then
	$MATRIX_PATH $1 100 100 > $2 &
fi
if [$SLURM_NTASKS == 4]
then
	$MATRIX_PATH $1 100 100 100 100 > $2 &
fi
exit