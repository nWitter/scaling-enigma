#!/bin/bash
#########################
#


MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

echo "starting"
./interference &
./$MATRIX_PATH $@ > mat.out &	#0 $1 > $2 &
wait



