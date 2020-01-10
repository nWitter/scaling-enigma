#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#SBATCH -o ./eni%j.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=mpp2
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=28
#SBATCH --time=00:03:00
#


echo "Testing TimedInterf"

chmod +x tmdCall.sh
chmod +x timingThread
chmod +x simple_loop

export OMP_NUM_THREADS=28
mpiexec -n 1 ./simple_loop > enix.out
mpiexec -n 1 ./timingThread > timed.out
#mpiexec -n 1 ./enigma_loop > eniy.out

echo "all started, we done"
exit 0