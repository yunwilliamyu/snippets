/* count_char.cpp
 * Counts the occurences of each character in a file
*/

#include <stdio.h>
#include <iterator>
#include <fstream>
#include <iostream>
#include <stdlib.h>

int main( int argc, char *argv[])
{
	if (argc < 2) {
		std::cerr << "Counts the occurences of each character value in [input_file]" << std::endl;
		std::cerr << "Usage: " << argv[0] << " input_file" << std::endl;
		exit(-1);
	}

	
	std::FILE * inFile;
	//char outfile_name[4096];
	//unsigned int name_length;

	int c; // character input
	inFile=fopen(argv[1],"r");
	if (inFile==NULL) {
		perror ("Error opening input file.");
		exit(-3);
	}

	unsigned long count[256];
	for (int i=0; i<256; i++)
		count[i]=0;
	while ( (c=getc(inFile)) !=EOF)
	{
		count[c]++;
	}
	fclose(inFile);
	//unsigned long average;
	//average = sum / count;
	//assert(average > 0);
	//assert(average < 256);
	for (int i=0; i<256; ++i) {
		printf("%i: %lu\n", i, count[i]);
	}
	return 0;
};

