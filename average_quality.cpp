/* average_quality.cpp
 * Finds the average quality in a SAM file
*/

#include <stdio.h>
#include <iterator>
#include <fstream>
#include <iostream>
#include <stdlib.h>

int main( int argc, char *argv[])
{
	if (argc < 2) {
		std::cerr << "Finds the average quality in [input_file]" << std::endl;
		std::cerr << "Usage: " << argv[0] << " input_file" << std::endl;
		exit(-1);
	}

	
	std::FILE * inFile;
	//char outfile_name[4096];
	//unsigned int name_length;
	int col=1;

	int c; // character input
	inFile=fopen(argv[1],"r");
	if (inFile==NULL) {
		perror ("Error opening input file.");
		exit(-3);
	}

	unsigned long count=0;
	unsigned long sum=0;
	while ( (c=getc(inFile)) !=EOF)
	{
		if (col == 11) {
			//printf(".");
			switch (c) {
				case '\t':
					++col;
					break;
				case '\n':
					col = 1;
					break;
				default:
					sum+=c;
					count++;
			}

		} else {
			switch (c) {
				case '\n':
					col=0;
					// Deliberate fall-through
				case '\t':
					++col;
					// Deliberate fall-through
				default:
					break;
			}
		}
	}
	fclose(inFile);
	unsigned long average;
	average = sum / count;
	//assert(average > 0);
	//assert(average < 256);
	printf("%lu ", average);
	putchar((char)average);
	printf("\n");
	return 0;
};

