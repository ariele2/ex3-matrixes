#ifndef INT_MATRIX_H
#define INT_MATRIX_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"

namespace mtm { 
    class IntMatrix {
        int* data;
        Dimensions dims;
    public:
        explicit IntMatrix(Dimensions dims, int value = 0);
        IntMatrix(const IntMatrix& matrix);
        ~IntMatrix();
        IntMatrix& operator=(const IntMatrix& matrix);
        static IntMatrix& Identity(int size); //no need for this pointer so is static
        IntMatrix& transpose();
        int height() const;
        int width() const;
        int size() const;
        int& operator()(int row, int col);
        const int& operator()(int row, int col) const;
        IntMatrix operator-() const;
        IntMatrix& operator+=(const int num);
    };
    IntMatrix operator+(const IntMatrix& matrix1, const IntMatrix& matrix2);
    IntMatrix operator-(const IntMatrix& matrix1, const IntMatrix& matrix2);
    IntMatrix operator+(const IntMatrix& matrix, const int num);
} 

#endif //INT_MATRIX_H