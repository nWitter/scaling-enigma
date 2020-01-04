#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#SBATCH -o ./eni%j.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=mpp2
#SBATCH --ntasks=2 
#SBATCH --cpus-per-task=7
#SBATCH --time=0-00:02:00
#

module load slurm_setup
export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1
#export VT_PCTRACE=1

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main
MATRIX_SIZE=$0

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

echo "Initiating"
echo "tasks " $SLURM_NTASKS ", cpuPerTask " $SLURM_CPUS_PER_TASK
chmod +x startInterference.sh
mpiexec -n $SLURM_NTASKS ./startInterference.sh $MATRIX_PATH $MATRIX_SIZE

exit 0