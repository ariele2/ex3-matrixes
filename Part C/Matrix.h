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
        explicit Matrix(Dimensions dims, T value=T());
        Matrix(const Matrix& matrix);
        ~Matrix();
        Matrix& operator=(const Matrix& matrix);
        static Matrix Diagonal(int size, T element); //no need for this pointer so is static
        Matrix transpose() const;
        int height() const;
        int width() const;
        int size() const;
        T& operator()(int row, int col);
        const T& operator()(int row, int col) const;
        Matrix operator-() const;
        Matrix& operator+=(const T element);
        template <class U>
        friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix);
        Matrix<bool>& inverseMatrix();
        Matrix<bool> operator==(T element) const;
        Matrix<bool> operator!=(T element) const;
        Matrix<bool> operator>(T element) const;
        Matrix<bool> operator<(T element) const;
        Matrix<bool> operator<=(T element) const;
        Matrix<bool> operator>=(T element) const;
        
        template<class Predicate>
        Matrix apply(Predicate predicate) const {
            mtm::Matrix<T> new_matrix((*this).dims);
            for (int i=0; i<(*this).height(); i++) {
                for (int j=0; j<(*this).width(); j++) {
                    new_matrix(i,j) = predicate((*this)(i,j));
                }
            }
            return new_matrix;
        }
        class AccessIllegalElement;
        class IllegalInitialization;
        class DimensionMismatch;
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
    class Matrix<T>::AccessIllegalElement: public mtm::Exception{
        public:
        const char* what() const noexcept override{
            return "Mtm matrix error: An attempt to access an illegal element";
        }
    };
    template <class T>
    class Matrix<T>::IllegalInitialization: public mtm::Exception{
        public:
        const char* what() const noexcept override{
            return "Mtm matrix error: Illegal initialization values";
        }
    };
    template <class T>
    class Matrix<T>::DimensionMismatch: public mtm::Exception{
        mtm::Dimensions dims_mat_1, dims_mat_2;
        std::string error_str;
        public:
        DimensionMismatch(mtm::Dimensions dims_mat_1, mtm::Dimensions dims_mat_2): 
                            dims_mat_1(dims_mat_1), dims_mat_2(dims_mat_2),
                            error_str("Mtm matrix error: Dimension mismatch: "
                             + dims_mat_1.toString() + " " + dims_mat_2.toString())  {}
        const char* what() const noexcept override{
            return error_str.c_str();
        }
    };
    // use operator<< to print the matrix, while supplying to the function the matrix that you want to print
    template <class T> 
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
        return mtm::printMatrix(os,matrix.begin(),matrix.end(),(matrix.width()));
    }
    // this opertaor+ adds two matrices while checking if they both have the same dimensions and type.
    // adds the elements on the same spot on one matrix with the other one.
    //assuming there is operator+ for type T
    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix1, const Matrix<T>& matrix2) {
        mtm::Dimensions dims1(matrix1.height(),matrix1.width());
        mtm::Dimensions dims2(matrix2.height(),matrix2.width());
        if (dims1 != dims2) {
            throw typename mtm::Matrix<T>::DimensionMismatch(dims1, dims2);
        }
        mtm::Matrix<T> sum_matrix(dims1);
        for (int i=0; i<sum_matrix.height(); i++) { //cant go out of bounds - no need to check
            for (int j=0; j<sum_matrix.width(); j++) {
                sum_matrix(i,j) = matrix1(i,j) + matrix2(i,j);
            }
        }
        return sum_matrix;
    }
    // opertaor- subtract two matrices while checking if they both have the same dimensions and type.
    // subtracts the elements on the same spot on one matrix with the other one.
    //assuming there is operator- for type T
    template <class T>
    Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2) {
        mtm::Dimensions dims1(matrix1.height(),matrix1.width());
        mtm::Dimensions dims2(matrix2.height(),matrix2.width());
        if (dims1 != dims2) {
            throw typename mtm::Matrix<T>::DimensionMismatch(dims1, dims2);
        }
        mtm::Matrix<T> sub_matrix(dims1);
        sub_matrix = matrix1 + (-matrix2);
        return sub_matrix;
    }
    // the two opertaor+ below, adds an element to a matrix while checking if the element and the matrix
    // shares the same type. adds the element to all of the elements inside the matrix.
    //assuming there is operator+ for type T
    template <class T>
    Matrix<T> operator+(const Matrix<T>& matrix, const T element) {
        Matrix<T> sum_matrix(matrix);
        return (sum_matrix += element); 
    }
    template <class T>
    Matrix<T> operator+(const T element, const Matrix<T>& matrix) {
        mtm::Dimensions sum_dims(matrix.height(),matrix.width());
        Matrix<T> element_matrix(sum_dims,element);
        return (element_matrix + matrix);
    }
    // checks if any of the elements inside the matrix conatins the value true, if so returns true
    // otherwise, returns false.
    template <class T>
    bool any(const Matrix<T>& matrix) {
        for (int i=0; i<matrix.height(); i++) {
            for(int j=0; j<matrix.width(); j++) {
                if (matrix(i,j)) {
                    return true;
                }
            }
        }
        return false;
    }
    // checks if all of the elements inside the matrix conatins the value true, if so returns true
    // otherwise, returns false.
    template <class T>
    bool all(const Matrix<T>& matrix) {
        for (int i=0; i<matrix.height(); i++) {
            for(int j=0; j<matrix.width(); j++) {
                if (!matrix(i,j)) {
                    return false;
                }
            }
        }
    return true;
    }
} 

