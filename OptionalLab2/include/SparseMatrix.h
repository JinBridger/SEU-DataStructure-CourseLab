#pragma once
#include "MatrixTerm.h"

/* Sparse Matrix class
 * Using Matrix Term array as data
 */

class MatrixTerm;

class SparseMatrix {
public:
    // Constructor and destructor
    SparseMatrix(int, int, int);
    ~SparseMatrix();

    // Fast Transpose Algorithm
    // With only one colSize array
    SparseMatrix& fastTranspose();

    // Print the matrix in array form
    void print();

private:
    int         rowCnt, colCnt, nonZeroCnt;
    MatrixTerm* data;
};