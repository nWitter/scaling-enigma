#!/bin/bash
#########################
#

mpiexec -n 1 ./interference &
mpiexec -n 1 ./$0 $1 > $2 &



