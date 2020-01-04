#!/bin/bash
#########################
#

echo "starting n=1 t=7"
sbatch --ntasks=1 --cpus-per-task=7 enigma.sh 600 n1t7.out


echo "starting n=2 t=7"
sbatch --ntasks=2 --cpus-per-task=7 enigma.sh 600 n2t7.out

#1
#echo "starting 1 core"
#salloc --partition=mpp2_inter --ntasks=1 --cpus-per-task=1 --time=2
#echo "allocated 1 core"
#export OMP_NUM_THREADS=1
#mpiexec -n $SLURM_NTASKS ./startInterference.sh $MATRIX_PATH 200 > mat1.out
#exit 0

exit 0