#ifndef MATRIX_H 
#define MATRIX_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"

namespace mtm { 
    template <class T>
    class Matrix {
        Dimensions dims;
        T* data;
    public:
        class iterator;
        class const_iterator;
        iterator begin();
        iterator end();
        const const_iterator begin() const;
        const const_iterator end() const;
        explicit Matrix(Dimensions dims, T value = 0);
        Matrix(const Matrix& matrix);
        ~Matrix();
        Matrix& operator=(const Matrix& matrix);
        static Matrix Diagonal(int size, int num); //no need for this pointer so is static
        Matrix transpose() const;
        int height() const;
        int width() const;
        int size() const;
        T& operator()(int row, int col);
        const T& operator()(int row, int col) const;
        Matrix operator-() const;
        Matrix& operator+=(const T num);
        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
        Matrix<bool>& inverseMatrix();
        Matrix<bool> operator==(T num) const;
        Matrix<bool> operator!=(T num) const;
        Matrix<bool> operator>(T num) const;
        Matrix<bool> operator<(T num) const;
        Matrix<bool> operator<=(T num) const;
        Matrix<bool> operator>=(T num) const;
        class AccessIllegalElement: public std::exception{
            public:
            const char* what() const {
                return "Mtm matrix error: An attempt to access an illegal element";
            }
        };
        class IllegalInitialization: public std::exception{
            public:
            const char* what() const {
                return "Mtm matrix error: Illegal initialization values";
            }
        };
        template <class T>
        class DimensionMismatch{
            Matrix<T> matrix1;
            Matrix<T> matrix2;
            public:
            DimensionMismatch(Matrix<T> matrix1,Matrix<T> matrix2): matrix1(matrix1),matrix2(matrix2) {}
            const std::string what() const {
                return "Mtm matrix error: Dimension mismatch:(" + std::to_string(matrix.height()) + "," +
                       std::to_string(matrix1.width())+ ") (" + std::to_string(matrix2.height()) + 
                       "," + std::to_string(matrix2.width()) + ")";
            }
        };
    };
    template <class T>
    class Matrix<T>::iterator {
        Matrix<T>* matrix;
        int index;
        iterator(Matrix<T>* matrix, int index);
        friend class Matrix;
        public:
        T& operator*() const;
        iterator& operator++();
        iterator operator++(int);
        bool operator==(const iterator& it) const;
        bool operator!=(const iterator& it) const;
        ~iterator() = default;
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;
    };
    template <class T>
    class Matrix<T>::const_iterator {
        const Matrix<T>* matrix;
        int index;
        const_iterator(const Matrix<T>* matrix, int index);
        friend class Matrix;
        public:
        const T& operator*() const;
        const const_iterator& operator++();
        const const_iterator operator++(int);
        bool operator==(const const_iterator& it) const;
        bool operator!=(const const_iterator& it) const;
        ~const_iterator() = default;
        const_iterator(const const_iterator&) = default;
        const_iterator& operator=(const const_iterator&) = default;
    };
    template <class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);
    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix1, const Matrix<T>& matrix2);
    template <class T>
    Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2);
    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix, const T num);
    template <class T>
    Matrix<T> operator+(const int num, const Matrix<T>& matrix);
    template <class T>
    bool any(const Matrix<T>& matrix);
    template <class T>
    bool all(const Matrix<T>& matrix);
} 

template <class T>
mtm::Matrix<T>::Matrix(Dimensions dims, T value): 
    dims(dims), data(new int[dims.getRow()*dims.getCol()])
 { 
     for (int i=0; i<dims.getRow()*dims.getCol(); i++) {
         data[i] = value;
     }
 }

template <class T>
mtm::Matrix<T>::Matrix(const Matrix<T>& matrix):
    dims(matrix.dims), data (new int[dims.getRow()*dims.getCol()])
 {
     for (int i=0; i<dims.getRow()*dims.getCol(); i++) {
         data[i] = matrix.data[i];
     }
 }

template <class T>
mtm::Matrix<T>::~Matrix() {
    delete[] this->data;
}

