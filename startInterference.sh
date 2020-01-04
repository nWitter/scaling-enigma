#!/bin/bash
#########################
#

echo "starting Interference"
echo $0
echo $1

./interference &
./$0 $1 > mat.out &
wait



