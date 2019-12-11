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

//Reading inputs from "readInputSpheres.c" 
	int i,j;
	int n_cols = 3;
	double rad;
	int ns;
	double* sphereArr = readInputSpheres(filename1, &rad, &ns);


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
	printf("radius of spheres --> %f\n", rad);
	printf("Number of spheres --> %d\n", ns);
  	for (i = 0; i < ns; i++) {
    		for (j = 0; j < n_cols; j++) {
      		printf("%lf ", sphereArr[i * n_cols + j]);
    		}
  	printf("\n");
  	}
	printf("End of sphere TESTING\n");

// Collision detection
// Need to compute all : 1st) - (point - plane)  ;  2nd) - (point - line)  ;  3rd) - (point - point), 

	// Computes point - point (distance from sphere center to each vertex of triangle)
	// d = sqrt((x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2)
	int spheres, tri;
	double d1,d2,d3;
	double ax, ay, az, bx, by, bz, nxx, nyy, nzz, nx, ny, nz;
	double dpx, dpy, dpz, dist, pox, poy, poz, D, distance, distancecheck;
	for (spheres = 0; spheres < ns; spheres++) {
		for (tri = 0; tri < nTriangles; tri++) {
			printf("\nSphere ID: %d  ---  Triangle ID: %d\n", spheres, tri);
			printf("Distance to vertices\n");
			d1 = sqrt(pow((sphereArr[spheres * n_cols + 0]-mesh[tri * 9 + 0]),2)+pow((sphereArr[spheres * n_cols + 1]-mesh[tri * 9 + 1]),2)+pow((sphereArr[spheres * n_cols + 2]-mesh[tri * 9 + 2]),2));
			printf("d1 = %f   ", d1);

			d2 = sqrt(pow((sphereArr[spheres * n_cols + 0]-mesh[tri * 9 + 3]),2)+pow((sphereArr[spheres * n_cols + 1]-mesh[tri * 9 + 4]),2)+pow((sphereArr[spheres * n_cols + 2]-mesh[tri * 9 + 5]),2));
			printf("d2 = %f   ", d2);

			d3 = sqrt(pow((sphereArr[spheres * n_cols + 0]-mesh[tri * 9 + 6]),2)+pow((sphereArr[spheres * n_cols + 1]-mesh[tri * 9 + 7]),2)+pow((sphereArr[spheres * n_cols + 2]-mesh[tri * 9 + 8]),2));
			printf("d3 = %f\n", d3);
			//will put into array


// point - line
// 1st) point - plane -- then detect if point inside triangle on plane

			//calculateing normal vector to triangle (p1, p2, p3)
			// a = p2-p1  ;  b = p3-p1
			// nx = ay*bz - az*by  ;  ny = az*bx - ax*bz  ;  nz = ax*by - ay*bx
			printf("Normal Unit Vectors for Triangles\n");
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



			//distance from P to point in plane(on triangle)
//			dpx = ((sphereArr[spheres * n_cols + 0]-mesh[tri * 9 + 0])*nx);
//			dpy = ((sphereArr[spheres * n_cols + 1]-mesh[tri * 9 + 1])*ny);
//			dpz = ((sphereArr[spheres * n_cols + 2]-mesh[tri * 9 + 2])*nz);
//			printf("dpx = %f  :  dpy = %f  :  dpz = %f\n", dpx, dpy, dpz);

			// determining D for eq of plane
			D = -(nxx*mesh[tri * 9 + 0])-(nyy*mesh[tri * 9 + 1])-(nzz*mesh[tri * 9 + 2]);
//			printf("D = %f \n",D);

			// closest distance to plane
			distance = fabs((sphereArr[spheres * 3 + 0]*nxx)+(sphereArr[spheres * 3 + 1]*nyy)+(sphereArr[spheres * 3 + 2]*nzz) + D)/sqrt(pow(nxx,2)+pow(nyy,2)+pow(nzz,2));

			printf("Distance to closest point on plane = %f \n",distance);

			//Projected point from P to closest point in plane P0
			pox = (sphereArr[spheres * n_cols + 0]-(distance*nx));
			poy = (sphereArr[spheres * n_cols + 1]-(distance*ny));
			poz = (sphereArr[spheres * n_cols + 2]-(distance*nz));
			printf("New closest point on plane : (pox = %f , poy = %f , poz = %f) \n", pox, poy, poz);

			//verifying point accuracy, compare with distance
			distancecheck = sqrt(pow((sphereArr[spheres * 3 + 0]-pox),2)+pow((sphereArr[spheres * 3 + 1]-poy),2)+pow((sphereArr[spheres * n_cols + 2]-poz),2));
			printf("Verify distance; d = %f   \n", distancecheck);


// closest distance
// wrong calc - remove			dist = sqrt(pow((sphereArr[spheres * n_cols + 0]-pox),2)+pow((sphereArr[spheres * n_cols + 1]-poy),2)+pow((sphereArr[spheres * n_cols + 2]-poz),2));
//			printf("Distance to closest point on plane = %f \n",dist);			
			
		}
	}


	//free values
	free(mesh);
	free(sphereArr);
	return 0;
}
