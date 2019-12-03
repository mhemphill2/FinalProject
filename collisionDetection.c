#include <stdio.h>
#include <stdlib.h>
#include "readInputMesh.h"

int main() {

	const char filename[] = "mesh.input.obj";
	const char filename1[] = "spheres.input.csv";
	int* readInputMeshEntries(filename);
	double* readInputMesh(filename);
	double* InputSpheresradNS(filename1);
	double* InputSpheresCoord(filename1);

//Read inputs from mesh
	int nt;		//# of triangles
	int* meshentries = (int*)malloc(1 * sizeof(int));
	meshentries = readInputMeshEntries(filename);
	nt = meshentries[0];		//# of triangles
	int entry = nt * 3 * 3;		//# of coordinate entries
	double* mesh = (double*)malloc(entry*sizeof(double));
	mesh = readInputMesh(filename);		//inputs mesh

	int i,j;



//Reading inputs from "readInputSpheres.c" 
//	int i,j;
	int n_cols = 3;
	double rad;
	double ns;
	double* radNS = (double*)malloc(2 * sizeof(double));
	radNS = InputSpheresradNS(filename1);	//Function call to return radius and # of spheres
	rad = radNS[0];		//Radius
	ns = radNS[1];		//# of spheres

	int n_rows = ns;
	double* arr = (double*)malloc(n_rows * n_cols * sizeof(double));	
	arr = InputSpheresCoord(filename1);	//Function call to return array of x,y,z sphere coordinates

//Will remove before final build, TESTING INPUT VALUES
	printf("Start of triangle TESTING\n");
	printf("nt = %d\n", nt);
	printf("entries = %d\n", entry);
	//prints x1 y1 z1 x2 y2 z2 x3 y3 z3 coordinates for each triangle
  	for (i = 0; i < nt; i++) {
    		for (j = 0; j < 9; j++) {
      		printf("%lf ", mesh[i * 9 + j]);
    		}
  	printf("\n");
  	}
	printf("End of triangle TESTING\n");

	printf("Start of sphere TESTING\n");
	printf("radius of spheres --> %f\n", rad);
	printf("Number of spheres --> %f\n", ns);
  	for (i = 0; i < n_rows; i++) {
    		for (j = 0; j < n_cols; j++) {
      		printf("%lf ", arr[i * n_cols + j]);
    		}
  	printf("\n");
  	}
	printf("End of sphere TESTING\n");

// Collision detection, closest point to triangle, in work






	//free values
	free(meshentries);
	free(mesh);
	free(radNS);
	free(arr);
	return 0;
}
