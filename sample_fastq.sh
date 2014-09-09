#!/bin/bash
# Samples every 20th read of a FASTQ file specified as the first argument, outputs to standard out.
cat $1 | awk -v seed=0 'BEGIN{srand(seed);} {if (rand()>0.95) {print;getline;print;getline;print;getline;print;} else {getline;getline;getline;}}'
