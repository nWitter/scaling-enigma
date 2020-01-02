#!/bin/bash
#########################
#

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

mpiexec -n $SLURM_NTASKS ./interference &
mpiexec -n $SLURM_NTASKS ./$MATRIX_PATH $@ > out &	#0 $1 > $2 &



