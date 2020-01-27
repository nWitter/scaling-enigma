#!/bin/bash
#########################
#

echo "additional step"
echo $2
echo $3

mpiexec -n $1 $2 $3&



