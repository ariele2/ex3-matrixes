#include "IntMatrix.h"
#include <assert.h>


mtm::IntMatrix::IntMatrix(Dimensions dims, int value): 
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

mtm::IntMatrix mtm::IntMatrix::Identity(int size) {
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

int mtm::IntMatrix::height() const {
    return this->dims.getRow();
}

int mtm::IntMatrix::width() const {
    return this->dims.getCol();
}

int mtm::IntMatrix::size() const {
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

mtm::IntMatrix mtm::IntMatrix::transpose() const {
    mtm::Dimensions trans_dims(dims.getCol(),dims.getRow());
    mtm::IntMatrix trans_matrix(trans_dims);
    for (int i=0; i<dims.getRow(); i++) {
        for (int j=0; j<dims.getCol(); j++) {
            trans_matrix(j,i) = (*this)(i,j);
        }
    }
    return trans_matrix;
}

mtm::IntMatrix mtm::operator+(const IntMatrix& matrix1, const IntMatrix& matrix2) {
    assert(matrix1.height() == matrix2.height() && matrix1.width() == matrix2.width());
    mtm::Dimensions sum_dims(matrix1.height(), matrix1.width());
    mtm::IntMatrix sum_matrix(sum_dims);
    for (int i=0; i<sum_matrix.height(); i++) {
        for (int j=0; j<sum_matrix.width(); j++) {
            sum_matrix(i,j) = matrix1(i,j) + matrix2(i,j);
        }
    }
    return sum_matrix;
}

mtm::IntMatrix mtm::IntMatrix::operator-() const {
    mtm::IntMatrix new_matrix(this->dims);
    for (int i=0; i<dims.getRow(); i++) {
        for (int j=0; j<dims.getCol(); j++) {
            new_matrix(i,j) = -(*this)(i,j);
        }
    }
    return new_matrix;
}

mtm::IntMatrix mtm::operator-(const IntMatrix& matrix1, const IntMatrix& matrix2) {
    assert(matrix1.height() == matrix2.height() && matrix1.width() == matrix2.width());
    mtm::Dimensions sub_dims(matrix1.height(), matrix1.width());
    mtm::IntMatrix sub_matrix(sub_dims);
    sub_matrix = matrix1 + (-matrix2);
    return sub_matrix;
}

mtm::IntMatrix& mtm::IntMatrix::operator+=(const int num) {
    mtm::IntMatrix to_add(this->dims, num);
    *this = *this + to_add;
    return *this;
}

mtm::IntMatrix mtm::operator+(const mtm::IntMatrix& matrix, const int num) {
    IntMatrix sum_matrix(matrix);
    return (sum_matrix += num);
}

mtm::IntMatrix mtm::operator+(const int num, const mtm::IntMatrix& matrix) {
    IntMatrix sum_matrix(matrix);
    return (sum_matrix += num);
}

std::ostream& mtm::operator<<(std::ostream& os, const mtm::IntMatrix& matrix) {
    std::string string_matrix;
    string_matrix = mtm::printMatrix(matrix.data, matrix.dims);
    return os<<string_matrix;
}

mtm::IntMatrix& mtm::IntMatrix::inverseMatrix() {
    for (int i=0; i<(*this).height(); i++) {
        for (int j=0; j<(*this).width(); j++) {
            if ((*this)(i,j) == 0) {
                (*this)(i,j) = 1;
            }
            else {
                (*this)(i,j) = 0;
            }
        }
    }
    return (*this);
}

mtm::IntMatrix mtm::IntMatrix::operator==(int num) const {
    mtm::IntMatrix result_mat(this->dims);
    for (int i=0; i<result_mat.height(); i++) {
        for (int j=0; j<result_mat.width(); j++) {
            if ((*this)(i,j) == num) {
                result_mat(i,j) = 1;
            }
        }
    }
    return result_mat;
} 

mtm::IntMatrix mtm::IntMatrix::operator!=(int num) const {
    mtm::IntMatrix result_mat(this->dims);
    result_mat = (*this) == num;
    return result_mat.inverseMatrix();
}

mtm::IntMatrix mtm::IntMatrix::operator>(int num) const {
    mtm::IntMatrix result_mat(this->dims);
    for (int i=0; i<result_mat.height(); i++) {
        for (int j=0; j<result_mat.width(); j++) {
            if ((*this)(i,j) > num) {
                result_mat(i,j) = 1;
            }
        }
    }
    return result_mat;
} 

mtm::IntMatrix mtm::IntMatrix::operator<(int num) const {
    mtm::IntMatrix result_mat(this->dims);
    for (int i=0; i<result_mat.height(); i++) {
        for (int j=0; j<result_mat.width(); j++) {
            if ((*this)(i,j) < num) {
                result_mat(i,j) = 1;
            }
        }
    }
    return result_mat;
}

mtm::IntMatrix mtm::IntMatrix::operator<=(int num) const {
    mtm::IntMatrix result_mat(this->dims);
    result_mat = (*this) > num;
    return result_mat.inverseMatrix();
}

mtm::IntMatrix mtm::IntMatrix::operator>=(int num) const {
    mtm::IntMatrix result_mat(this->dims);
    result_mat = (*this) < num;
    return result_mat.inverseMatrix();
}

bool mtm::any(const IntMatrix& matrix) {
    for (int i=0; i<matrix.height(); i++) {
        for(int j=0; j<matrix.width(); j++) {
            if (matrix(i,j) != 0) {
                return true;
            }
        }
    }
    return false;
}

bool mtm::all(const IntMatrix& matrix) {
    for (int i=0; i<matrix.height(); i++) {
        for(int j=0; j<matrix.width(); j++) {
            if (matrix(i,j) == 0) {
                return false;
            }
        }
    }
    return true;
}

mtm::IntMatrix::iterator::iterator(mtm::IntMatrix* matrix, int index):
 matrix(matrix),
 index(index)
{}

int& mtm::IntMatrix::iterator::operator*() const {
    assert(index >= 0 && index < matrix->size());
    return matrix->data[index];
}

mtm::IntMatrix::iterator& mtm::IntMatrix::iterator::operator++() {
    ++index;
    return *this;
}

mtm::IntMatrix::iterator mtm::IntMatrix::iterator::operator++(int) {
    iterator result = *this;
    ++*this;
    return result;
} 

bool mtm::IntMatrix::iterator::operator==(const iterator& i) const {
    assert(matrix == i.matrix);
    return index == i.index;
}

bool mtm::IntMatrix::iterator::operator!=(const iterator& i) const {
    return !(*this == i);
}

mtm::IntMatrix::iterator mtm::IntMatrix::begin() {
    return iterator(this, 0);
}

mtm::IntMatrix::iterator mtm::IntMatrix::end() {
    return iterator(this, this->size());
}


mtm::IntMatrix::const_iterator::const_iterator(const mtm::IntMatrix* matrix, int index):
 matrix(matrix),
 index(index)
{}

const int& mtm::IntMatrix::const_iterator::operator*() const {
    assert(index >= 0 && index < matrix->size());
    return matrix->data[index];
}

const mtm::IntMatrix::const_iterator& mtm::IntMatrix::const_iterator::operator++() {
    ++index;
    return *this;
}

const mtm::IntMatrix::const_iterator mtm::IntMatrix::const_iterator::operator++(int) {
    const_iterator result = *this;
    ++*this;
    return result;
} 

bool mtm::IntMatrix::const_iterator::operator==(const const_iterator& i) const {
    assert(matrix == i.matrix);
    return index == i.index;
}

bool mtm::IntMatrix::const_iterator::operator!=(const const_iterator& i) const {
    return !(*this == i);
}

const mtm::IntMatrix::const_iterator mtm::IntMatrix::begin() const {
    return const_iterator(this, 0);
}

const mtm::IntMatrix::const_iterator mtm::IntMatrix::end() const{
    return const_iterator(this, this->size());
}