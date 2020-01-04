#!/bin/bash
#########################
#

echo "starting Interference"
echo $1
echo $2
echo $3

chmod +x interference
for i in {1..$4}
do
	./interference &
done
./$1 $2 > $3 &
echo "started prog and " $4 " interference instances"
wait



