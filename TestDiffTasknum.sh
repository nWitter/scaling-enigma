#!/bin/bash
#########################
#

for ii in {1..10}
do
	echo "starting n=1 t=4"
	sbatch --ntasks=1 --cpus-per-task=4 --time=5 enigma.sh 700 n1t4e1-$ii.out 1
done
#echo "starting n=1 t=7"
#sbatch --ntasks=1 --cpus-per-task=7 --time=5 enigma.sh 700 n1t7e1.out 1

#echo "starting n=1 t=14"
#sbatch --ntasks=1 --cpus-per-task=14 --time=5 enigma.sh 700 n1t14e1.out 1

#1
#echo "starting 1 core"
#salloc --partition=mpp2_inter --ntasks=1 --cpus-per-task=1 --time=2
#echo "allocated 1 core"
#export OMP_NUM_THREADS=1
#mpiexec -n $SLURM_NTASKS ./startInterference.sh $MATRIX_PATH 200 > mat1.out
#exit 0

exit 0