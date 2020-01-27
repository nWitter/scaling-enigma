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

# Args: matrix_size, output file, interference slow

module load slurm_setup
export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
chmod +x startInterference.sh

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

#export VT_PCTRACE=1

echo "tasks " $SLURM_NTASKS ", cpuPerTask " $SLURM_CPUS_PER_TASK

mpiexec -n $SLURM_NTASKS ./MPI_Manager $3 $4 > eni0.out&
#mpiexec -n $SLURM_NTASKS $MATRIX_PATH $1 > $2 &
#srun -n$SLURM_NTASKS ./MPI_Manager $3 &
srun -n$SLURM_NTASKS --nice=10000 ./startInterference.sh $SLURM_NTASKS $MATRIX_PATH $1 $2 >eni1.out &
wait

echo "all started, we done"
exit 0