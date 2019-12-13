//Authors: Michael Hemphill & Nikolaj Scharling Holm
/**
* \details This function computes collisions between a mesh and a number of 
* spheres with a given radius. The collision detection considers all three
* options for collisons including colliding through the plane inside the
* triangle, colliding through a vertex of the triangle, and 
* colliding through a line of the triangle.
* 
*
* \param *mesh A pointer to a 1D array storing the nodes in the mesh
* \param nTriangles The number of triangles constructed by the mesh nodes
* \param *sarr A Pointer to a 1D array storing the center points of the spheres
* \param ns The number of spheres
* \param rad The sphere radius
* \param *count A variable counting the number of collisions, which is returned
* to the main function
* 
* The function returns a pointer to an array containing the ID's of colliding triangles and 
*spheres corrosponding to the order they appear in the input files.
*
*/
#ifndef outputFile_H
#define outputFile_H

#include <stddef.h>

int* collisionDetection(double* mesh, int nTriangles, double* sarr, int ns, double rad, int* count);

#endif
