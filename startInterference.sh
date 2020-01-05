#!/bin/bash
#########################
#

echo "Starting instances -"
echo "Number: " $4
chmod +x interference

for ((i=0; i<$4; i++))
do
	echo "--started one instance"
	./interference > out.out &
done

echo "starting program"
./$1 $2 > $3 &
echo "started prog and " $4 " interference instances"
wait



