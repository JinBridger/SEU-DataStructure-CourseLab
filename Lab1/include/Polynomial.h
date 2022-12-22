#pragma once
#include <iostream>

class Polynomial {
public:
	Polynomial(int deg, double* coef);
	Polynomial(int deg);
	~Polynomial();

	// Add New Term
	void AddTerm(double coef, int exp);

	// Using iteration
	double F1a(double x);
	double F2a(double x);

	// Using recursion
	double F1b(double x, int n = 0, double pow_x = 1);
	double F2b(double x, int n = 0);

private:
	// Highest exponent
	int m_degree;

	// Coefficients
	double* m_coef;
};