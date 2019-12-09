#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#
#SBATCH --nodes=1
#
#
#SBATCH --time=0-00:01:00

export OMP_NUM_THREADS=4
export OMP_PROC_BIND=true
export OMP_PLACES=cores

export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1

export OMP_NUM_THREADS=${SLURM_CPUS_PER_TASK}

export OMP_PLACES=cores
export OMP_PROC_BIND=close

MATRIX_PATH = ./chameleon-apps/applications/matrix_example/main

echo run
mpirun -np 1 ./a.out

echo end

exit 0