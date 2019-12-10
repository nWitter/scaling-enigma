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
srun -n1 -w tux[1,0] ./interference > out

#
# run program
#

srun -n2 -w tux[1,1] ./$MATRIX_PATH/main 500 20 20 > mat

echo end
exit 0