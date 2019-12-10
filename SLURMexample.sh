#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#
#SBATCH --nodes=2
#SBATCH --time=0-00:03:00
#


#
#SBATCH --cpus-per-task=4
#
#

echo initiate things
export OMP_PROC_BIND=close
export OMP_PLACES=cores
export OMP_NUM_THREADS=20

export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1


export VT_PCTRACE=1

MATRIX_PATH=../chameleon-apps/applications/matrix_example

echo run
mpiexec -n 1 -o ./interference > out

#
# run program
#

mpiexec -n 2 -o ./$MATRIX_PATH/main 500 20 20 > mat

echo end
exit 0