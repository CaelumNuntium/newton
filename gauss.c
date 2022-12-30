#include <stdio.h>
#include <stdlib.h>
int PRINT_WARNINGS = 1;
const double eps = 1e-6;
void gauss(int type, int n, double* a, double* b, double* x)
{
	double* aint;
	double* acur;
	double* aacur;
	int* e;
	int i, j, m, k, p, q;
	double a0, a1, max, tmp;
	m = n + 1;
	aint = (double*)malloc(m * n * sizeof(double));
	for(i = 0; i < n; i++)
	{
		acur = aint + i * m;
		aacur = a + i * n;
		for(j = 0; j < n; j++)
		{
			acur[j] = aacur[j];
		}
		acur[n] = b[i];
	}
	switch(type)
	{
		case 1:
			for(k = 0; k < n; k++)
			{
				aacur = aint + k * m;
				a0 = aacur[k];
				if(a0 < eps && a0 > -eps && PRINT_WARNINGS)
				{
					printf("WARNING: The leading element is close to 0!\n");
				}
				for(j = k; j < m; j++)
				{
					aacur[j] /= a0;
				}
				for(i = k + 1; i < n; i++)
				{
					acur = aint + i * m;
					a1 = acur[k];
					for(j = k; j < m; j++)
					{
						acur[j] -= aacur[j] * a1;
					}
				}
			}
			for(i = n - 1; i > -1; i--)
			{
				acur = aint + i * m;
				x[i] = acur[n];
				for(j = i + 1; j < n; j++)
				{
					x[i] -= acur[j] * x[j];
				}
			}
			break;
		case 2:
			for(k = 0; k < n; k++)
			{
				aacur = aint + k * m;
				a0 = aacur[k];
				if(a0 < eps && a0 > -eps && PRINT_WARNINGS)
				{
					printf("WARNING: The leading element is close to 0!\n");
				}
				for(j = k; j < m; j++)
				{
					aacur[j] /= a0;
				}
				for(i = 0; i < k; i++)
				{
					acur = aint + i * m;
					a1 = acur[k];
					for(j = k; j < m; j++)
					{
						acur[j] -= aacur[j] * a1;
					}
				}
				for(i = k + 1; i < n; i++)
				{
					acur = aint + i * m;
					a1 = acur[k];
					for(j = k; j < m; j++)
					{
						acur[j] -= aacur[j] * a1;
					}
				}
			}
			for(i = 0; i < n; i++)
			{
				x[i] = aint[i * m + n];
			}
			break;
		case 3:
			e = (int*)malloc(n * sizeof(int));
			for(k = 0; k < n; k++)
			{
				max = aint[k * m + k];
				p = k;
				q = k;
				for(i = k; i < n; i++)
				{
					acur = aint + i * m;
					for(j = k; j < n; j++)
					{
						if(acur[j] > max)
						{
							max = acur[j];
							p = i;
							q = j;
						}
					}
				}
				e[k] = q;
				acur = aint + p * m;
				aacur = aint + k * m;
				for(i = 0; i < m; i++)
				{
					tmp = acur[i];
					acur[i] = aacur[i];
					aacur[i] = tmp;
				}
				for(i = 0; i < n; i++)
				{
					acur = aint + i * m;
					tmp = acur[q];
					acur[q] = acur[k];
					acur[k] = tmp;
				}
				a0 = aacur[k];
				for(j = k; j < m; j++)
				{
					aacur[j] /= a0;
				}
				for(i = 0; i < k; i++)
				{
					acur = aint + i * m;
					a1 = acur[k];
					for(j = k; j < m; j++)
					{
						acur[j] -= aacur[j] * a1;
					}
				}
				for(i = k + 1; i < n; i++)
				{
					acur = aint + i * m;
					a1 = acur[k];
					for(j = k; j < m; j++)
					{
						acur[j] -= aacur[j] * a1;
					}
				}
			}
			for(i = 0; i < n; i++)
			{
				x[i] = aint[i * m + n];
			}
			for(i = n - 1; i >= 0; i--)
			{
				tmp = x[i];
				x[i] = x[e[i]];
				x[e[i]] = tmp;
			}
			free(e);
			break;
		case 4:
			e = (int*)malloc(n * sizeof(int));
			for(k = 0; k < n; k++)
			{
				max = aint[k * m + k];
				p = k;
				q = k;
				for(i = k; i < n; i++)
				{
					acur = aint + i * m;
					for(j = k; j < n; j++)
					{
						if(acur[j] > max)
						{
							max = acur[j];
							p = i;
							q = j;
						}
					}
				}
				e[k] = q;
				acur = aint + p * m;
				aacur = aint + k * m;
				for(i = 0; i < m; i++)
				{
					tmp = acur[i];
					acur[i] = aacur[i];
					aacur[i] = tmp;
				}
				for(i = 0; i < n; i++)
				{
					acur = aint + i * m;
					tmp = acur[q];
					acur[q] = acur[k];
					acur[k] = tmp;
				}
				a0 = aacur[k];
				for(j = k; j < m; j++)
				{
					aacur[j] /= a0;
				}
				for(i = k + 1; i < n; i++)
				{
					acur = aint + i * m;
					a1 = acur[k];
					for(j = k; j < m; j++)
					{
						acur[j] -= aacur[j] * a1;
					}
				}
			}
			for(i = n - 1; i > -1; i--)
			{
				acur = aint + i * m;
				x[i] = acur[n];
				for(j = i + 1; j < n; j++)
				{
					x[i] -= acur[j] * x[j];
				}
			}
			for(i = n - 1; i >= 0; i--)
			{
				tmp = x[i];
				x[i] = x[e[i]];
				x[e[i]] = tmp;
			}
			free(e);
			break;
	}
	free(aint);
}

