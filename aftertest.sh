#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
outfile="testout.txt"
for filename in $DIR/output/*
do
	echo $filename >> $outfile
	input=$filename
	while IFS= read -r line
	do
		if [[ $line == "#R0 Computations with chameleon*" ]]; then
			echo "$line" >> $outfile
		fi
		if [[ $line == "#R0: Computations with normal tasking*" ]]; then
			echo "$line" >> $outfile
		fi
	done < "$input"
done




exit
