#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#SBATCH -o ./eni%j.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=mpp2
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=28
#SBATCH --time=00:04:00

module load slurm_setup
export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1
#export VT_PCTRACE=1

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

echo "Initiating"
echo "tasks " $SLURM_NTASKS ", cpuPerTask " $SLURM_CPUS_PER_TASK
chmod +x startInterference.sh

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
mpiexec -n $SLURM_NTASKS ./MPI_Manager $2 &
mpiexec -n $SLURM_NTASKS $MATRIX_PATH > $1 &
wait

echo "all started, we done"
exit 0