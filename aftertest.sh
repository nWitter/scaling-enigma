#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
for filename in $DIR/output/*; do
	echo "$filename" >> testout.txt
	input="$filename"
	while IFS= read -r line; do
		echo "$line"
		if [[ $line == "#R0 Computations with chameleon*"]];
		then
			echo "$line" >> testout.txt
		fi
		if [[ $line == "#R0: Computations with normal tasking*"]];
		then
			echo "$line" >> testout.txt
		fi


"$line"
	done < "$input"
done




exit
