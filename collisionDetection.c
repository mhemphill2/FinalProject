#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "readInputMesh.h"
#include "readInputSpheres.h"
//temporary stuff - run command
//gcc collisionDetection.c readInputSpheres.c readInputMesh.c -Wall -O3 -o coldet -lm
int main() {

	//What is the exact filenames/types and how should we read them? input arguments?
	const char filename[] = "mesh.input.obj";
	const char filename1[] = "spheres.input.csv";
	//Why is the step beneath done??
	int* readInputMeshEntries(filename);
	double* readInputMesh(filename);
	double* InputSpheresradNS(filename1);
	double* InputSpheresCoord(filename1);

	//Initialize mesh metrics
	int nTriangles = 0;
	int nMeshEntries = 0;
	double* mesh;
	//ReadInputMesh returning 1D array containing values
	mesh = readInputMesh(filename, &nTriangles, &nMeshEntries);

	//Test reading works:
	/*printf("nTriangles=%d, nMeshe=%d\n", nTriangles, nMeshEntries);
	for (size_t i = 0; i < nMeshEntries; i++)
	{
		printf("mesh[%d]=%f\n", i, mesh[i]);
	}*/

	int i, j;

//Reading inputs from "readInputSpheres.c" 
//	int i,j;
	int n_cols = 3;
	double rad;
	int ns;
	double* sphereArr = readInputSpheres(filename1, &rad, &ns);

	//double* radNS = (double*)malloc(2 * sizeof(double));
	//radNS = InputSpheresradNS(filename1);	//Function call to return radius and # of spheres
	////rad = radNS[0];		//Radius
	////ns = radNS[1];		//# of spheres

	//int n_rows = ns;
	//double* arr = (double*)malloc(n_rows * n_cols * sizeof(double));	
	//arr = InputSpheresCoord(filename1);	//Function call to return array of x,y,z sphere coordinates

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

	printf("\nStart of sphere TESTING\n");
	printf("radius of spheres --> %f\n", rad);
	printf("Number of spheres --> %f\n", ns);
  	for (i = 0; i < ns; i++) {
    		for (j = 0; j < n_cols; j++) {
      		printf("%lf ", sphereArr[i * n_cols + j]);
    		}
  	printf("\n");
  	}
	printf("End of sphere TESTING\n");

// Collision detection, order: (s,t) ; (i,j) ; (sphere,triangle)
// Need to compute all (point - point), (point - line), (point - plane)

	// Computes point - point (distance from sphere center to each vertex of triangle)
	// d = sqrt((x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2)
	int spheres, tri;
	double d1,d2,d3;
	printf("\nDistance to vertices\n");
	for (spheres = 0; spheres < ns; spheres++) {
		for (tri = 0; tri < nTriangles; tri++) {
			printf("Sphere ID: %d  ---  Triangle ID: %d\n", spheres, tri);
			d1 = sqrt(pow((sphereArr[spheres * n_cols + 0]-mesh[tri * 9 + 0]),2)+pow((sphereArr[spheres * n_cols + 1]-mesh[tri * 9 + 1]),2)+pow((sphereArr[spheres * n_cols + 2]-mesh[tri * 9 + 2]),2));
			printf("d1 = %f   ", d1);

			d2 = sqrt(pow((sphereArr[spheres * n_cols + 0]-mesh[tri * 9 + 3]),2)+pow((sphereArr[spheres * n_cols + 1]-mesh[tri * 9 + 4]),2)+pow((sphereArr[spheres * n_cols + 2]-mesh[tri * 9 + 5]),2));
			printf("d2 = %f   ", d2);

			d3 = sqrt(pow((sphereArr[spheres * n_cols + 0]-mesh[tri * 9 + 6]),2)+pow((sphereArr[spheres * n_cols + 1]-mesh[tri * 9 + 7]),2)+pow((sphereArr[spheres * n_cols + 2]-mesh[tri * 9 + 8]),2));
			printf("d3 = %f\n", d3);
			//will put into array
		}
	}

// point - line

// 1st) point - plane -- then if point inside triangle on plane -- point could be on plane outside of triangle

	//calculateing normal vector to triangle (p1, p2, p3)
	// a = p2-p1  ;  b = p3-p1
	// nx = ay*bz - az*by  ;  ny = az*bx - ax*bz  ;  nz = ax*by - ay*bx
	double ax, ay, az, bx, by, bz, nxx, nyy, nzz, nx, ny, nz;
	printf("\nNormal Vectors for Triangles\n");
//	for (spheres = 0; spheres < ns; spheres++) {
		for (tri = 0; tri < nTriangles; tri++) {
			printf("Triangle ID: %d\n", tri);
			ax = mesh[tri * 9 + 3] - mesh[tri * 9 + 0];
			ay = mesh[tri * 9 + 4] - mesh[tri * 9 + 1];
			az = mesh[tri * 9 + 5] - mesh[tri * 9 + 2];
			bx = mesh[tri * 9 + 6] - mesh[tri * 9 + 0];
			by = mesh[tri * 9 + 7] - mesh[tri * 9 + 1];
			bz = mesh[tri * 9 + 8] - mesh[tri * 9 + 2];
			//non-normalized unit vector
			nxx = (ay*bz) - (az*by);
			nyy = (az*bx) - (ax*bz);
			nzz = (ax*by) - (ay*bx);
			//normalized unit vector (nx,ny,nz / sqrt(nx^2+ny^2+nz^2)
			nx = nxx/sqrt(pow(nxx,2)+pow(nyy,2)+pow(nzz,2));
			ny = nyy/sqrt(pow(nxx,2)+pow(nyy,2)+pow(nzz,2));
			nz = nzz/sqrt(pow(nxx,2)+pow(nyy,2)+pow(nzz,2));
			printf("nx = %f  :  ny = %f  :  nz = %f\n", nx, ny, nz);
		}
//	}


	//free values
	free(mesh);
	free(sphereArr);
	return 0;
}
