#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#SBATCH -o ./eni%j.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=mpp2
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:03:00
#


echo "Testing TimedInterf"

chmod +x tmdCall.sh
chmod +x timingThread
chmod +x enigma_loop

export OMP_NUM_THREADS=1
mpiexec -n 1 ./enigma_loop > enix.out

echo "all started, we done"
exit 0