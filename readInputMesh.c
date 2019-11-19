#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define buff 1028;

double* readInputMesh(const char* filename) {
	printf("hul igennem\n");
	
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("Can't open file\n");
		return 1;
	}

	char str[5];
	size_t strl = 0;

	float n = atof(fgets(str, 1028, fp));
	printf("n= %lf\n", n);

	for (size_t i = 0; i < n * 3; i++) {

	}
	//is it best to load it in to 9 or three columns?
	while (fgets(str,strl,fp))	{
		if (strlen(str) > strl) {
			strl = strlen(str);
			continue;
		}
		printf("str len = %d\n",strlen(str));
	}


	return 0;
}