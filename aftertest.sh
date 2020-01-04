#!/bin/bash
for filename in /output/*.out; do
	echo $file
	input="$file"
	while IFS= read -r line; do
		echo "$line"
	done < "$input"
done



exit
