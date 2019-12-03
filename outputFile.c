#include <stdlib.h>
#include <stdio.h>


//sugested input arguments is an array storing the collisions 
//ID's and the length of this array
int outputFile() {
	char filename[] = "collision_detection.out ";

	FILE* fp = fopen(filename, "w");

	fprintf(fp, "s,t\n");

	int n = 8;
	int meshid[] = { 1,3,4,5,7,33,53,123 };
	int sphereid[] = { 2,3,55,67,83,123,132,155 };
	int collisions[] = { 1,3,4,5,7,33,53,123,2,3,55,67,83,123,132,155 };


	int c = 0;
	for (size_t i = 0; i < n; i++)
	{
		//solution for 2 arrays storing ID's
		fprintf(fp, "%d,%d\n", meshid[i], sphereid[i]);
		//alternative with one array storing ID's in rowmajor. 
		//Don't know which one is faster though.
		printf("%d,%d\n", collisions[c],collisions[c+1]);
		c=c+2;
	}

	fclose(fp);

	
}