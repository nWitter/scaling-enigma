#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#
#SBATCH --nodes=2
#SBATCH --tasks-per-nodes=1
#SBATCH --time=0-00:03:00
#
#
#

echo initiate things
export OMP_PROC_BIND=close
export OMP_PLACES=cores
#export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1


export VT_PCTRACE=1

MATRIX_PATH=../chameleon-apps/applications/matrix_example

echo run
mpirun -np 1 ./interference > out

#
# run program
#

mpirun -np 2 ./$MATRIX_PATH/main 200 > mat

echo end
exit 0