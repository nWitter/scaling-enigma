#!/bin/bash
#########################
#

echo "additional step"
echo $1
echo $3

mpiexec -n $1 $2 $3 > $4


