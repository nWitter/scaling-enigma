#!/bin/bash
#########################
#

MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

./MPI_Manager $3 $4 &
$MATRIX_PATH $1 100 100 > $2 &


exit