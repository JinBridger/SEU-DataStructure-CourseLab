#include "Polynomial.h"

Polynomial::Polynomial(int deg, double* coef) : m_degree(deg) {
	// Construct with given degree and coeff
	m_coef = new double[deg + 1];
	for (int i = 0; i <= deg; ++i) {
		m_coef[i] = coef[i];
	}
}

Polynomial::Polynomial(int deg) : m_degree(deg) {
	// Construct with given degree
	m_coef = new double[deg + 1];
	for (int i = 0; i <= deg; ++i) {
		m_coef[i] = rand() % 10;
	}
}

Polynomial::~Polynomial() {
	// Release memory
	delete[] m_coef;
}

void Polynomial::AddTerm(double coef, int exp) {
	if (exp > m_degree) {
		double* tmp_coef = new double[exp + 1];
		for (int i = 0; i <= m_degree; ++i)
			tmp_coef[i] = m_coef[i];
		tmp_coef[exp - 1] += coef;
		delete[] m_coef;
		m_coef = tmp_coef;
	}
	else {
		m_coef[exp - 1] += coef;
	}
}

// Using iteration
double Polynomial::F1a(double x) {
	double res = 0;
	double power = 1;
	for (int i = 0; i <= m_degree; ++i) {
		res += power * m_coef[i];
		power *= x;
	}
	return res;
}
double Polynomial::F2a(double x) {
	double res = m_coef[m_degree];
	for (int i = m_degree - 1; i >= 0; --i) {
		res *= x;
		res += m_coef[i];
	}
	return res;
}

// Using recursion
double Polynomial::F1b(double x, int n, double pow_x) {
	if (n == m_degree) {
		return m_coef[m_degree] * pow_x;
	}
	return m_coef[n] * pow_x + F1b(x, n + 1, pow_x * x);
}
double Polynomial::F2b(double x, int n) {
	if (n == m_degree) {
		return m_coef[m_degree];
	}
	return m_coef[n] + x * F2b(x, n + 1);
}