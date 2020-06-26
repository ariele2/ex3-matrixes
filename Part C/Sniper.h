#ifndef HW3_Sniper_H
#define HW3_Sniper_H
#include "Character.h"

namespace mtm {
    class Sniper : public Character {
        public:
        void move() const; 
        void reload() const; 
        void attack() const; 
    };
}

#endif