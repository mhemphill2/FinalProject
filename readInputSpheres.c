// Michael Hemphill - Read "spheres.input.csv" file and return values to main function
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readInputSpheres.h"


//Function to read n spheres, radius and convert input to 1D array
double* readInputSpheres(const char* filename1, double* radius, int* nSpheres) {

	FILE* fp = fopen(filename1, "r");
	if (!fp) {
		printf("Can't open file\n");
		return 1;
	}

	char str[256];
	int strl = 256;

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

//Function to return radius and # of spheres
double* InputSpheresradNS(const char* filename1){
	FILE* fp;
	fp = fopen(filename1, "r");
	char line[200];
	char* rstring;		//string inputs
	char* nsstring;		//string inputs
	double r;		//radius
	double ns;		//# of spheres
	char* xyz;
	double* radNS = (double*)malloc(2 * sizeof(double));

	//Check if file exists
	if (!fp) {
		printf("Can't open file\n");
		return 0;
	}
	//Goes through the first 3 lines to obtain radius and # of spheres
	//Returns 2x1 matrix of radius and # of spheres
	xyz = fgets(line,200,fp);	//placeholder to skip first line
	rstring = fgets(line,200,fp);
	r = atof(rstring);
	nsstring = fgets(line,200,fp);
	ns = atof(nsstring);
	radNS[0] = r;
	radNS[1] = ns;
	return radNS;
}

double* InputSpheresCoord(const char* filename1){
	FILE* fp;
	fp = fopen(filename1, "r");
	char line[200];
	int i, j;
	char* rstring;		//string inputs
	char* nsstring;		//string inputs
	double r;		//radius
	int ns;			//# of spheres
	char* xyz;


	//Check if file exist
	if (!fp) {
		printf("Can't open file\n");
		return 0;
	}
	//passes through first 3 lines of code
	xyz = fgets(line,200,fp);
	rstring = fgets(line,200,fp);
	r = atof(rstring);
	nsstring = fgets(line,200,fp);
	ns = atoi(nsstring);

	//Sets variables, allocates memory, and builds array of x,y,z sphere coordinates
	int n_rows = ns;
	int n_cols = 3;
	char* linet;
	char* token;
	double t1;
	double* arr = (double*)malloc(n_rows * n_cols * sizeof(double));

	for (i = 0; i < n_rows; i++) {
		linet = fgets(line,200,fp);
		token = strtok(linet, ",");
		for (j = 0; j<3;j++){
			t1 = atof(token);
			arr[i * n_cols + j] = t1;		
			token = strtok(NULL, ",");
		}
	}

	//Close file and return array
	fclose(fp);
	return arr;
}

