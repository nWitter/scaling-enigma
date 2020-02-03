#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#SBATCH -o ./eni%j.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=mpp2
#SBATCH --nodes=2
#SBATCH --tasks-per-node=1
#SBATCH --time=00:03:00

# Args: matrix_size, output file, interfNodePercentage, interferenceSlow

module load slurm_setup
export OMP_NUM_THREADS=28

export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1
chmod +x startProgram.sh

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main


echo "tasks " $SLURM_NTASKS ", cpuPerTask " $SLURM_CPUS_PER_TASK

mpiexec -n $SLURM_NTASKS startProgram.sh $@

echo "all started, we done"
exit 0