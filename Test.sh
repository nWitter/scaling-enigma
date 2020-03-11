#!/bin/bash
#########################
#

mkdir -p output
chmod +x enigma.sh

for a in 1 2 3
do
for i in 1 2 3 4 5
do
	echo "task" $1 " " $i
	sbatch --ntasks=8 --cpus-per-task=7 --time=00:03:00 ./enigma.sh 5 $i 8 $a &
	#sbatch --ntasks=8 --cpus-per-task=7 --time=00:03:00 ./enigma.sh 8 3 &
	sleep 300
done
done

for a in 1 2 3
do
for i in 1 2 3 4 5
do
	echo "seccond task" $1 " " $i
	sbatch --ntasks=2 --cpus-per-task=28 --time=00:03:00 ./enigma.sh 5 $i 2 $a &
	sleep 300
done
done


	#sbatch --ntasks=4 --cpus-per-task=28 --time=00:03:00 ./enigma.sh 1000 output/rr.out -a 1 -i 1 -rr --duration 30
	

	
	#sbatch --ntasks=8 --cpus-per-task=7 --time=00:10:00 ./enigma.sh
	#sbatch --nodes=12 --tasks-per-node=4 --time=00:10:00 ./enigma.sh

	
	#sbatch --ntasks=4 --cpus-per-task=28 --time=00:03:00 ./enigma.sh 1000 output/4.out -a 4 -i 1 -rr --duration 30
	#sbatch --ntasks=4 --cpus-per-task=28 --time=00:03:00 ./enigma.sh 1000 output/0.out -a 1 -i 0 -rr --duration 30

exit 0