template <class T>
mtm::Matrix<T> mtm::Matrix<T>::Diagonal(int size, int num) {
    mtm::Dimensions dims(size,size);
    mtm::Matrix diagonal(dims);
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            if (i == j) {
                diagonal(i,j) = num;
            }
        }
    }
    return diagonal;
}

template <class T>
int mtm::Matrix<T>::height() const {
    return this->dims.getRow();
}

template <class T>
int mtm::Matrix<T>::width() const {
    return this->dims.getCol();
}

template <class T>
int mtm::Matrix<T>::size() const {
    return (this->dims.getRow() * this->dims.getCol());
}

template <class T>
mtm::Matrix<T> mtm::Matrix<T>::transpose() const {
    mtm::Dimensions trans_dims(dims.getCol(),dims.getRow());
    mtm::Matrix trans_matrix(trans_dims);
    for (int i=0; i<dims.getRow(); i++) {
        for (int j=0; j<dims.getCol(); j++) {
            trans_matrix(j,i) = (*this)(i,j);
        }
    }
    return trans_matrix;
}

template <class T>
mtm::Matrix<T> operator+(const mtm::Matrix<T>& matrix1, const mtm::Matrix<T>& matrix2) {
    mtm::Dimensions sum_dims(matrix1.height(), matrix1.width());
    mtm::Matrix<T> sum_matrix(sum_dims);
    for (int i=0; i<sum_matrix.height(); i++) {
        for (int j=0; j<sum_matrix.width(); j++) {
            sum_matrix(i,j) = matrix1(i,j) + matrix2(i,j);
        }
    }
    return sum_matrix;
}

template <class T>
mtm::Matrix<T> mtm::Matrix<T>::operator-() const {
    mtm::Matrix<T> new_matrix(this->dims);
    for (int i=0; i<dims.getRow(); i++) {
        for (int j=0; j<dims.getCol(); j++) {
            new_matrix(i,j) = -(*this)(i,j);
        }
    }
    return new_matrix;
}

template <class T>
mtm::Matrix<T> operator-(const mtm::Matrix<T>& matrix1, const mtm::Matrix<T>& matrix2) {
    assert(matrix1.height() == matrix2.height() && matrix1.width() == matrix2.width());
    mtm::Dimensions sub_dims(matrix1.height(), matrix1.width());
    mtm::Matrix<T> sub_matrix(sub_dims);
    sub_matrix = matrix1 + (-matrix2);
    return sub_matrix;
}

template <class T>
mtm::Matrix<T>& mtm::Matrix<T>::operator+=(const T num) {
    mtm::Matrix<T> to_add(this->dims, num);
    *this = *this + to_add;
    return *this;
}

template <class T>
mtm::Matrix<T> mtm::operator+(const mtm::Matrix<T>& matrix, const T num) {
    Matrix<T> sum_matrix(matrix);
    return (sum_matrix += num);
}

template <class T>
T& mtm::Matrix<T>::operator()(int row, int col){
    return data[dims.getCol()*row + col];
}

template <class T>
const T& mtm::Matrix<T>::operator()(int row, int col) const{
    return data[dims.getCol()*row + col];
}

template<class T>
mtm::Matrix<bool>& mtm::Matrix<T>::inverseMatrix() {
    for (int i=0; i<(*this).height(); i++) {
        for (int j=0; j<(*this).width(); j++) {
            (*this)(i,j) = !(*this)(i,j);
        }
    }
    return (*this);
}

template <class T>
std::ostream& mtm::operator<<(std::ostream& os, const mtm::Matrix<T>& matrix) {
    std::string string_matrix;
    string_matrix = mtm::printMatrix(os,matrix.begin(),matrix.end(),static_cast<unsigned int>(matrix.width()));
    return os<<string_matrix;
}

template <class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator==(T num) const{
    mtm::Matrix<bool> result_mat(this->dims,false);
    for (int i=0; i<result_mat.height(); i++) {
        for (int j=0; j<result_mat.width(); j++) {
            if ((*this)(i,j) == num) {
                result_mat(i,j) = true;
            }
        }
    }
    return result_mat;
}

template <class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator!=(T num) const {
    mtm::Matrix<bool> result_mat(this->dims);
    result_mat = (*this) == num;
    return result_mat.inverseMatrix();
}

