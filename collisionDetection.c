#include <stdio.h>
#include <stdlib.h>
#include "readInputMesh.h"

int main() {

	size_t *n_mesh;
	size_t* n_entries;
	const char filename[] = "input.obj";
	readInputMesh(filename, n_mesh, n_entries);

	return 0;
}
