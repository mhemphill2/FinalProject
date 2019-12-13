//Author Nikolaj Holm & Michael Hemphill

/**
* \details The outpuFile function take in an array and a count of collisions detected.
*It creates or alters a file called "collision_detection.out" and write the sphere and mesh ID's in that order.
*
*
* \param *collisions Pointer to the array, storring ID's of colliding spheres and triangles.
* \param count Count variable holding the number of collisions between the mesh and spheres.
*
* **output**: A file containing sphere and Triangle ID's.
*
* The format of the output file is:
*
* - The first line reads: "s,t"
* - The following lines read "<sphere ID>, <Triangle ID>"
*
*/
#ifndef outputFile_H
#define outputFile_H

#include <stddef.h>

int* outputFile(int *collisions, int count);

#endif
