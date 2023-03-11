#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "newton.h"
#include "f.h"
#ifdef VECTORIZE
const int n = 1;
double* fvect(double*);
#endif
int write_result(int, double*, const char*);
int main(int argc, char* argv[])
{
	int nmax, i;
	double* x;
	double* zero;
	nmax = 1000;
	if(argc > 1)
	{
		if(atoi(argv[1]) > 0)
		{
			nmax = atoi(argv[1]);
		}
		else
		{
			printf("Warning! Using NMAX = %d\n", nmax);
		}
	}
	x = (double*)malloc(n * sizeof(double));
	#ifdef VECTORIZE
	newton(n, fvect, nmax, &x0, x);
	printf("x = %lf\n", x[0]);
	zero = fvect(x);
	#else
	newton(n, f, nmax, x0, x);
	zero = f(x);
	#endif
	printf("|f(x)| = %lf\n", norm(n, zero));
	free(zero);
	write_result(n, x, "result.dat");
	free(x);
	return 0;
}


#ifdef VECTORIZE
double* fvect(double* x)
{
	double* res;
	res = (double*)malloc(sizeof(double));
	res[0] = f(x[0]);
	return res;
}
#endif


int write_result(int n, double* x, const char* filename)
{
	FILE *fp;
	int i;
	if((fp = fopen(filename, "w")) == NULL)
	{
		return -1;
	}
	for(i = 0; i < n; i++)
	{
		fprintf(fp, "%lf\n", x[i]);
	}
	fclose(fp);
	return 0;
}


