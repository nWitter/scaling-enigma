#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#SBATCH -o ./eni%j.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=mpp2
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --time=00:03:00
#


echo "Testing MPIsetup"
echo "tasks " $SLURM_NTASKS ", cpuPerTask " $SLURM_CPUS_PER_TASK
chmod +x MPI_Manager

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
mpiexec -n $SLURM_NTASKS ./MPI_Manager > mpi.out

echo "all started, we done"
exit 0