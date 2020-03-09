#!/bin/bash
#########################
#

mkdir -p output
chmod +x enigma.sh


	sbatch --ntasks=4 --cpus-per-task=28 ./enigma.sh 1000 output/rr.out -a 1 -i 1 -rr --duration 30
	sbatch --ntasks=4 --cpus-per-task=28 ./enigma.sh 1000 output/4.out -a 4 -i 1 -rr --duration 30
	sbatch --ntasks=4 --cpus-per-task=28 ./enigma.sh 1000 output/0.out -a 1 -i 0 -rr --duration 30




#echo "starting n=1 t=7"
#sbatch --ntasks=1 --cpus-per-task=7 --time=5 enigma.sh 700 n1t7e1.out 1

#echo "starting n=1 t=14"
#sbatch --ntasks=1 --cpus-per-task=14 --time=5 enigma.sh 700 n1t14e1.out 1

exit 0