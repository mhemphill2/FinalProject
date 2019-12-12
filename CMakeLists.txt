#author: Nikolaj Scharling Holm, HW05 me459
cmake_minimum_required(VERSION 2.6)
project(finalProj)
SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -O3 -o -g")
add_executable(colDet mainFunction.c collisionDetection.c readInputMesh.c readInputSpheres.c outputFile.c)
target_link_libraries(colDet m)
