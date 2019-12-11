#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "readInputMesh.h"
#include "readInputSpheres.h"
//temporary stuff - run command
//gcc collisionDetection.c readInputsph.c readInputMesh.c -Wall -O3 -o coldet -lm
int main() {
	// Just a heads up,
	// I changed all "spheres" to "sph" and "sphereArr" to "sarr" -- trying to keep lines shorter
	// Still need Doxygen


	//What is the exact filenames/types and how should we read them? input arguments?
<<<<<<< HEAD
//	const char filename[] = "mesh.input.obj";
//	const char filename1[] = "spheres.input.csv";
//	const char filename[] = "box.obj";
//	const char filename1[] = "test_vercities.csv";
	const char filename[] = "2tri_test.obj";
	const char filename1[] = "1testsphere.csv";
=======

>>>>>>> 52dd45081d4f26022bd8e6e65610de86f9ab4273

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

//Reading inputs from "readInputsph.c" 
	int i,j;
	int n_cols = 3;
	double rad;
	int ns;
	double* sarr = readInputSpheres(filename1, &rad, &ns);		//sphere array


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
    		for (j = 0; j < n_cols; j++) {
      		printf("%lf ", sarr[i * n_cols + j]);
    		}
  	printf("\n");
  	}
	printf("End of sphere TESTING\n");

// Collision detection
// Need to compute all : 1st) - (point - plane)  ;  2nd) - (point - line)  ;  3rd) - (point - point), 

	// Computes point - point (distance from sphere center to each vertex of triangle)
	// d = sqrt((x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2)
	int sph, tri;
	double d1,d2,d3;
	double ax, ay, az, bx, by, bz, nxx, nyy, nzz, nx, ny, nz;	// normal vectors
	double pox, poy, poz, D, distance, distancecheck;	// distance and point on plane
