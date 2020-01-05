#!/bin/bash
#########################
#

echo "starting instances"
chmod +x interference

for i in {1..$4}
do
	echo "--started one instance"
	./interference > out.out &
done

echo "starting program"
./$1 $2 > $3 &
echo "started prog and " $4 " interference instances"
wait



