#!/bin/bash
#########################
#

echo "starting Interference"
echo $0
echo $1
echo $2

chmod +x interference.sh
./interference &
./$0 $1 > $2 &
wait



