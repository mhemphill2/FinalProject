# FinalProject
Default Final Project for ME459

This repo is created by Michael Hemphill and Nikolaj Scharling Holm.

The program was created to detect collisions between a mesh consisting
of af number of triangles and a number of spheres with a given radius
and center point. 

The program was made as the final project concluding the course
ME459 lectured by Prof. Dan Negrut on UW-Madison fall 2019

##################################################################################

How can I run the program?

The program is built using CMake, making it easy to run the program on your own computer no matter which platform it is based on. Beneath are the instruction step to compile and run the program using a shell on a linux machine

Requirements
To build the program one must have at minimum version 2.6 of CMake installed. The program can be built using the command line or the CMake GUI. Note if you wish to build the program and run it on a windows computer using Visual Studio, the line reading: target_link_libraries(colDet m) must be changed to: target_link_libraries(colDet ${m}). 

The git repo should be public so there should be no issues attempting to clone it.

Steps

1.	Use the command: git clone to clone the repo from 
https://github.com/mhemphill2/FinalProject.git 
2.	Run cd FinalProject to change directory.
3.	Use the command: cd build, to change the directory again.
4.	Use the command: cmake .. to create a make file.
5.	Use the command: make to build the executable file.
6.	Run the command: ./colDet <filename.obj> <filename.csv>.

Note for step 6 that the user must type in the filenames manually. If one wish to run the program using the offered test files type in: ./colDet mesh.input.obj spheres.input.csv.

Options:

If a slurm workload manager is used, a default sbatchfile is located in the build directory. Running this after building the program using CMake, will start the program using the the input files already in the build directory,

If CMake is not available on the used computer, program can be build running following command:

gcc mainFunction.c collisionDetection.c readInputSpheres.c readInputMesh.c output-File.c -Wall -O3 -o coldet -lm

