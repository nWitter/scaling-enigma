#!/bin/bash
#########################
#

echo "additional step"
echo $1
echo $2
echo $3
echo $4

#mpiexec -n $1 
$2 $3 > $4


