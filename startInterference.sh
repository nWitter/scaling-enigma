#!/bin/bash
#########################
#
MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

echo $@
echo "starting"
./MPI_Manager $@ &
sleep 2

$MATRIX_PATH $1 100 100 100 100 100 100 100 100 > $2

exit