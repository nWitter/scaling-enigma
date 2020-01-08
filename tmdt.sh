#!/bin/bash
#########################
#
#SBATCH --job-name=scaling-test
#SBATCH -o ./eni%j.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=mpp2
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --time=00:03:00
#


echo "Testing TimedInterf"
chmod +x timingThread

export OMP_NUM_THREADS=4
mpiexec -n 1 ./timingThread > tmdt.out

echo "all started, we done"
exit 0