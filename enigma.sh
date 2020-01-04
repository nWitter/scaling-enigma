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
#SBATCH --time=0-00:02:00
#

module load slurm_setup
export OMP_NUM_THREADS=28
export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1
#export VT_PCTRACE=1

echo "running mpi"
chmod +x run.sh
mpiexec -n $SLURM_NTASKS ./run.sh 600

exit 0