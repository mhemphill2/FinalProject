#include <stdio.h>
#include <stdlib.h>
#include "readInputMesh.h"

int main() {

//	const char filename[] = "input.obj";
	const char filename1[] = "spheres.input.csv";
//	readInputMesh(filename);


//Reading inputs from "readInputSpheres.c" 
	int i,j;
	int n_cols = 3;
	double rad;
	double ns;
	double* radNS = (double*)malloc(2 * sizeof(double));
	radNS = readInputSpheresradNS(filename1);	//Function call to return radius and # of spheres
	rad = radNS[0];		//Radius
	ns = radNS[1];		//# of spheres

	int n_rows = ns;
	double* arr = (double*)malloc(n_rows * n_cols * sizeof(double));	
	arr = readInputSpheresCoord(filename1);	//Function call to return array of x,y,z sphere coordinates


//Will remove before final build, TESTING INPUT VALUES
	printf("Start of collison detection TESTING\n");
	printf("radius of spheres --> %f\n", rad);
	printf("Number of spheres --> %f\n", ns);
  	for (i = 0; i < n_rows; i++) {
    		for (j = 0; j < n_cols; j++) {
      		printf("%lf ", arr[i * n_cols + j]);
    		}
  	printf("\n");
  	}
	printf("End of collison detection TESTING\n");

	//free values
	free(radNS);
	free(arr);
	return 0;
}
