#include <iostream>
#include <random>
#include <ctime>
#include <iomanip>

#include "Polynomial.h"

int n_num[] = { 1, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100 };

// Calculation f3 with F1a, F2a, F1b, F2b
// Print time cost
void f3(double x, int n) {

	// Load coef
	double* coef_array = new double[n + 1];
	double ret;
	coef_array[0] = 1;
	for (int i = 1; i <= n; ++i) {
		coef_array[i] = double(1) / i;
	}

	// Init polynomial
	Polynomial poly = Polynomial(n, coef_array);

	double startF1a, endF1a, timeF1a;
	double startF2a, endF2a, timeF2a;
	double startF1b, endF1b, timeF1b;
	double startF2b, endF2b, timeF2b;

	startF1a = clock();
	for (int cnt = 0; cnt < 1000000; ++cnt)
		poly.F1a(x);
	endF1a = clock();
	timeF1a = (endF1a - startF1a) / CLOCKS_PER_SEC;

	startF2a = clock();
	for (int cnt = 0; cnt < 1000000; ++cnt)
		poly.F2a(x);
	endF2a = clock();
	timeF2a = (endF2a - startF2a) / CLOCKS_PER_SEC;

	startF1b = clock();
	for (int cnt = 0; cnt < 1000000; ++cnt)
		poly.F1b(x);
	endF1b = clock();
	timeF1b = (endF1b - startF1b) / CLOCKS_PER_SEC;

	startF2b = clock();
	for (int cnt = 0; cnt < 1000000; ++cnt)
		poly.F2b(x);
	endF2b = clock();
	timeF2b = (endF2b - startF2b) / CLOCKS_PER_SEC;

	// Print time cost
	std::cout << "|" << n << "\t|";
	std::cout << std::fixed << std::setprecision(3) << timeF1a << "\t|";
	std::cout << std::fixed << std::setprecision(3) << timeF2a << "\t|";
	std::cout << std::fixed << std::setprecision(3) << timeF1b << "\t|";
	std::cout << std::fixed << std::setprecision(3) << timeF2b << "\t|";
	std::cout << std::fixed << std::setprecision(5) << poly.F1a(x) << "\t|" << std::endl;

	// Release memory
	delete[] coef_array;
}

int main() {

	std::cout << "Coeff: {";
	double coef_1[6];
	for (int i = 0; i < 5; ++i) {
		coef_1[i] = rand() % 10;
		std::cout << coef_1[i] << ", ";
	}
	coef_1[5] = rand() % 10;
	std::cout << coef_1[5] << "}" << std::endl;

	Polynomial test(5);
	std::cout << "F1a: " << test.F1a(3) << std::endl;
	std::cout << "F2a: " << test.F2a(3) << std::endl;
	std::cout << "F1b: " << test.F1b(3) << std::endl;
	std::cout << "F2b: " << test.F2b(3) << std::endl;

	std::cout << std::endl << std::endl;

	std::cout << "Time cost: (us)" << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << "|n\t|F1a\t|F2a\t|F1b\t|F2b\t|Value\t\t|" << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
	for (int i = 0; i < 16; ++i)
		f3(1.1, n_num[i]);
	std::cout << "---------------------------------------------------------" << std::endl;
}