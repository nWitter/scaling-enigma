#!/bin/bash
#########################
#

if [ $1 != -1 ]; then
	echo "launch interf"
	./MPI_Manager $1 $2 &
else
	echo "PROGRAM only"
fi
exit