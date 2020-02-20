#!/bin/bash
#########################
#

mkdir -p output
chmod +x enigma.sh


	sbatch --ntasks=4 --cpus-per-task=28 ./enigma.sh 800 output/00.out -a 1 -i 1 -f -t 30
	#sbatch --ntasks=2 --cpus-per-task=28 ./enigma.sh 1200 output/01.out 0 0
	#sbatch --ntasks=2 --cpus-per-task=28 ./enigma.sh 1200 output/10.out 1 1
	#sbatch --ntasks=2 --cpus-per-task=28 ./enigma.sh 1200 output/11.out 1 1




#echo "starting n=1 t=7"
#sbatch --ntasks=1 --cpus-per-task=7 --time=5 enigma.sh 700 n1t7e1.out 1

#echo "starting n=1 t=14"
#sbatch --ntasks=1 --cpus-per-task=14 --time=5 enigma.sh 700 n1t14e1.out 1

exit 0