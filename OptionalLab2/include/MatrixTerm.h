#pragma once
#include "SparseMatrix.h"

/* Matrix Term class
 * Store the matrix element
 */

class MatrixTerm {
    friend class SparseMatrix;

public:
    MatrixTerm() = default;
    MatrixTerm(int, int, int);

private:
    int row, col, value;
};