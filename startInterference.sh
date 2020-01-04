#!/bin/bash
#########################
#

echo "starting Interference"

./interference &
./$0 $1 > mat.out &
wait



