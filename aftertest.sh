#!/bin/bash
#########################
#


for file in /output/n*t*.out
do
	input="$file"
	while IFS= read -r line
	do
		echo "$line"
	done < "$input"
done



exit
