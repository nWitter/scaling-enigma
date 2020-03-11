#!/bin/bash
#########################
#
MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

echo $@
echo "starting"
./MPI_Manager $@ &
sleep 2

for i in 1 2 3 4 5
do
	echo 1
	$MATRIX_PATH $1 $2 > $3$i.out
	echo -done
	sleep 100
done

exit