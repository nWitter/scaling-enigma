#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#SBATCH -o ./e%j.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=mpp2
#SBATCH --ntasks=2 
#SBATCH --cpus-per-task=7
#SBATCH --time=0-00:01:00
#

module load slurm_setup
export OMP_NUM_THREADS=28
export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1
#export VT_PCTRACE=1

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

chmod +x run.sh
source ./run.sh $MATRIX_PATH 600 out1
wait

exit 0