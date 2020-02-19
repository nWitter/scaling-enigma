#!/bin/bash
#########################
#

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
export I_MPI_PIN_DOMAIN=node
export I_MPI_PIN=1
export I_MPI_ADJUST_BARRIER=1

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

./MPI_Manager $3 $4 &
$MATRIX_PATH $1 100 100 > $2 &


exit