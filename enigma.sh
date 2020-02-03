#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#SBATCH -o ./eni%j.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=mpp2
#SBATCH --nodes=2
#SBATCH --cpus-per-node=28
#SBATCH --time=00:03:00

# Args: matrix_size, output file, interfNodePercentage, interferenceSlow

module load slurm_setup
export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
chmod +x startProgram.sh

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main


echo "tasks " $SLURM_NTASKS ", cpuPerTask " $SLURM_CPUS_PER_TASK
echo "arguments: " $@
if [ $3 != -1 ]; then
	echo "launch interf"
	mpiexec -n $SLURM_NTASKS ./MPI_Manager $3 $4 &
else
	echo "PROGRAM only"
fi
mpiexec -n $SLURM_NTASKS $MATRIX_PATH $1 > $2 &
#mpiexec -n $SLURM_NTASKS startProgram.sh $@
#srun -n$SLURM_NTASKS ./MPI_Manager $3 &
#srun -n$SLURM_NTASKS --nice=10000 ./startInterference.sh $SLURM_NTASKS $MATRIX_PATH $1 $2 > eni1.out &
wait

echo "all started, we done"
exit 0