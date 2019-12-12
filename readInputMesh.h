// Author: Nikolaj Holm
/**
* \details The function reads data from a file, containing a mesh built of 
* triangles, store it on the local machine and output a 1D array containing
* the data. The function alters the parameters **nTriangles** and 
* **nMeshEntries** during execution, based on the data. The filename must be
* given.
* 
* \param filname Pointer to an array of type char, that contains the filename.
* \param nTriangles Contains the number of triangles in the mesh.
* \param nMeshEntries Contains the number of total coordinates in the mesh.
*
* \return Entries Returns an array containing vertities
*
* Given a filename the function reads in a mesh consisting of triangles. 
* The file must be formatted as follows:
*
* - The first line contain the number of triangles.
* - All following lines come in sets of three. Each set of three lines 
*	represent one triangel.
* - Each of theese three lines contain a x,y and z coordinate representing each node in the triangle.
*
*/

#ifndef readInputMesh_H
#define readInputMesh_H

#include <stddef.h>

double* readInputMesh(const char* filename, int *nTriangles, int *nMeshEntries);

#endif
