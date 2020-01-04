#!/bin/bash
cd /output
for filename in /*; do
	echo $file
	input="$file"
	while IFS= read -r line; do
		echo "$line"
	done < "$input"
done



exit
