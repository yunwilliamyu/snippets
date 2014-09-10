#!/bin/bash
# Get only SNPs from a VCF variant file
for file in $@
do
	cat $file | awk '{ if (( length($4) == 1 )&&( length($5) == 1))  print}' > $file.snp
done
