#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "readInputMesh.h"
#include "readInputSpheres.h"
#include "collisionDetection.h"

//temporary stuff - run command
//gcc collisionDetection.c readInputsph.c readInputMesh.c -Wall -O3 -o coldet -lm
int main() {

	/*const char filename[] = "mesh.input.obj";
	const char filename1[] = "spheres.input.csv";*/
	/*const char filename[] = "box.obj";
	const char filename1[] = "test_vercities.csv";*/
	const char filename[] = "2tri_test.obj";
	const char filename1[] = "1testsphere.csv";

	//Initialize mesh metrics
	int nTriangles = 0;
	int nMeshEntries = 0;
	double* mesh;

	//ReadInputMesh returning 1D array containing values
	mesh = readInputMesh(filename, &nTriangles, &nMeshEntries);

//Reading inputs from "readInputsph.c" 
	int i,j;
	double rad;
	int ns;
	double* sarr = readInputSpheres(filename1, &rad, &ns);		//sphere array

	clock_t start, end;
	double cpu_time_used;
	start = clock();
	collisionDetection(mesh, nTriangles, sarr, ns, rad);
	end = clock();
	cpu_time_used = (((double)(end - start)) / CLOCKS_PER_SEC) * 1000;

//Will remove before final build, TESTING INPUT VALUES
	printf("Start of triangle TESTING\n");
	printf("nt = %d\n", nTriangles);
	printf("entries = %d\n", nMeshEntries);

	//prints x1 y1 z1 x2 y2 z2 x3 y3 z3 coordinates for each triangle
  	for (i = 0; i < nTriangles; i++) {
    		for (j = 0; j < 9; j++) {
      		printf("%lf ", mesh[i * 9 + j]);
    		}
  	printf("\n");
  	}
	printf("End of triangle TESTING\n");

	//prints x y z coordinates for each sphere center
	printf("\nStart of sphere TESTING\n");
	printf("radius of sph --> %f\n", rad);
	printf("Number of sph --> %d\n", ns);
  	for (i = 0; i < ns; i++) {
    		for (j = 0; j < 3; j++) {
      		printf("%lf ", sarr[i * 3 + j]);
    		}
  	printf("\n");
  	}
	printf("End of sphere TESTING\n\n");


	//free values
	free(mesh);
	free(sarr);
	return 0;
}
