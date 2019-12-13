#!/usr/bin/env bash
#SBATCH --job-name=coldet
#SBATCH --partition=wacc
#SBATCH --time=0-0:5:00
#SBATCH --cpus-per-task=1
#SBATCH --output="coldetoutput.txt"

################################
# Add your bash commands below #
################################

gcc mainFunction.c collisionDetection.c readInputSpheres.c readInputMesh.c outputFile.c -Wall -O3 -o colDet -lm
./colDet mesh.input.obj spheres.input.csv
