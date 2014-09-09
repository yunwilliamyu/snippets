#!/bin/bash
# Computes the number of bits to store a quality score, using bzip2 compression

for file in $@
do
	cut -f11 $file > .$file.qual
	orig_size=`wc -c < .$file.qual`
	orig_lines=`wc -l < .$file.qual`
	orig_size=`echo "$orig_size - $orig_lines" | bc`
	bzip2 .$file.qual
	new_size=`wc -c < .$file.qual.bz2`
	rm .$file.qual.bz2
	#echo $file
	bitsq=`echo "scale=4; 1/( $orig_size / ( $new_size * 8)) " | bc`
	echo -e $file'\t'$bitsq
done	
