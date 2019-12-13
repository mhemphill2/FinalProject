#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "readInputMesh.h"
#include "readInputSpheres.h"
#include "collisionDetection.h"

int main() {

// gcc collisionDetection.c readInputsph.c readInputMesh.c -Wall -O3 -o coldet -lm
	const char filename[] = "mesh.input.obj";
	const char filename1[] = "spheres.input.csv";
//	const char filename[] = "box.obj";
//	const char filename1[] = "test_vercities.csv";
//	const char filename[] = "2tri_test.obj";
//	const char filename1[] = "1testsphere.csv";

	//Initialize mesh metrics
	int nTriangles = 0;
	int nMeshEntries = 0;
	int count = 0;
	double* mesh;


//	printf("sizeof %d\n", 10000*30000*sizeof(short int)/1000000);

	//ReadInputMesh returning 1D array containing values
	mesh = readInputMesh(filename, &nTriangles, &nMeshEntries);

//Reading inputs from "readInputsph.c" 
//	int i,j;
	double rad;
	int ns;
	double* sarr = readInputSpheres(filename1, &rad, &ns);

	printf("# of Triangles: %d\n", nTriangles);

	printf("# of Spheres: %d\n", ns);
  	
	printf("File output to collision_detection.out\n");
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	int* collisions = collisionDetection(mesh, nTriangles, sarr, ns, rad, &count);
	end = clock();
	cpu_time_used = (((double)(end - start)) / CLOCKS_PER_SEC) * 1000;
	printf("Collision Detection time in ms: %f\n", cpu_time_used);

	printf("count: %d\n", count);

	outputFile(collisions, count);



	//free values
	free(collisions);
	free(mesh);
	free(sarr);
	return 0;
}
