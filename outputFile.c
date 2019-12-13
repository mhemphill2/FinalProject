#include <stdlib.h>
#include <stdio.h>


//sugested input arguments is an array storing the collisions 
//ID's and the length of this array
int outputFile(int *collisions, int count) {

	const char filenamew[] = "collision_detection.out";
	FILE* fp = fopen(filenamew, "w");
	fprintf(fp, "s,t\n");

	for (int i = 0; i < count;)
	{
		fprintf(fp, "%d,%d\n", collisions[i],collisions[i+1]);
		printf("%d,%d\n", collisions[i],collisions[i+1]);
		i = i+2;
	}

	fclose(fp);
	return;
}
