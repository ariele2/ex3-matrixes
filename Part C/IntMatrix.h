#ifndef INT_MATRIX_H
#define INT_MATRIX_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"

namespace mtm { 
    class IntMatrix {
        Dimensions dims;
        int* data;
    public:
        class iterator;
        class const_iterator;
        iterator begin();
        iterator end();
        const const_iterator begin() const;
        const const_iterator end() const;
        explicit IntMatrix(Dimensions dims, int value = 0);
        IntMatrix(const IntMatrix& matrix);
        ~IntMatrix();
        IntMatrix& operator=(const IntMatrix& matrix);
        static IntMatrix Identity(int size); //no need for this pointer so is static
        IntMatrix transpose() const;
        int height() const;
        int width() const;
        int size() const;
        int& operator()(int row, int col);
        const int& operator()(int row, int col) const;
        IntMatrix operator-() const;
        IntMatrix& operator+=(const int num);
        friend std::ostream& operator<<(std::ostream& os, const IntMatrix& matrix);
        IntMatrix& inverseMatrix();
        IntMatrix operator==(int num) const;
        IntMatrix operator!=(int num) const;
        IntMatrix operator>(int num) const;
        IntMatrix operator<(int num) const;
        IntMatrix operator<=(int num) const;
        IntMatrix operator>=(int num) const;
    };
    class IntMatrix::iterator {
        IntMatrix* matrix;
        int index;
        iterator(IntMatrix* matrix, int index);
        friend class IntMatrix;
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
    class IntMatrix::const_iterator {
        const IntMatrix* matrix;
        int index;
        const_iterator(const IntMatrix* matrix, int index);
        friend class IntMatrix;
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
    std::ostream& operator<<(std::ostream& os, const IntMatrix& matrix);
    IntMatrix operator+(const IntMatrix& matrix1, const IntMatrix& matrix2);
    IntMatrix operator-(const IntMatrix& matrix1, const IntMatrix& matrix2);
    IntMatrix operator+(const IntMatrix& matrix, const int num);
    IntMatrix operator+(const int num, const IntMatrix& matrix);
    bool any(const IntMatrix& matrix);
    bool all(const IntMatrix& matrix);
} 

#endif //INT_MATRIX_H