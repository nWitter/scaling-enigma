#!/bin/bash
#########################
#

mkdir -p output
chmod +x enigma.sh



	#sbatch --ntasks=4 --cpus-per-task=28 --time=00:03:00 ./enigma.sh 1000 output/rr.out -a 1 -i 1 -rr --duration 30
	
for i in 1 2 3 4 5 6 7 8 9 10
do
	sbatch --ntasks=$1 --cpus-per-task=$2 --time=00:04:00 ./enigma.sh 1000 output/$1-$2-$3-$4-$i.out -a $3 -i $4 -rr
	sleep 10
done	
	
	
	
	#sbatch --ntasks=4 --cpus-per-task=28 --time=00:03:00 ./enigma.sh 1000 output/4.out -a 4 -i 1 -rr --duration 30
	#sbatch --ntasks=4 --cpus-per-task=28 --time=00:03:00 ./enigma.sh 1000 output/0.out -a 1 -i 0 -rr --duration 30

exit 0