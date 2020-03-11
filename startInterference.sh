#!/bin/bash
#########################
#
MATRIX_PATH=../chameleon-apps/applications/matrix_example/main



./MPI_Manager $@ &
sleep 2
for i in 1 2 3 4 5
do
	$MATRIX_PATH $1 $2 > $2$i.out &
	sleep 100
done

exit