// constructor - recievs dims of Dimensions type, and a gneric value T to make a new matrix.
template <class T>
mtm::Matrix<T>::Matrix(Dimensions dims, T value):
    dims(dims), data(NULL) {
    if (dims.getRow() <= 0 || dims.getCol() <=0) {
        throw typename mtm::Matrix<T>::IllegalInitialization();
    }
        data = new T[dims.getRow()*dims.getCol()];
        int mat_size = (*this).size();
    try {
        for (int i=0; i<mat_size; i++) {
            data[i] = value;
        }
    } 
    catch (std::exception& e) {
        delete[] this->data;
        throw;
    }
}

// copy constructor - recievs a matrix, and returns a new copy of it.
//assuming there is operator= for type T
template <class T>
mtm::Matrix<T>::Matrix(const Matrix<T>& matrix):
    dims(matrix.dims) {
    if (dims.getRow() <= 0 || dims.getCol() <=0) {
        throw typename mtm::Matrix<T>::IllegalInitialization();
    }
        data = new T[dims.getRow()*dims.getCol()];
        int mat_size = (*this).size();
    try {
        for (int i=0; i<mat_size; i++) {
            data[i] = matrix.data[i];
        }
    }
    catch (std::exception& e) {
        delete[] this->data;
        throw;
    }
}

// destructor - in charge of erasing the data we have allocated for the matrix.
template <class T>
mtm::Matrix<T>::~Matrix() {
    delete[] this->data;
}

//operator= : recievs an already initialized matrix, and assigning the recived matrix to the requested matrix. 
template <class T>
mtm::Matrix<T>& mtm::Matrix<T>::operator=(const Matrix<T>& matrix) {
    if (this == &matrix) {
        return *this;
    }
    mtm::Matrix<T> matrix_holder(matrix);  
    delete[] this->data;
    this->data = matrix_holder.data;
    this->dims = matrix.dims;
    matrix_holder.data = NULL;
    return (*this);
}
// makes a diagonal matrix, while recieving the size (rows and columns the same size) and the element
//assuming there is operator= for type T
template <class T>
mtm::Matrix<T> mtm::Matrix<T>::Diagonal(int size, T element) {
    if (size <= 0) {
        throw IllegalInitialization();
    }
    mtm::Dimensions dims(size,size);
    mtm::Matrix<T> diagonal(dims);
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            if (i == j) {
                diagonal(i,j) = element;
            }
        }
    }
    return diagonal;
}

// returns the height of the matrix (number of rows)
template <class T>
int mtm::Matrix<T>::height() const {
    return this->dims.getRow();
}

//returns the width of the matrix (number of columns)
template <class T>
int mtm::Matrix<T>::width() const {
    return this->dims.getCol();
}

// return the size of the matrix (rows*columns)
template <class T>
int mtm::Matrix<T>::size() const {
    return (this->dims.getRow() * this->dims.getCol());
}

