// Author: Michael Hemphill

#ifndef readInputSpheres_H
#define readInputSpheres_H

#include <stddef.h>

//Delete two upper if readInputSpheres works
double* InputSpheresradNS(const char* filename1);
double* InputSpheresCoord(const char* filename1);
double* readInputSpheres(const char* filename1, double* radius, int* nSpheres);

#endif
