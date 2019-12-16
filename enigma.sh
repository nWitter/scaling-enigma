#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#SBATCH -o ./%j.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=mpp2
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=28
#SBATCH --time=0-00:02:00
#

echo initiate
module load slurm_setup
export OMP_NUM_THREADS=28

#export OMP_PROC_BIND=close
#export OMP_PLACES=cores

export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1

#export VT_PCTRACE=1


MATRIX_PATH=../chameleon-apps/applications/matrix_example

echo run
mpiexec -n 1 ./interference > out &

#
# run program
#

mpiexec -n 1 ./$MATRIX_PATH/main 300 > mat &
wait

echo end
exit 0