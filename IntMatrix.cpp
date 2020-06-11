#include "IntMatrix.h"


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

int* mtm::IntMatrix::getData(const IntMatrix& matrix) {
    return matrix.data;
}

mtm::IntMatrix& Identity(int size) {
    mtm::Dimensions dims(size,size);
    mtm::IntMatrix identity(dims);
    for (int i=0; i<dims.getRow()*dims.getCol(); i+=dims.getCol()+1) {
            mtm::IntMatrix::getData(identity)[i] = 1;
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