template <class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator>(T num) const {
    mtm::Matrix<bool> result_mat(this->dims,false);
    for (int i=0; i<result_mat.height(); i++) {
        for (int j=0; j<result_mat.width(); j++) {
            if ((*this)(i,j) > num) {
                result_mat(i,j) = true;
            }
        }
    }
    return result_mat;
} 

template <class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator<(T num) const {
    mtm::Matrix<bool> result_mat(this->dims,false);
    for (int i=0; i<result_mat.height(); i++) {
        for (int j=0; j<result_mat.width(); j++) {
            if ((*this)(i,j) < num) {
                result_mat(i,j) = true;
            }
        }
    }
    return result_mat;
}

template <class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator<=(T num) const {
    mtm::Matrix<bool> result_mat(this->dims);
    result_mat = (*this) > num;
    return result_mat.inverseMatrix();
}

template <class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator>=(T num) const {
    mtm::Matrix<boo> result_mat(this->dims);
    result_mat = (*this) < num;
    return result_mat.inverseMatrix();
}

template <class T>
bool mtm::any(const Matrix<T>& matrix) {
    for (int i=0; i<matrix.height(); i++) {
        for(int j=0; j<matrix.width(); j++) {
            if (matrix(i,j) != false) {
                return true;
            }
        }
    }
    return false;
}

template <class T>
bool mtm::all(const Matrix<T>& matrix) {
    for (int i=0; i<matrix.height(); i++) {
        for(int j=0; j<matrix.width(); j++) {
            if (matrix(i,j) == false) {
                return false;
            }
        }
    }
    return true;
}

template <class T>
mtm::Matrix<T>::iterator::iterator(mtm::Matrix<T>* matrix, int index):
 matrix(matrix),
 index(index)
{}

template <class T>
T& mtm::Matrix<T>::iterator::operator*() const {
    assert(index >= 0 && index < matrix->size());
    return matrix->data[index];
}

template <class T>
mtm::Matrix<T>::iterator& mtm::Matrix<T>::iterator::operator++() {
    ++index;
    return *this;
}

template <class T>
mtm::Matrix<T>::iterator mtm::Matrix<T>::iterator::operator++(int) {
    iterator result = *this;
    ++*this;
    return result;
} 

template <class T>
bool mtm::Matrix<T>::iterator::operator==(const iterator& i) const {
    assert(matrix == i.matrix);
    return index == i.index;
}

template <class T>
bool mtm::Matrix<T>::iterator::operator!=(const iterator& i) const {
    return !(*this == i);
}

template <class T>
mtm::Matrix<T>::iterator mtm::Matrix<T>::begin() {
    return iterator(this, 0);
}

template <class T>
mtm::Matrix<T>::iterator mtm::Matrix<T>::end() {
    return iterator(this, this->size());
}

template <class T>
mtm::Matrix<T>::const_iterator::const_iterator(const mtm::Matrix<T>* matrix, int index):
 matrix(matrix),
 index(index)
{}

template <class T>
const T& mtm::Matrix<T>::const_iterator::operator*() const {
    assert(index >= 0 && index < matrix->size());
    return matrix->data[index];
}

template <class T>
const mtm::Matrix<T>::const_iterator& mtm::Matrix<T>::const_iterator::operator++() {
    ++index;
    return *this;
}

template <class T>
const mtm::Matrix<T>::const_iterator mtm::Matrix<T>::const_iterator::operator++(int) {
    const_iterator result = *this;
    ++*this;
    return result;
} 

template <class T>
bool mtm::Matrix<T>::const_iterator::operator==(const const_iterator& i) const {
    assert(matrix == i.matrix);
    return index == i.index;
}

template <class T>
bool mtm::Matrix<T>::const_iterator::operator!=(const const_iterator& i) const {
    return !(*this == i);
}

template <class T>
const mtm::Matrix<T>::const_iterator mtm::Matrix<T>::begin() const {
    return const_iterator(this, 0);
}

template <class T>
const mtm::Matrix<T>::const_iterator mtm::Matrix<T>::end() const{
    return const_iterator(this, this->size());
}

#endif //MATRIX_H
