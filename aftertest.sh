#!/bin/bash
#########################
#

cd /output
for file in /*
do
	input="$file"
	while IFS= read -r line
	do
		echo "$line"
	done < "$input"
done



exit
