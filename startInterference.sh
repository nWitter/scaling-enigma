#!/bin/bash
#########################
#

echo "starting Interference"
echo $1
echo $2

./interference &
./$1 $2 > mat.out &
wait



