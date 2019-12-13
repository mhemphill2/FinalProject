#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {

	//rand triangles
	const char filename[] = "test_tri.obj";
	FILE* fp = fopen(filename, "w");
	int nt = 30;
	double Arandt,Brandt,Crandt,At,Bt,Ct;
	fprintf(fp, "%d\n", nt);
	for (int i = 0; i < nt*3; i++)
	{
		Arandt = rand()%2001;
		Brandt = rand()%2001;
		Crandt = rand()%2001;
	        At = Arandt-1000;
	        Bt = Brandt-1000;
	        Ct = Crandt-1000;
		fprintf(fp, "%f,%f,%f\n", At, Bt, Ct);
	}
	fclose(fp);

	// rand spheres
	const char filename1[] = "test_sphere.csv";
	FILE* fp1 = fopen(filename1, "w");
	double r = 5;
	int n = 10;
	double Arand,Brand,Crand,A,B,C;
	fprintf(fp, "x,y,z\n");
	fprintf(fp, "%f\n", r);
	fprintf(fp, "%d\n", n);
	for (int i = 0; i < n; i++)
	{
		Arand = rand()%2001;
		Brand = rand()%2001;
		Crand = rand()%2001;
	        A = Arand-1000;
	        B = Brand-1000;
	        C = Crand-1000;
		fprintf(fp, "%f,%f,%f\n", A, B, C);
	}


	fclose(fp1);
	return 0;
}

