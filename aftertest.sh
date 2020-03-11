#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
outfile="testout.txt"
for filename in $DIR/output/*
do
	echo $filename >> $outfile
	while IFS= read -r line; do
		if [[ $line == *"Computations"* ]]; then
			echo "$line" >> $outfile
		fi
	done < $filename
done




exit
