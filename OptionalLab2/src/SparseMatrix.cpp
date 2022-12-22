#include "SparseMatrix.h"

#include <iostream>

// Constructor and destructor
SparseMatrix::SparseMatrix(int r, int c, int n) : rowCnt(r), colCnt(c), nonZeroCnt(n) {
    data = new MatrixTerm[n];

    std::cout << "Please input the row, col, val of elements:" << std::endl;

    for (int i = 0; i < n; ++i) {
        std::cin >> data[i].row;
        std::cin >> data[i].col;
        std::cin >> data[i].value;
    }

    std::cout << "Input finished..." << std::endl;
}

SparseMatrix::~SparseMatrix() {
    delete[] data;
}

// Fast Transpose Algorithm
// With only one colSize array
SparseMatrix& SparseMatrix::fastTranspose() {
    // The colSize array
    int* colSize = new int[colCnt];
    // The new Data
    MatrixTerm* newData = new MatrixTerm[nonZeroCnt];
    // Init to all 0
    for (int i = 0; i < colCnt; ++i) {
        colSize[i] = 0;
    }
    // Calculate the colSize
    for (int i = 0; i < nonZeroCnt; ++i) {
        colSize[data[i].col]++;
    }

    // Convert colSize to colStart
    int curColStart = 0;
    int nxtColSize  = 0;
    for (int i = 0; i < colCnt; ++i) {
        curColStart += colSize[i];
        colSize[i] = nxtColSize;
        nxtColSize = curColStart;
    }

    // Use colSize as colStart
    for (int i = 0; i < nonZeroCnt; ++i) {
        int newIndex            = colSize[data[i].col]++;
        newData[newIndex].col   = data[i].row;
        newData[newIndex].row   = data[i].col;
        newData[newIndex].value = data[i].value;
    }

    // Update data
    delete[] data;
    delete[] colSize;
    data = newData;

    return *this;
}

// Print the matrix in array form
void SparseMatrix::print() {
    std::cout << "Printing the Sparse Matrix..." << std::endl;
    std::cout << "row\tcol\tvalue" << std::endl;

    for (int i = 0; i < nonZeroCnt; ++i) {
        std::cout << data[i].row << "\t";
        std::cout << data[i].col << "\t";
        std::cout << data[i].value << std::endl;
    }
}
