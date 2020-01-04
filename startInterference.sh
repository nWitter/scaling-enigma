#!/bin/bash
#########################
#

echo "starting Interference"

./interference &
./$1 $2 > mat.out &
wait



