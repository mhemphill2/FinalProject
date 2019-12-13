//Author: Michael Hemphill and Nikolaj Scharling Holm

#include <stdlib.h>
#include <stdio.h>
#include "outputFile.h"

int* outputFile(int *collisions, int count) {

	//Defining the filename
	const char filenamew[] = "collision_detection.out";
	//Creating or opening the file for write purposes
	FILE* fp = fopen(filenamew, "w");
	//Print header to outputfile
	fprintf(fp, "s,t\n");

	//Print collision ID's to file
	for (int i = 0; i < count;)
	{
		fprintf(fp, "%d,%d\n", collisions[i],collisions[i+1]);
		i = i+2;
	}

	//Close file
	fclose(fp);
	return;
}
