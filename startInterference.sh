#!/bin/bash
#########################
#

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

echo "args: " $@

if [ $3 != -1 ]; then
	echo "launch interf"
	./MPI_Manager $3 $4 &
else
	echo "PROGRAM only"
fi

$MATRIX_PATH $1 > $2 