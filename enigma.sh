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
#SBATCH --time=00:04:00
#
#
# Args: matrix_size, output file, interfNodePercentage, interferenceSlow
#
#
# TODO allow 1,2,4,8 nodes


module load slurm_setup

export OMP_NUM_THREADS=28
export I_MPI_PIN_DOMAIN=auto
export I_MPI_PIN=1

echo "tasks " $SLURM_NTASKS
echo "args: " $@

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

#start interference in different thread
#chmod +x startInterference.sh
#./startInterference.sh $@ &

#mpiexec -n $SLURM_NTASKS ./MPI_Manager $3 $4 $5 &
mpiexec -n $SLURM_NTASKS $MATRIX_PATH $1 100 100 > $2 &


echo "all started, we done"
exit 0