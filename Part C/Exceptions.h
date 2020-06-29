#ifndef HW3_EXCEPTIONS_H
#define HW3_EXCEPTIONS_H
#include "Auxiliaries.h"
#include <iostream>

namespace mtm {
    class GameException : public Exception {};
    class IllegalArgument : public GameException {
        public:
        const char* what() const noexcept override;
    }; 
    class IllegalCell : public GameException {
        public:
        const char* what() const noexcept override;
    };
    class CellEmpty : public GameException {
        public:
        const char* what() const noexcept override;
    };
    class MoveTooFar : public GameException{
        public:
        const char* what() const noexcept override;
    };
    class CellOccupied : public GameException {
        public:
        const char* what() const noexcept override;
    };
    class OutOfRange : public GameException {
        public:
        const char* what() const noexcept override;
    };
    class OutOfAmmo : public GameException {
        public:
        const char* what() const noexcept override;
    };
    class IllegalTarget : public GameException {
        public:
        const char* what() const noexcept override;
    };
}



 



#endif