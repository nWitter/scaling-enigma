#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#SBATCH -o ./eni%j.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=mpp2
#

module load slurm_setup
export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1
#export VT_PCTRACE=1

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

echo "Initiating"
echo "tasks " $SLURM_NTASKS ", cpuPerTask " $SLURM_CPUS_PER_TASK
chmod +x startInterference.sh

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
#mpiexec -n $SLURM_NTASKS ./startInterference.sh $MATRIX_PATH $@
mpiexec -n $SLURM_NTASKS ./enigma_loop 

exit 0