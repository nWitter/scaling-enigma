#!/bin/bash
#########################
#

module load slurm_setup
export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1
#export VT_PCTRACE=1

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main
MATRIX_SIZE=600

chmod +x startInterference.sh

#1
echo "starting 1 core"
salloc --partition=mpp2_inter --ntasks=1 --cpus-per-task=1 --time=2
echo "allocated 1 core"
export OMP_NUM_THREADS=1
mpiexec -n $SLURM_NTASKS ./startInterference.sh $MATRIX_PATH 200 > mat1.out


#2
echo "starting 2 cores"
salloc --partition=mpp2_inter --ntasks=2 --cpus-per-task=1 --time=2
echo "allocated 2 cores"
export OMP_NUM_THREADS=2
mpiexec -n $SLURM_NTASKS ./startInterference.sh $MATRIX_PATH 200 > mat2.out