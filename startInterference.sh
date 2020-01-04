#!/bin/bash
#########################
#

echo "starting Interference"
echo $1
echo $2
echo $3

chmod +x interference.sh
./interference &
./$1 $2 > $3 &
wait