// transposes the matrix - makes the rows as columns and the columns as rows.
//assuming there is operator= for type T
template <class T>
mtm::Matrix<T> mtm::Matrix<T>::transpose() const {
    mtm::Dimensions trans_dims(dims.getCol(),dims.getRow());
    mtm::Matrix<T> trans_matrix(trans_dims);
    for (int i=0; i<dims.getRow(); i++) {
        for (int j=0; j<dims.getCol(); j++) {
            trans_matrix(j,i) = (*this)(i,j);
        }
    }
    return trans_matrix;
}

// unary operator - , use this to make all the elements in the matrix to the opposite mark.
//assuming there is  unary operator- for type T
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

// adds an element to the given matrix - (adds it to all of the elements in the matrix)
//assuming there is operator+ for type T
template <class T>
mtm::Matrix<T>& mtm::Matrix<T>::operator+=(const T element) {
    mtm::Matrix<T> to_add(this->dims, element);
    *this = *this + to_add;
    return *this;
}

// operator() - use this to access an element inside the matrix by (row,column) syntax. (non const matrix)
template <class T>
T& mtm::Matrix<T>::operator()(int row, int col){
    if (row >= (*this).height() || row < 0 || col >= (*this).width() || col < 0) {
        throw typename mtm::Matrix<T>::AccessIllegalElement();
    }
    return data[dims.getCol()*row + col];
}

// operator() - use this to access an element inside the matrix by (row,column) syntax. (const matrix)
template <class T>
const T& mtm::Matrix<T>::operator()(int row, int col) const{
    if (row >= (*this).height() || row < 0 || col >= (*this).width() || col < 0) {
        throw typename mtm::Matrix<T>::AccessIllegalElement();
    }
    return data[dims.getCol()*row + col];
}

// a helper function - changes all true elements inside the matrix to false, and false to true.
template<class T>
mtm::Matrix<bool>& mtm::Matrix<T>::inverseMatrix() {
    for (int i=0; i<(*this).height(); i++) {
        for (int j=0; j<(*this).width(); j++) {
            (*this)(i,j) = !(*this)(i,j);
        }
    }
    return (*this);
}

// use this to find how many elements in the matrix are equal to a given element. returns a bool matrix
// with true on the spots where it is equal, and false where it is not.
//assuming there is operator== for type T
template <class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator==(T element) const{
    mtm::Matrix<bool> result_mat(this->dims,false);
    for (int i=0; i<result_mat.height(); i++) {
        for (int j=0; j<result_mat.width(); j++) {
            if ((*this)(i,j) == element) {
                result_mat(i,j) = true;
            }
        }
    }
    return result_mat;
}

// same as the operator== but the other way (fins all the elements not equal to the given element)
//assuming there is operator== for type T
template <class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator!=(T element) const {
    mtm::Matrix<bool> result_mat(this->dims);
    result_mat = (*this) == element;
    return result_mat.inverseMatrix();
}

// use this to find how many elements in the matrix are bigger than a given element. returns a bool matrix
// with true on the spots where it is bigger, and false where it is not.
//assuming there is operator> for type T
template <class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator>(T element) const {
    mtm::Matrix<bool> result_mat(this->dims,false);
    for (int i=0; i<result_mat.height(); i++) {
        for (int j=0; j<result_mat.width(); j++) {
            if ((*this)(i,j) > element) {
                result_mat(i,j) = true;
            }
        }
    }
    return result_mat;
} 

// use this to find how many elements in the matrix are smaller than a given element. returns a bool matrix
// with true on the spots where it is smaller, and false where it is not.
//assuming there is operator< for type T
template <class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator<(T element) const {
    mtm::Matrix<bool> result_mat(this->dims,false);
    for (int i=0; i<result_mat.height(); i++) {
        for (int j=0; j<result_mat.width(); j++) {
            if ((*this)(i,j) < element) {
                result_mat(i,j) = true;
            }
        }
    }
    return result_mat;
}

// use this to find how many elements in the matrix are smaller or equal to a given element. returns a bool matrix
// with true on the spots where it is smaller or equal, and false where it is not.
//assuming there is operator> for type T
template <class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator<=(T element) const {
    mtm::Matrix<bool> result_mat(this->dims);
    result_mat = (*this) > element;
    return result_mat.inverseMatrix();
}

