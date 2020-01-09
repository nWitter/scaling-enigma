#!/bin/bash
#########################
#

echo "Starting instances:"
chmod +x enigma_loop

for ((i=0; i<$4; i++))
do
	echo "--started one instance"
	./enigma_loop > enix.out &
done

#./MPI_Manager

echo "starting program"
./$1 $2 > $3 &
echo "started prog and " $4 " interference instances"
wait



