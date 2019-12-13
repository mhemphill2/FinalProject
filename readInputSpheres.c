#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readInputSpheres.h"


//Function to read n spheres, radius and convert input to 1D array. Delete two below before final.
double* readInputSpheres(const char* filename1, double* radius, int* nSpheres) {

	FILE* fp = fopen(filename1, "r");
	if (!fp) {
		printf("Sphere file not found. Please check that the filename is correct.\n");
		return 1;
	}

	char str[256];
	int strl = 256;

	//Skip first line reading x,y,z
	fgets(str, strl, fp);

	//Define radius and nSpheres
	*radius = atof(fgets(str, strl, fp));
	*nSpheres = atoi(fgets(str, strl, fp));

	//Allocate memory to store input
	double* spheres = (double*)malloc(*nSpheres * 3 * sizeof(double));

	for (size_t i = 0; i < *nSpheres; i++)
	{
		fgets(str, strl, fp);
		//printf("%s\n", str);
		char* token = strtok(str, ",");
		size_t j = 0;
		while (token != NULL) {
			spheres[i * 3 + j] = atof(token);
			j++;
			token = strtok(NULL, ",");
		}
	}
	return spheres;
}
