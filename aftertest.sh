#!/bin/bash
for filename in $(dirname $dir_path)/output/*; do
	echo $file
	input="$file"
	while IFS= read -r line; do
		echo "$line"
	done < "$input"
done



exit
