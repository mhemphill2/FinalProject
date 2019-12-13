//Authors: Michael Hemphill and Nikolaj Scharling Holm

/**
*  \details The main function distribute the work of the collision detection
* It takes in three input arguments, the first one being the run command,
* the second one being, the mesh filename and the third being the 
* sphere filename. 
*
* **Notice**: In order for the program to work correctly it is the second
* command line argument must be the filname for the mesh and vice versa.
* Other wise the program will switch up the sphere and meshes and outout
* wrong results or terminate
*
* \param argc The number of input argumnets. Must be 3 (program name, mesh 
* filename and sphere file name)
* \param *argv[] an array storing the input arguments
*
*
* **Output**
*
* - The main function outputs the number of triangles
* - The number of spheres
* - A message confirming the result were written to an output file
* - The time used for computation
* - The number of collisions
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "readInputMesh.h"
#include "readInputSpheres.h"
#include "collisionDetection.h"
#include "outputFile.h"

// Alternate compile command
// gcc mainFunction.c collisionDetection.c readInputSpheres.c readInputMesh.c outputFile.c -Wall -O3 -o coldet -lm

int main(int argc, char* argv[]) {

	if ((argc < 3) || (3 < argc))
	{
		printf("Error: 2 arguments required\nEnter name of mesh.input file and spheres.input file. Include filetype identifier.\n eg. \"mesh.input.obj spheres.input.csv\"\n");
		return 0;
	}

	char* filename = argv[1];
	char* filename1 = argv[2];

	//Initialize mesh metrics
	int nTriangles = 0;
	int nMeshEntries = 0;
	int count = 0;
	double* mesh;

	//ReadInputMesh returning 1D array containing values
	mesh = readInputMesh(filename, &nTriangles, &nMeshEntries);
	if (mesh == 1) {
		return 0;
	}

//Reading inputs from "readInputsph.c" 
	double rad;
	int ns;
	double* sarr = readInputSpheres(filename1, &rad, &ns);
	if (sarr == 1) {
		return 0;
	}
	printf("# of Triangles: %d\n", nTriangles);
	printf("# of Spheres: %d\n", ns);  	
	printf("File output to collision_detection.out\n");
	
	// timings
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	int* collisions = collisionDetection(mesh, nTriangles, sarr, ns, rad, &count);
	end = clock();
	cpu_time_used = (((double)(end - start)) / CLOCKS_PER_SEC) * 1000;

	printf("Collision Detection time in ms: %f\n", cpu_time_used);
	printf("# of collisions: %d\n", count/2);
	outputFile(collisions, count);


	//free values
	free(collisions);
	free(mesh);
	free(sarr);
	return 0;
}
