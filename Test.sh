#!/bin/bash
#########################
#

mkdir -p output
chmod +x enigma.sh



	#sbatch --ntasks=4 --cpus-per-task=28 --time=00:03:00 ./enigma.sh 1000 output/rr.out -a 1 -i 1 -rr --duration 30
	
sbatch --ntasks=$1 --cpus-per-task=$2 --time=00:010:00 ./enigma.sh 1000 output/$1-$2-$3-$4-.out -a $3 -i $4 -rr
	
	
	
	#sbatch --ntasks=4 --cpus-per-task=28 --time=00:03:00 ./enigma.sh 1000 output/4.out -a 4 -i 1 -rr --duration 30
	#sbatch --ntasks=4 --cpus-per-task=28 --time=00:03:00 ./enigma.sh 1000 output/0.out -a 1 -i 0 -rr --duration 30

exit 0