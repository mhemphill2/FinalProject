//Author: Nikolaj Scharling Holm

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readInputMesh.h"


double* readInputMesh(const char* filename, int* nTriangles, int* nMeshEntries) {
	
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("Mesh file not found. Please check that the filename is correct.\n");
		return 1;
	}
	
	//Buffer length to string
	char str[256];
	int strl = 256;
	//Make string float value
	*nTriangles = atof(fgets(str, strl, fp));
	//nTriangles times 3 rows pr triangle times  entries pr row
	*nMeshEntries = *nTriangles * 3 * 3;
	//Allocating memory to store data
	double* mesh = (double*)malloc(*nMeshEntries*sizeof(double));
	
	//nTriangles*3 equals n rows
	for (size_t i = 0; i < *nTriangles*3; i++)
	{
		//fgets reads each line of the input file
		fgets(str, strl, fp);
		//printf("%s\n", str);
		char* token = strtok(str, ",");
		size_t j=0;
		while (token != NULL) {
			mesh[i * 3 + j] = atof(token);
			j++;
			token = strtok(NULL, ",");
		}
	}

	fclose(fp);

	return mesh;
}
