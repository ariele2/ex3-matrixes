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
        static IntMatrix& Identity(int size); 
        static int* getData(const IntMatrix& matrix);
        int height();
        int width();
        int size();
    };
}

#endif //INT_MATRIX_H