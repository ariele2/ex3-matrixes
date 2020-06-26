#include "Soldier.h"

using namespace mtm;

Character* Soldier::clone() const {
    return new Soldier(*this);
}

Soldier::Soldier(int health, int ammo, int range, int power): Character(health,ammo,range,power) {}
         