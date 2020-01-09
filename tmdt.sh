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

chmod +x tmdCall.sh
chmod +x timingThread
chmod +x enigma_loop

export OMP_NUM_THREADS=4
#mpiexec -n 1 -o ./tmdCall.sh
mpiexec -n 1 --overbook ./enigma_loop > enix.out &
mpiexec -n 1 --overbook ./timingThread > tmdt.out &

echo "all started, we done"
exit 0