#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readInputMesh.h"

double* readInputMesh(const char* filename, size_t* n_mesh, size_t* n_entries) {
	
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("Can't open file\n");
		return 1;
	}
	
	char str[56];
	int strl = 56;
	double n = atof(fgets(str, strl, fp));
	int entry = n * 3 * 3;
	//printf("entry= %d\n", entry);
	double* mesh = (double*)malloc(entry*sizeof(double));
	

	for (size_t i = 0; i < n*3; i++)
	{
		fgets(str, strl, fp);
		//printf("%s\n", str);
		char* token = strtok(str, ",");
		size_t j=0;
		while (token != NULL) {
			mesh[i * 3 + j] = atof(token);
			j++;
			token = strtok(NULL, ",");
		}
	}

	for(size_t i = 0; i < entry; i++)
	{
		printf("mesh[%zu]=%lf\n", i, mesh[i]);
	}

	fclose(fp);

	return mesh;
}