#!/bin/bash
##########################
#SBATCH --job-name=interference-test
#SBATCH -o ./eni%j.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --partition=mpp2_inter
#SBATCH --ntasks=2
#SBATCH --cpus-per-task=28
#SBATCH --time=00:04:00
#
#
# Args: matrix_size, output file, interfNodePercentage, interferenceSlow
#
#
# TODO allow 1,2,4,8 nodes


module load slurm_setup
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
export I_MPI_PIN_DOMAIN=node
export I_MPI_PIN=1

echo "tasks " $SLURM_NTASKS
echo "cores per task " $SLURM_CPUS_PER_TASK
echo "args: " $@

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

#start interference in different thread
#chmod +x startInterference.sh
#./startInterference.sh $@ &

mpiexec -n $SLURM_NTASKS ./MPI_Manager $3 $4 $5 &
#mpiexec -n $SLURM_NTASKS $MATRIX_PATH $1 100 100 &
if [ $SLURM_NTASKS == 2 ]; then
	echo "launch for 2 nodes"
	mpiexec -n 2 $MATRIX_PATH $1 100 100 > $2 &
fi

wait

echo "all started, we done"
exit 0