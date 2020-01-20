#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#SBATCH -o ./eni%j.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=mpp2
#SBATCH --ntasks=4
#SBATCH --cpus-per-task=4
#SBATCH --time=00:03:00
#


echo "Testing MPIsetup"
export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
chmod +x MPI_Manager

mpiexec -n $SLURM_NTASKS ./MPI_Manager > mpi.out

echo "all started, we done"
exit 0