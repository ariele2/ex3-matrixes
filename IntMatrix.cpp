#include "IntMatrix.h"
#include <assert.h>


mtm::IntMatrix::IntMatrix(Dimensions dims, int value = 0): 
    dims(dims), data(new int[dims.getRow()*dims.getCol()])
 { 
     for (int i=0; i<dims.getRow()*dims.getCol(); i++) {
         data[i] = value;
     }
 }

mtm::IntMatrix::IntMatrix(const IntMatrix& matrix):
    dims(matrix.dims), data (new int[dims.getRow()*dims.getCol()])
 {
     for (int i=0; i<dims.getRow()*dims.getCol(); i++) {
         data[i] = matrix.data[i];
     }
 }

mtm::IntMatrix::~IntMatrix() {
    delete[] this->data;
}

mtm::IntMatrix& mtm::IntMatrix::operator=(const IntMatrix& matrix) {
    if (this == &matrix) {
        return *this;
    }
    delete[] this->data;
    this->data = new int[matrix.dims.getRow()*matrix.dims.getCol()];
    this->dims = matrix.dims;
    for(int i=0; i<dims.getRow() * dims.getCol(); i++) {
        data[i] = matrix.data[i];
    }
    return *this;
}

mtm::IntMatrix& Identity(int size) {
    mtm::Dimensions dims(size,size);
    mtm::IntMatrix identity(dims);
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            if (i == j) {
                identity(i,j) = 1;
            }
        }
    }
    return identity;
}

int mtm::IntMatrix::height() {
    return this->dims.getRow();
}

int mtm::IntMatrix::width() {
    return this->dims.getCol();
}

int mtm::IntMatrix::size() {
    return (this->dims.getRow() * this->dims.getCol());
}

int& mtm::IntMatrix::operator()(int row, int col) {
    assert(row >= 0 && row < dims.getRow() && col >= 0 && col < dims.getCol());
    return data[dims.getCol()*row + col];
}

// try to check if the returned data is right, considering that the indexing starts from 0
const int& mtm::IntMatrix::operator()(int row, int col) const {
    assert(row >= 0 && row < dims.getRow() && col >= 0 && col < dims.getCol());
    return data[dims.getCol()*row + col];
}

mtm::IntMatrix& mtm::IntMatrix::transpose() {
    mtm::Dimensions trans_dims(dims.getCol(),dims.getRow());
    mtm::IntMatrix trans_matrix(trans_dims);
    for (int i=0; i<dims.getRow(); i++) {
        for (int j=0; j<dims.getCol(); j++) {
            trans_matrix(j,i) = (*this)(i,j);
        }
    }
}