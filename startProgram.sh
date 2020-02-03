#!/bin/bash
#########################
#args
# 1 matrix size
# 2 outfile
# 3 interference nodes
# 4 interference fraction
#
# TODO:
# num nodes
# 



MATRIX_PATH=../chameleon-apps/applications/matrix_example/main

echo "args: " $@

#start interference in different thread
chmod +x startProgram.sh
./startInterference.sh $3 $4

$MATRIX_PATH $1 100 100 > $2

exit
