#ifndef HW3_Soldier_H
#define HW3_Soldier_H
#include "Character.h"

namespace mtm {
    class Soldier : public Character {
        public:
        Soldier() = delete;
        Soldier(int health, int ammo, int range, int power);
        Character* clone() const override;
    };
}

#endif