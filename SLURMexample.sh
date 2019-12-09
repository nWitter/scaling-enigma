#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#
#SBATCH --nodes=1
#SBATCH --time=0-00:00:10
#
#
#

echo initiate things
export OMP_PROC_BIND=close
export OMP_PLACES=cores
export OMP_NUM_THREADS=${SLURM_CPUS_PER_TASK}

export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1


#MATRIX_PATH = ./chameleon-apps/applications/matrix_example/main

echo run
mpirun -np 1 ./interference.o > out

#
# run program
#


echo end
exit 0