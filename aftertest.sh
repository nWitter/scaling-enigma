#!/bin/bash
#########################
#


for file in /output/*
do
	input="$file"
	while IFS= read -r line
	do
		echo "$line"
	done < "$input"
done



exit
