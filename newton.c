#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "newton.h"
const double newton_eps = 1e-7;
const double h = 1e-7;
void newton(int n, double* (*f)(double*), int nmax, double* x0, double* x)
{
	int i, j, k;
	double* tmp;
	double* mdiff;
	double* b;
	double* cur;
	double bcur;
	double* ftmp;
	tmp = (double*)malloc(n * sizeof(double));
	mdiff = (double*)malloc(n * n * sizeof(double));
	b = (double*)malloc(n * sizeof(double));
	for(i = 0; i < n; i++)
	{
		tmp[i] = x0[i];
	}
	for(k = 0; k < nmax; k++)
	{
		diff(f, tmp, n, mdiff);
		ftmp = f(tmp);
		for(i = 0; i < n; i++)
		{
			cur = mdiff + i * n;
			bcur = 0;
			for(j = 0; j < n; j++)
			{
				bcur += cur[j] * tmp[j];
			}
			b[i] = bcur - ftmp[i];
		}
		free(ftmp);
		gauss(4, n, mdiff, b, x);
		for(i = 0; i < n; i++)
		{
			tmp[i] -= x[i];
		}
		if(norm(n, tmp) < newton_eps)
		{
			break;
		}
		for(i = 0; i < n; i++)
		{
			tmp[i] = x[i];
		}
	}
	free(tmp);
	free(mdiff);
	free(b);
}

void diff(double* (*f)(double*), double* x, int n, double* res)
{
	int i, j, k;
	double* cur;
	double* f1;
	double* f2;
	double* x1;
	double* x2;
	x1 = (double*)malloc(n * sizeof(double));
	x2 = (double*)malloc(n * sizeof(double));
	for(i = 0; i < n; i++)
	{
		x1[i] = x[i];
		x2[i] = x[i];
	}
	for(i = 0; i < n; i++)
	{
		cur = res + i * n;
		for(j = 0; j < n; j++)
		{
			x1[j] -= h;
			x2[j] += h;
			f1 = f(x1);
			f2 = f(x2);
			cur[j] = (f2[i] - f1[i]) / h / 2;
			free(f1);
			free(f2);
			x1[j] = x[j];
			x2[j] = x[j];
		}
	}
	free(x1);
	free(x2);
}

double norm(int n, double* a)
{
	int i;
	double res;
	res = 0;
	for(i = 0; i < n; i++)
	{
		res += (a[i] * a[i]);
	}
	return sqrt(res);
}

