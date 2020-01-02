#!/bin/bash
#########################
#

mpiexec -n $SLURM_NTASKS ./interference &
mpiexec -n $SLURM_NTASKS ./$0 $1 > $2 &



