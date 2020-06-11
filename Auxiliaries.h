#ifndef EX3_AUXILARIES_H
#define EX3_AUXILARIES_H
#include <string>
#include <iostream>



namespace mtm { 
    class Dimensions {
        int row, col;
    public:
        Dimensions( int row_t,  int col_t);
        std::string toString() const;
        bool operator==(const Dimensions& other) const;
        bool operator!=(const Dimensions& other) const;
        int getRow() const ;
        int getCol() const ;
    };
    
    std::string printMatrix(const int* matrix,const Dimensions& dim);

}



#endif //EX3_AUXILARIES_H
