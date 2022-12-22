// Disable Visual Studio's freopen_s
// If you are NOT using Visual Studio
// Please COMMIT this line
#define _CRT_SECURE_NO_WARNINGS

#include "SparseMatrix.h"

#include <fstream>
#include <iostream>

int main() {
    // Open the input file and redirect std::cin to this
    freopen("res\\input.txt", "r", stdin);

    SparseMatrix test(5, 5, 5);
    test.print();
    std::cout << "Transposing..." << std::endl;
    test.fastTranspose();
    test.print();
}