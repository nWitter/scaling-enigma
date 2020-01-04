#!/bin/bash
for filename in $(dirname $(dirname $(realpath $0)))/output/*; do
	echo $file
	input="$file"
	while IFS= read -r line; do
		echo "$line"
	done < "$input"
done



exit
