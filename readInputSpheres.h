// Author: Michael Hemphill
/**
* \details The function reads data from a file with a given filename. 
* The data is stored and return a 1D array containing the sphere
* coordinates. The function alters the parameters **radius** and **nSpheres** 
* based on the data.
*
* \param filname1 Pointer to an array of type char, that contains the filename.
* \param radius Contains the number of triangles in the mesh.
* \param nSpheres Contains the number of total coordinates in the mesh.
*
* \return Entries Returns an array containing sphere coordinates
*
* Given a filename the function reads in a list of sphere coordinates.
* The file must be formatted as follows:
*
* - The first line contains a header "x,y,z".
* - The next line contain the sphere radius.
* - The third line contain the number of spheres.
* - All following lines contain a x,y and z coordinate representing the center
* of each sphere.
*
*
*/

#ifndef readInputSpheres_H
#define readInputSpheres_H

#include <stddef.h>

double* readInputSpheres(const char* filename1, double* radius, int* nSpheres);

#endif
