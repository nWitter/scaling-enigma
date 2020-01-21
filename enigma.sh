#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#SBATCH -o ./eni%j.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=mpp2
#SBATCH --ntasks=2
#SBATCH --cpus-per-task=28
#SBATCH --time=00:03:00

module load slurm_setup
export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
#export VT_PCTRACE=1
chmod +x startInterference.sh

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

echo "tasks " $SLURM_NTASKS ", cpuPerTask " $SLURM_CPUS_PER_TASK

mpiexec -n $SLURM_NTASKS ./MPI_Manager $3 &
sleep 20
mpiexec -n $SLURM_NTASKS $MATRIX_PATH $1 > $2 &
wait

echo "all started, we done"
exit 0