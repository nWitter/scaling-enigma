#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#SBATCH -o ./enigma.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --export=NONE
#SBATCH --clusters=mpp2
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=28
#SBATCH --time=0-00:02:00
#

#
#

echo initiate
#module load slurm_setup
export OMP_NUM_THREADS=28

export OMP_PROC_BIND=close
export OMP_PLACES=cores

export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1

export VT_PCTRACE=1



echo run
mpiexec -n $SLURM_NTASKS ./interference > out &

#
# run program
#

MATRIX_PATH=../chameleon-apps/applications/matrix_example
mpiexec -n $SLURM_NTASKS ./$MATRIX_PATH/main 500 > mat &
wait

echo end
exit 0