#define VECTORIZE // If f(x) is a scalar function, put "#define VECTORIZE" here
double f(double x) // Function f(x) must return double type value or double* pointer
{
	double n = 1.31;
	return 1 - (sqrt(3.0) * sin(x) * cos(x) / 2.0 / sqrt(n * n - sin(x) * sin(x)) + 0.5 * cos(x)) / sqrt(1 - (0.5 * sin(x) - sqrt(3.0) / 2 * sqrt(n * n - sin(x) * sin(x))) * (0.5 * sin(x) - sqrt(3.0) / 2 * sqrt(n * n - sin(x) * sin(x))));
}

double x0 = 0.7; // x0 is the initial estimate