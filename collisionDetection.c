#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "readInputMesh.h"
#include "readInputSpheres.h"
//temporary stuff - run command
//gcc collisionDetection.c readInputsph.c readInputMesh.c -Wall -O3 -o coldet -lm
int main() {

	const char filename[] = "mesh.input.obj";
	const char filename1[] = "spheres.input.csv";
//	const char filename[] = "box.obj";
//	const char filename1[] = "test_vercities.csv";
//	const char filename[] = "2tri_test.obj";
//	const char filename1[] = "1testsphere.csv";

	//Initialize mesh metrics
	int nTriangles = 0;
	int nMeshEntries = 0;
	double* mesh;

	//ReadInputMesh returning 1D array containing values
	mesh = readInputMesh(filename, &nTriangles, &nMeshEntries);

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
	printf("End of sphere TESTING\n\n");

// Collision detection
// Need to compute all : 1st) - (point - plane)  ;  2nd) - (point - line)  ;  3rd) - (point - point), 

	int sph, tri;
	double d1,d2,d3;
	double ax, ay, az, bx, by, bz, nxx, nyy, nzz, nx, ny, nz;	// normal vectors
	double pox, poy, poz, D, distance;	// distance and projected point on plane


	double dotAC, dotACAB, dotACAP, dotAB, dotABAP, u, v;

	for (sph = 0; sph < ns; sph++) {
		for (tri = 0; tri < nTriangles; tri++) {

// 1st) point - plane -- then detect if point inside triangle on plane


//			printf("\nSphere ID: %d  ---  Triangle ID: %d\n", sph, tri);


			//calculateing normal vector to triangle (p1, p2, p3)
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
//			printf("nx = %f  :  ny = %f  :  nz = %f\n", nx, ny, nz);

			// determining D for eq of plane
			D = -(nxx*mesh[tri * 9 + 0])-(nyy*mesh[tri * 9 + 1])-(nzz*mesh[tri * 9 + 2]);
//			printf("D = %f \n",D);

			// closest distance to plane
			distance = fabs((sarr[sph * 3 + 0]*nxx)+(sarr[sph * 3 + 1]*nyy)+(sarr[sph * 3 + 2]*nzz) + D)/sqrt(pow(nxx,2)+pow(nyy,2)+pow(nzz,2));
//			printf("Distance to closest point on plane = %f \n",distance);

			//Projected point from P to closest point in plane P0
			pox = (sarr[sph * n_cols + 0]-(distance*nx));
			poy = (sarr[sph * n_cols + 1]-(distance*ny));
			poz = (sarr[sph * n_cols + 2]-(distance*nz));
//			printf("Projected closest point on plane : (pox = %f , poy = %f , poz = %f) \n", pox, poy, poz);


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
//			printf("u = %f  v = %f\n", u,v);

			//detects if point is inside triangle
			if (u >= 0 && v >= 0 && u+v <= 1) {
//				printf("Projected closest point on plane : (pox = %f , poy = %f , poz = %f) \n", pox, poy, poz);
				// this is closest point, compare to radius
				// compare po to P with radius
				// return closest point
				if ( distance <= rad) {
					printf("DETECTED FROM POINT IN PLANE\n");
					printf("SPHERE TRIANGLE INTERSECT: %d, %d\n",sph, tri);
					printf("Projected closest point on plane : (pox = %f , poy = %f , poz = %f) \n\n", pox, poy, poz);
					//return ?????
				}

			}
				
			else if (u < 0 || v < 0 || u+v > 1) {
				
// 2nd) -- point - line : testing sphere point to all 3 lines			
			double ab[3] = {mesh[tri * 9 + 3] - mesh[tri * 9 + 0], mesh[tri * 9 + 4] - mesh[tri * 9 + 1], mesh[tri * 9 + 5] - mesh[tri * 9 + 2]};
			double bc[3] = {mesh[tri * 9 + 6] - mesh[tri * 9 + 3], mesh[tri * 9 + 7] - mesh[tri * 9 + 4], mesh[tri * 9 + 8] - mesh[tri * 9 + 5]};
			double ca[3] = {mesh[tri * 9 + 0] - mesh[tri * 9 + 6], mesh[tri * 9 + 1] - mesh[tri * 9 + 7], mesh[tri * 9 + 2] - mesh[tri * 9 + 8]};


			double ap[3] = {sarr[sph * n_cols + 0] - mesh[tri * 9 + 0], sarr[sph * n_cols + 1] - mesh[tri * 9 + 1], sarr[sph * n_cols + 2] - mesh[tri * 9 + 2]};
			double bp[3] = {sarr[sph * n_cols + 0] - mesh[tri * 9 + 3], sarr[sph * n_cols + 1] - mesh[tri * 9 + 4], sarr[sph * n_cols + 2] - mesh[tri * 9 + 5]};
			double cp[3] = {sarr[sph * n_cols + 0] - mesh[tri * 9 + 6], sarr[sph * n_cols + 1] - mesh[tri * 9 + 7], sarr[sph * n_cols + 2] - mesh[tri * 9 + 8]};


			double t0 = ((ab[0]*ap[0])+(ab[1]*ap[1])+(ab[2]*ap[2])) / ((ab[0]*ab[0])+(ab[1]*ab[1])+(ab[2]*ab[2]));
			double t1 = ((bc[0]*bp[0])+(bc[1]*bp[1])+(bc[2]*bp[2])) / ((bc[0]*bc[0])+(bc[1]*bc[1])+(bc[2]*bc[2]));
			double t2 = ((ca[0]*cp[0])+(ca[1]*cp[1])+(ca[2]*cp[2])) / ((ca[0]*ca[0])+(ca[1]*ca[1])+(ca[2]*ca[2]));
//			printf("t0 , t1 , t2  =  %f , %f , %f \n", t0, t1, t2);


			double  pline0[3] = {mesh[tri * 9 + 0] + (t0*ab[0]), mesh[tri * 9 + 1] + (t0*ab[1]), mesh[tri * 9 + 2] + (t0*ab[2])};
			double  pline1[3] = {mesh[tri * 9 + 3] + (t1*bc[0]), mesh[tri * 9 + 4] + (t1*bc[1]), mesh[tri * 9 + 5] + (t1*bc[2])};
			double  pline2[3] = {mesh[tri * 9 + 6] + (t2*ca[0]), mesh[tri * 9 + 7] + (t2*ca[1]), mesh[tri * 9 + 8] + (t2*ca[2])};
//				printf("Projected point on line is closest\n");
//				printf("New closest point on line : (pline0 = %f ,  %f ,  %f) \n", pline0[0], pline0[1], pline0[2]);
//				printf("New closest point on line : (pline1 = %f ,  %f ,  %f) \n", pline1[0], pline1[1], pline1[2]);
//				printf("New closest point on line : (pline2 = %f ,  %f ,  %f) \n", pline2[0], pline2[1], pline2[2]);
//			}

			// calc distance from P to pline
			double distpline0 = sqrt(pow((sarr[sph * 3 + 0]-pline0[0]),2)+pow((sarr[sph * 3 + 1]-pline0[1]),2)+pow((sarr[sph * n_cols + 2]-pline0[2]),2));
			double distpline1 = sqrt(pow((sarr[sph * 3 + 0]-pline1[0]),2)+pow((sarr[sph * 3 + 1]-pline1[1]),2)+pow((sarr[sph * n_cols + 2]-pline1[2]),2));
			double distpline2 = sqrt(pow((sarr[sph * 3 + 0]-pline2[0]),2)+pow((sarr[sph * 3 + 1]-pline2[1]),2)+pow((sarr[sph * n_cols + 2]-pline2[2]),2));
//			printf("Distance to closest point on : line 1 = %f , line 2 = %f ,  line 3 = %f \n",distpline0, distpline1, distpline2);

			if (((t0 > 0 && t0 < 1) && distpline0 <= rad) || ((t1 > 0 && t1 < 1) && distpline1 <= rad) || ((t2 > 0 && t2 < 1) && distpline2 <= rad)) {
				printf("DETECTED FROM POINT TO LINE\n");
				printf("SPHERE TRIANGLE INTERSECT: %d, %d\n",sph, tri);				
				printf("Projected points on line : (%f,  %f,  %f) ; (%f,  %f,  %f) ; (%f,  %f,  %f)\n", pline0[0], pline0[1], pline0[2], pline1[0], pline1[1], pline1[2], pline2[0], pline2[1], pline2[2]);
				printf("Distances to lines: %f ; %f ; %f \n\n",distpline0, distpline1, distpline2);

				//return ?????
			}

// 3rd) point - point
			else if ((t0 <= 0 || t0 >= 1) && (t1 <= 0 || t1 >= 1) && (t2 <= 0 || t2 >= 1)){
			
			// Computes point - point (distance from sphere center to each vertex of triangle)
//			printf("Distance to vertices\n");
			d1 = sqrt(pow((sarr[sph * n_cols + 0]-mesh[tri * 9 + 0]),2)+pow((sarr[sph * n_cols + 1]-mesh[tri * 9 + 1]),2)+pow((sarr[sph * n_cols + 2]-mesh[tri * 9 + 2]),2));
//			printf("d1 = %f   ", d1);

			d2 = sqrt(pow((sarr[sph * n_cols + 0]-mesh[tri * 9 + 3]),2)+pow((sarr[sph * n_cols + 1]-mesh[tri * 9 + 4]),2)+pow((sarr[sph * n_cols + 2]-mesh[tri * 9 + 5]),2));
//			printf("d2 = %f   ", d2);

			d3 = sqrt(pow((sarr[sph * n_cols + 0]-mesh[tri * 9 + 6]),2)+pow((sarr[sph * n_cols + 1]-mesh[tri * 9 + 7]),2)+pow((sarr[sph * n_cols + 2]-mesh[tri * 9 + 8]),2));
//			printf("d3 = %f\n", d3);
			

			if ( d1 <= rad || d2 <= rad || d3 <= rad) {
				printf("DETECTED FROM POINT TO VERTICES\n");
				printf("SPHERE TRIANGLE INTERSECT: %d, %d\n",sph, tri);
				printf("Distances to vertices: %f ; %f ; %f \n\n",d1, d2, d3);
				//return ?????

			}
			}
			}
		}

	}

	//free values
	free(mesh);
	free(sarr);
	return 0;
}
