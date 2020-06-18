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
        int& operator()(int row, int col);
        const int& operator()(int row, int col) const;
        Matrix operator-() const;
        Matrix& operator+=(const int num);
        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
        Matrix& inverseMatrix();
        Matrix operator==(int num) const;
        Matrix operator!=(int num) const;
        Matrix operator>(int num) const;
        Matrix operator<(int num) const;
        Matrix operator<=(int num) const;
        Matrix operator>=(int num) const;
    };
    class Matrix::iterator {
        Matrix* matrix;
        int index;
        iterator(Matrix* matrix, int index);
        friend class Matrix;
        public:
        int& operator*() const;
        iterator& operator++();
        iterator operator++(int);
        bool operator==(const iterator& it) const;
        bool operator!=(const iterator& it) const;
        ~iterator() = default;
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;
    };
    class Matrix::const_iterator {
        const Matrix* matrix;
        int index;
        const_iterator(const Matrix* matrix, int index);
        friend class Matrix;
        public:
        const int& operator*() const;
        const const_iterator& operator++();
        const const_iterator operator++(int);
        bool operator==(const const_iterator& it) const;
        bool operator!=(const const_iterator& it) const;
        ~const_iterator() = default;
        const_iterator(const const_iterator&) = default;
        const_iterator& operator=(const const_iterator&) = default;
    };
    std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix1, const Matrix<T>& matrix2);
    template <class T>
    Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2);
    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix, const T num);
    Matrix operator+(const int num, const Matrix& matrix);
    bool any(const Matrix& matrix);
    bool all(const Matrix& matrix);
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
mtm::Matrix<T>::~IntMatrix() {
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
    mtm::IntMatrix sum_matrix(sum_dims);
    for (int i=0; i<sum_matrix.height(); i++) {
        for (int j=0; j<sum_matrix.width(); j++) {
            sum_matrix(i,j) = matrix1(i,j) + matrix2(i,j);
        }
    }
    return sum_matrix;
}

template <class T>
mtm::Matrix<T> mtm::Matrix<T>::operator-() const {
    mtm::IntMatrix new_matrix(this->dims);
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
    mtm::IntMatrix sub_matrix(sub_dims);
    sub_matrix = matrix1 + (-matrix2);
    return sub_matrix;
}

template <class T>
mtm::Matrix<T>& mtm::Matrix<T>::operator+=(const int num) {
    mtm::IntMatrix to_add(this->dims, num);
    *this = *this + to_add;
    return *this;
}

template <class T>
mtm::Matrix<T> mtm::operator+(const mtm::Matrix<T>& matrix, const T num) {
    IntMatrix sum_matrix(matrix);
    return (sum_matrix += num);
}

#endif //MATRIX_H


