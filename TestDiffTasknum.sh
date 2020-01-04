#!/bin/bash
#########################
#

module load slurm_setup
export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1
#export VT_PCTRACE=1

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main
MATRIX_SIZE=600


#1
echo "starting 1core"
salloc --partition=mpp2_inter --ntasks=1 --cpus-per-task=1 --time=2
export OMP_NUM_THREADS=1
mpiexec -n $SLURM_NTASKS ./startInterference.sh $MATRIX_PATH 200 > mat1.out


#2
echo "starting 2cores"
salloc --partition=mpp2_inter --ntasks=2 --cpus-per-task=1 --time=2
export OMP_NUM_THREADS=2
mpiexec -n $SLURM_NTASKS ./startInterference.sh $MATRIX_PATH 200 > mat2.out