//	double AB[3], BC[3], CA[3], PA[3], PB[3], PC[3];	// cross products to determine in point inside triangle


	float dotAC, dotACAB, dotACAP, dotAB, dotABAP, dottest, u, v;
	double test[3] = {1,2,3};
	double test1[3] = {2,3,4};

	for (sph = 0; sph < ns; sph++) {
		for (tri = 0; tri < nTriangles; tri++) {
			printf("\nSphere ID: %d  ---  Triangle ID: %d\n", sph, tri);
			printf("Distance to vertices\n");
			d1 = sqrt(pow((sarr[sph * n_cols + 0]-mesh[tri * 9 + 0]),2)+pow((sarr[sph * n_cols + 1]-mesh[tri * 9 + 1]),2)+pow((sarr[sph * n_cols + 2]-mesh[tri * 9 + 2]),2));
			printf("d1 = %f   ", d1);

			d2 = sqrt(pow((sarr[sph * n_cols + 0]-mesh[tri * 9 + 3]),2)+pow((sarr[sph * n_cols + 1]-mesh[tri * 9 + 4]),2)+pow((sarr[sph * n_cols + 2]-mesh[tri * 9 + 5]),2));
			printf("d2 = %f   ", d2);

			d3 = sqrt(pow((sarr[sph * n_cols + 0]-mesh[tri * 9 + 6]),2)+pow((sarr[sph * n_cols + 1]-mesh[tri * 9 + 7]),2)+pow((sarr[sph * n_cols + 2]-mesh[tri * 9 + 8]),2));
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

			// determining D for eq of plane
			D = -(nxx*mesh[tri * 9 + 0])-(nyy*mesh[tri * 9 + 1])-(nzz*mesh[tri * 9 + 2]);
//			printf("D = %f \n",D);

			// closest distance to plane
			distance = fabs((sarr[sph * 3 + 0]*nxx)+(sarr[sph * 3 + 1]*nyy)+(sarr[sph * 3 + 2]*nzz) + D)/sqrt(pow(nxx,2)+pow(nyy,2)+pow(nzz,2));

			printf("Distance to closest point on plane = %f \n",distance);

			//Projected point from P to closest point in plane P0
			pox = (sarr[sph * n_cols + 0]-(distance*nx));
			poy = (sarr[sph * n_cols + 1]-(distance*ny));
			poz = (sarr[sph * n_cols + 2]-(distance*nz));
			printf("New closest point on plane : (pox = %f , poy = %f , poz = %f) \n", pox, poy, poz);

			//verifying point accuracy, compare with distance
			distancecheck = sqrt(pow((sarr[sph * 3 + 0]-pox),2)+pow((sarr[sph * 3 + 1]-poy),2)+pow((sarr[sph * n_cols + 2]-poz),2));
			printf("Verify distance; d = %f   \n", distancecheck);

		// to determine if point is inside triangle -- building vectors
		// may not be necessary...


//			double AP[3] = {pox - mesh[tri * 9 + 0], poy - mesh[tri * 9 + 1], poz - mesh[tri * 9 + 2]};
//			double BP[3] = {pox - mesh[tri * 9 + 3], poy - mesh[tri * 9 + 4], poz - mesh[tri * 9 + 5]};
//			double CP[3] = {pox - mesh[tri * 9 + 6], poy - mesh[tri * 9 + 7], poz - mesh[tri * 9 + 8]};
			

			// nx = ay*bz - az*by  			;  ny = az*bx - ax*bz  		;  nz = ax*by - ay*bx
			// cross products
//			double ABAP[3] = {(AB[1]*AP[2]) - (AB[2]*AP[1]), (AB[2]*AP[0]) - (AB[0]*AP[2]), (AB[0]*AP[1]) - (AB[1]*AP[0])};
//			double BCBP[3] = {(BC[1]*BP[2]) - (BC[2]*BP[1]), (BC[2]*BP[0]) - (BC[0]*BP[2]), (BC[0]*BP[1]) - (BC[1]*BP[0])};
//			double CACP[3] = {(CA[1]*CP[2]) - (CA[2]*CP[1]), (CA[2]*CP[0]) - (CA[0]*CP[2]), (CA[0]*CP[1]) - (CA[1]*CP[0])};


//			printf("ABAP 1,2,3 = %f , %f , %f   \n", ABAP[0], ABAP[1], ABAP[2]);
//			printf("BCBP 1,2,3 = %f , %f , %f   \n", BCBP[0], BCBP[1], BCBP[2]);
//			printf("CACP 1,2,3 = %f , %f , %f   \n", CACP[0], CACP[1], CACP[2]);

		// testing if point inside of triangle

		
			double AB[3] = {mesh[tri * 9 + 3] - mesh[tri * 9 + 0], mesh[tri * 9 + 4] - mesh[tri * 9 + 1], mesh[tri * 9 + 5] - mesh[tri * 9 + 2]};
			double AC[3] = {mesh[tri * 9 + 6] - mesh[tri * 9 + 0], mesh[tri * 9 + 7] - mesh[tri * 9 + 1], mesh[tri * 9 + 8] - mesh[tri * 9 + 2]};
			double AP[3] = {pox - mesh[tri * 9 + 0], poy - mesh[tri * 9 + 1], poz - mesh[tri * 9 + 2]};

			//calc dot products
			dotAC = 0;
			dotACAB = 0;
			dotACAP = 0;
			dotAB = 0;
			dotABAP = 0;
		
			for (int dot = 0; dot < 3; dot++) {
				dotAC += AC[dot]*AC[dot];
				dotACAB += AC[dot]*AB[dot];
				dotACAP += AC[dot]*AP[dot];
				dotAB += AB[dot]*AB[dot];
				dotABAP += AB[dot]*AP[dot];
			}	

			u = ((dotAB * dotACAP) - (dotACAB * dotABAP)) / ((dotAC *dotAB)- (dotACAB*dotACAB));
			v = ((dotAC * dotABAP) - (dotACAB * dotACAP)) / ((dotAC *dotAB)- (dotACAB*dotACAB));
			printf("u = %f  v = %f\n", u,v);
			

			if (u >= 0 && v >= 0 && u+v <= 1) {
				printf("Projected point is on or in triangle (closest P)\n");
				// this is closed point, compare to radius
				// compare po to P with radius
				// return closest point
				if ( distance <= rad) {
					printf("SHPHERE TRIANGE INTERSECT: %d, %d\n",sph, tri);
				}

			}
				
			else {
				printf("Projected point is NOT on or in triangle\n");
			}
			
			// testing all point to all 3 lines
			
			double ab[3] = {mesh[tri * 9 + 3] - mesh[tri * 9 + 0], mesh[tri * 9 + 4] - mesh[tri * 9 + 1], mesh[tri * 9 + 5] - mesh[tri * 9 + 2]};
			double bc[3] = {mesh[tri * 9 + 6] - mesh[tri * 9 + 3], mesh[tri * 9 + 7] - mesh[tri * 9 + 4], mesh[tri * 9 + 8] - mesh[tri * 9 + 5]};
			double ca[3] = {mesh[tri * 9 + 0] - mesh[tri * 9 + 6], mesh[tri * 9 + 1] - mesh[tri * 9 + 7], mesh[tri * 9 + 2] - mesh[tri * 9 + 8]};
			// use po or p????			
			double ap[3] = {pox - mesh[tri * 9 + 0], poy - mesh[tri * 9 + 1], poz - mesh[tri * 9 + 2]};
			double bp[3] = {pox - mesh[tri * 9 + 3], poy - mesh[tri * 9 + 4], poz - mesh[tri * 9 + 5]};
			double cp[3] = {pox - mesh[tri * 9 + 6], poy - mesh[tri * 9 + 7], poz - mesh[tri * 9 + 8]};

			// need to loop through 3 lines
			double t0 = (ab[0]*ap[0])+(ab[1]*ap[1])+(ab[2]*ap[2]);
			double t1 = (bc[0]*bp[0])+(bc[1]*bp[1])+(bc[2]*bp[2]);
			double t2 = (ca[0]*cp[0])+(ca[1]*cp[1])+(ca[2]*cp[2]);
			printf("t0 , t1 , t2  =  %f , %f , %f \n", t0, t1, t2);
			if ((t0 <= 0 || t0 >= 1) && (t1 <= 0 || t1 >= 1) && (t2 <= 0 || t2 >= 1)){
				printf("Projected points are not on lines, go to vertices\n");
			}

			else {

				t0 = t0 / (ab[0]*ab[0])+(ab[1]*ab[1])+(ab[2]*ab[2]);
				t1 = t1 / (bc[0]*bc[0])+(bc[1]*bc[1])+(bc[2]*bc[2]);
				t2 = t2 / (ca[0]*ca[0])+(ca[1]*ca[1])+(ca[2]*ca[2]);
			double  pline0[3] = {mesh[tri * 9 + 0] + (t0*ab[0]), mesh[tri * 9 + 1] + (t0*ab[1]), mesh[tri * 9 + 2] + (t0*ab[2])};
			double  pline1[3] = {mesh[tri * 9 + 3] + (t1*bc[0]), mesh[tri * 9 + 4] + (t1*bc[1]), mesh[tri * 9 + 5] + (t1*bc[2])};
			double  pline2[3] = {mesh[tri * 9 + 6] + (t2*ca[0]), mesh[tri * 9 + 7] + (t2*ca[1]), mesh[tri * 9 + 8] + (t2*ca[2])};
				printf("Projected point on line is closest\n");
				printf("New closest point on line : (pline0 = %f ,  %f ,  %f) \n", pline0[0], pline0[1], pline0[2]);
				printf("New closest point on line : (pline1 = %f ,  %f ,  %f) \n", pline1[0], pline1[1], pline1[2]);
				printf("New closest point on line : (pline2 = %f ,  %f ,  %f) \n", pline2[0], pline2[1], pline2[2]);
			}

		}

	}


	//free values
	free(mesh);
	free(sarr);
	return 0;
}