// use this to find how many elements in the matrix are bigger or equal to a given element. returns a bool matrix
// with true on the spots where it is bigger or equal, and false where it is not.
//assuming there is operator< for type T
template <class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator>=(T element) const {
    mtm::Matrix<bool> result_mat(this->dims);
    result_mat = (*this) < element;
    return result_mat.inverseMatrix();
}

// iterator constructor - makes a new iterator that contains a pointer to matrix and the index.
template <class T>
mtm::Matrix<T>::iterator::iterator(mtm::Matrix<T>* matrix, int index):
 matrix(matrix),
 index(index)
{}

// iterator operator* - granting access to the element the iterator points to.
template <class T>
T& mtm::Matrix<T>::iterator::operator*() const {
    if(index < 0 || index >= matrix->size()) {
        throw typename mtm::Matrix<T>::AccessIllegalElement();
    }
    return matrix->data[index];
}

// operator++ moves the interator by one index ahead (happens befor the operation).
template <class T>
typename mtm::Matrix<T>::iterator& mtm::Matrix<T>::iterator::operator++() {
    ++index;
    return *this;
}

// operator++ moves the interator by one index ahead (happens after the operation).
template <class T>
typename mtm::Matrix<T>::iterator mtm::Matrix<T>::iterator::operator++(int) {
    iterator result = *this;
    ++*this;
    return result;
} 

// operator== check equality between the pointed objects of the iterators comparing.
template <class T>
bool mtm::Matrix<T>::iterator::operator==(const iterator& i) const {
    return index == i.index;
}

// operator!= check non equality between the pointed objects of the iterators comparing.
template <class T>
bool mtm::Matrix<T>::iterator::operator!=(const iterator& i) const {
    return !(*this == i);
}

// returns a new iterator to the begining of the matrix it points to.
template <class T>
typename mtm::Matrix<T>::iterator mtm::Matrix<T>::begin() {
    return iterator(this, 0);
}

// returns a new iterator to the end of the matrix it points to.
template <class T>
typename mtm::Matrix<T>::iterator mtm::Matrix<T>::end() {
    return iterator(this, this->size());
}

// const iterator constructor - makes a new iterator that contains a pointer to matrix and the index.
template <class T>
mtm::Matrix<T>::const_iterator::const_iterator(const mtm::Matrix<T>* matrix, int index):
 matrix(matrix),
 index(index)
{}

// const iterator operator* - granting access to the element the iterator points to (cant change the element).
template <class T>
const T& mtm::Matrix<T>::const_iterator::operator*() const {
    if(index < 0 || index >= matrix->size()) {
        throw AccessIllegalElement();
    }
    return matrix->data[index];
}

// const operator++ moves the interator by one index ahead (happens befor the operation).
template <class T>
const typename mtm::Matrix<T>::const_iterator& mtm::Matrix<T>::const_iterator::operator++() {
    ++index;
    return *this;
}

// operator++ moves the interator by one index ahead (happens after the operation).
template <class T>
const typename mtm::Matrix<T>::const_iterator mtm::Matrix<T>::const_iterator::operator++(int) {
    const_iterator result = *this;
    ++*this;
    return result;
} 

// operator== check equality between the pointed objects of the iterators comparing.
template <class T>
bool mtm::Matrix<T>::const_iterator::operator==(const const_iterator& i) const {
    return index == i.index;
}

// operator!= check non equality between the pointed objects of the iterators comparing.
template <class T>
bool mtm::Matrix<T>::const_iterator::operator!=(const const_iterator& i) const {
    return !(*this == i);
}

// returns a new iterator to the begining of the matrix it points to.
template <class T>
const typename mtm::Matrix<T>::const_iterator mtm::Matrix<T>::begin() const {
    return const_iterator(this, 0);
}

// const iterator constructor - makes a new iterator that contains a pointer to matrix and the index.
template <class T>
const typename mtm::Matrix<T>::const_iterator mtm::Matrix<T>::end() const{
    return const_iterator(this, this->size());
}

#endif //MATRIX_H
