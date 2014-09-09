#!/bin/bash
# Snips out only the quality string lines from a FASTQ file
for file in $@
do
	awk ' NR % 4 ==0 { print;}' $file > $file.qual
done
