#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "readInputMesh.h"
#include "readInputSpheres.h"
#include "collisionDetection.h"

int main() {
//int main(int argc, char* argv[]) {

/*	if (argc < 3)
	{
		printf("Enter name of input.mesh file and input.sphere file. Include filetype identifyer.\n eg. \"input.mesh.obj input.sphere.csv\"\n");
		return 0;
	}

	char* filename = argv[1];
	char* filename1 = argv[2];
	//printf("%s %s\n", t_filename, t_filename1);
*/
// gcc collisionDetection.c readInputsph.c readInputMesh.c -Wall -O3 -o coldet -lm
//	const char filename[] = "mesh.input.obj";
//	const char filename1[] = "spheres.input.csv";
//	const char filename[] = "box.obj";
//	const char filename1[] = "test_vercities.csv";
	const char filename[] = "test_tri.obj";
	const char filename1[] = "test_sphere.csv";

	//Initialize mesh metrics
	int nTriangles = 0;
	int nMeshEntries = 0;
	int count = 0;
	double* mesh;


//	printf("sizeof %d\n", 10000*30000*sizeof(short int)/1000000);

	//ReadInputMesh returning 1D array containing values
	mesh = readInputMesh(filename, &nTriangles, &nMeshEntries);
//	if (mesh == 1) {
//		return 0;
//	}
//Reading inputs from "readInputsph.c" 
	int i,j;
	double rad;
	int ns;
	double* sarr = readInputSpheres(filename1, &rad, &ns);
//	if (sarr == 1) {
//		return 0;
//	}
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
	
	outputFile(collisions, count);

	printf("# of collisions: %d\n", count/2);

	//free values
	free(collisions);
	free(mesh);
	free(sarr);
	return 0;
}
