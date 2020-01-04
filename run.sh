#!/bin/bash
#########################
#


MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

echo "starting"
./interference &
./$MATRIX_PATH $@ > out &	#0 $1 > $2 &
wait



